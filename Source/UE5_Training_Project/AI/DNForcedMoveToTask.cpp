


#include "UE5_Training_Project/AI/DNForcedMoveToTask.h"


// Engine
#include <NavigationSystem.h>
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Vector.h>
#include <BehaviorTree/BlackboardComponent.h>

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// BlackBaord
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"






UDNForcedMoveToTask::UDNForcedMoveToTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("ForcedMoveToTask");
}



EBTNodeResult::Type UDNForcedMoveToTask::ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in)
{
	Super::ExecuteTask(owner_comp_in, NodeMemory_in);

	auto Controller = Cast<ADNAIController>(owner_comp_in.GetAIOwner());
	auto self = Controller->GetPawn();
	ADNCommonCharacter* self_actor = dynamic_cast<ADNCommonCharacter*>(self);


	Controller->ClearFocus(EAIFocusPriority::Gameplay);
	Controller->MoveToLocation(Controller->get_blackboard()->GetValueAsVector(all_ai_bb_keys::target_location), 10.f, true, true, true);		// 10.f은 오차허용 범위, 타겟 지역으로 이동


	return EBTNodeResult::Succeeded;
}


void UDNForcedMoveToTask::TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds)
{
	Super::TickTask(owner_comp_in, NodeMemory_in, DeltaSeconds);

	/*if (nullptr != Controller->get_blackboard()->GetValueAsObject(all_ai_bb_keys::target_actor))
	{
		FinishLatentTask(owner_comp_in, EBTNodeResult::Succeeded);
	}*/
}