


#include "UE5_Training_Project/AI/DNChaseEnemyTask.h"


// Engine
#include <NavigationSystem.h>
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Vector.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <Blueprint/AIBlueprintHelperLibrary.h>

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Component
#include <UE5_Training_Project/Component/DNStatusComponent.h>

// BlackBaord
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"





UDNChaseEnemyTask::UDNChaseEnemyTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("FindEnemyPosTask");
}


EBTNodeResult::Type UDNChaseEnemyTask::ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in)
{
	Super::ExecuteTask(owner_comp_in, NodeMemory_in);

	auto Controller = Cast<ADNAIController>(owner_comp_in.GetAIOwner());
	auto self = Controller->GetPawn();
	ADNCommonCharacter* self_actor = dynamic_cast<ADNCommonCharacter*>(self);


	if (nullptr == self) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("self Initialize faild!"));
		return EBTNodeResult::Failed;
	}

	if (self_actor->get_status_component().Get()->_dead)
		return EBTNodeResult::Failed;

	//현재 에디터에 설정된 navi mesh로 초기화
	UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (nullptr == NavSystem) 
	{
		//navi mesh가 없다면 실패를 반환
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Enemy in Navi"));
		return EBTNodeResult::Failed;
	}

	ADNCommonCharacter* target = Cast<ADNCommonCharacter>(Controller->get_blackboard()->GetValueAsObject(all_ai_bb_keys::target_actor));
	if (nullptr == target)
		return EBTNodeResult::Failed;


	FVector const Origin = target->GetActorLocation();
	Controller->SetFocus(target);		// 타겟 바라보기


	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, Origin);


	//FNavLocation NextPatrol;
	//NextPatrol변수에 임의의 location 데이터를 넣고 다시 TargetLocation키의 value에 값을 넣어준다.
	/*if (NavSystem->GetRandomPointInNavigableRadius(Origin, _search_radius, NextPatrol, nullptr))
	{
		
	}*/


	FinishLatentTask(owner_comp_in, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}