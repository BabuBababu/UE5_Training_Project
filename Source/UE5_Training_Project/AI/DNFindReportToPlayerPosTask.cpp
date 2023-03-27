


#include "UE5_Training_Project/AI/DNFindReportToPlayerPosTask.h"


// Engine
#include <NavigationSystem.h>
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Vector.h>
#include <BehaviorTree/BlackboardComponent.h>

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"


// Character
#include "UE5_Training_Project/Character/DNPlayerCharacter.h"
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"

// Component
#include <UE5_Training_Project/Component/DNStatusComponent.h>

// BlackBaord
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"

// Manager
#include "UE5_Training_Project/Manager/DNLobbyNPCManager.h"


//
//	당직부관 근처 임의의 위치를 반환합니다.
//
//


UDNFindReportToPlayerPosTask::UDNFindReportToPlayerPosTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("FindPlayerPosTask");

}


EBTNodeResult::Type UDNFindReportToPlayerPosTask::ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in)
{
	Super::ExecuteTask(owner_comp_in, NodeMemory_in);

	auto Controller = Cast<ADNAIController>(owner_comp_in.GetAIOwner());
	auto self = Controller->GetPawn();

	ADNUnEnemyCharacter* self_actor = Cast<ADNUnEnemyCharacter>(self);
	ADNPlayerCharacter* player = dynamic_cast<ADNPlayerCharacter*>(GetWorld()->GetFirstPlayerController()->GetPawn());

	// 타겟에 플레이어를 배정합니다.
	Controller->get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor,player);


	//현재 에디터에 설정된 navi mesh로 초기화
	UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (nullptr == NavSystem) {
		//navi mesh가 없다면 실패를 반환
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Enemy in Navi"));
		return EBTNodeResult::Failed;
	}



	FVector player_location;
	FNavLocation NextPatrol;

	// 당직부관은 1명으로 할것이지만 추후에 여러명이 될수있으므로 컨테이너에 담았습니다.
	for (auto& doll : LOBBY_MANAGER->_post_doll_array)
	{
		player_location = doll.Value->GetActorLocation();
	}

	

	if (nullptr == self_actor)
		return EBTNodeResult::Failed;

	if (self_actor->get_status_component().Get()->_dead)
		return EBTNodeResult::Failed;


	// 포커스 해제합니다.
	Controller->ClearFocus(EAIFocusPriority::Gameplay);



	//NextPatrol변수에 임의의 location 데이터를 넣고 다시 TargetLocation키의 value에 값을 넣어준다.
	if (NavSystem->GetRandomPointInNavigableRadius(player_location, _search_radius, NextPatrol, nullptr))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Next Patrol position :%s"), *NextPatrol.Location.ToString()));

		Controller->get_blackboard()->SetValueAsVector(all_ai_bb_keys::target_location, NextPatrol);

	

	}








	self_actor->set_idle_animation();

	return EBTNodeResult::Succeeded;

}