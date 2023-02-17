﻿


#include "UE5_Training_Project/AI/DNFindCheckPointTask.h"


// Engine
#include <NavigationSystem.h>
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Vector.h>
#include <BehaviorTree/BlackboardComponent.h>

// Actor
#include "UE5_Training_Project/Actor/DNTargetPointActor.h"

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Component
#include <UE5_Training_Project/Component/DNStatusComponent.h>

// BlackBaord
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"





UDNFindCheckPointTask::UDNFindCheckPointTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("FindCheckPointTask");
}



EBTNodeResult::Type UDNFindCheckPointTask::ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in)
{
	Super::ExecuteTask(owner_comp_in, NodeMemory_in);

	auto Controller = Cast<ADNAIController>(owner_comp_in.GetAIOwner());
	auto self = Controller->GetPawn();
	ADNCommonCharacter* self_actor = dynamic_cast<ADNCommonCharacter*>(self);


	if (nullptr == self) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("self Initialize faild!"));
		return EBTNodeResult::Failed;
	}

	if (self_actor->get_status_component().Get()->_dead)
		return EBTNodeResult::Failed;

	//현재 에디터에 설정된 navi mesh로 초기화
	UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (nullptr == NavSystem) {
		//navi mesh가 없다면 실패를 반환
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Enemy in Navi"));
		return EBTNodeResult::Failed;
	}

	if (nullptr == _now_point)									//타겟 포인트가 없다면 넣어줍니다.
	{
		if (false == OBJECT_MANAGER->_location_actor_array.IsEmpty())
		{
			for (auto& location : OBJECT_MANAGER->_location_actor_array)
			{
				if (0 == location.Key)
				{
					_now_point = location.Value;
				}
			}
		}
	}

	if (_now_point->_is_destroyed)
	{
		if (false == OBJECT_MANAGER->_location_actor_array.IsEmpty())
		{
			for (auto& location : OBJECT_MANAGER->_location_actor_array)
			{
				if (_now_point->_index + 1 == location.Key)
				{
					_now_point = location.Value;				// 점령 당했다면 그 다음 포인트가 적용됩니다.
				}
			}
		}
	}

	FVector const Origin = _now_point->GetActorLocation();
	FNavLocation NextPatrol;

	//NextPatrol변수에 임의의 location 데이터를 넣고 다시 TargetLocation키의 value에 값을 넣어준다.
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, _search_radius, NextPatrol, nullptr))
	{
		Controller->get_blackboard()->SetValueAsVector(all_ai_bb_keys::target_location, NextPatrol.Location);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NextPosSuccess!"));
	}

	//그 다음 이동할 곳을 확인하기 위한 디버그메시지
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s"), *NextPatrol.Location.ToString()));

	FinishLatentTask(owner_comp_in, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}