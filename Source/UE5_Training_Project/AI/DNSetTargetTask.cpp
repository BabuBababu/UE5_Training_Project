


#include "UE5_Training_Project/AI/DNSetTargetTask.h"

// Engine
#include <NavigationSystem.h>
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Vector.h>
#include <BehaviorTree/BlackboardComponent.h>


// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Component
#include <UE5_Training_Project/Component/DNStatusComponent.h>

// BlackBaord
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"

UDNSetTargetTask::UDNSetTargetTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("SetTargetTask");
	bNotifyTick = false;			// 틱 비활성화
}


EBTNodeResult::Type UDNSetTargetTask::ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in)
{
	Super::ExecuteTask(owner_comp_in, NodeMemory_in);

	// 컨트롤러
	ADNAIController* controller = Cast<ADNAIController>(owner_comp_in.GetAIOwner());
	APawn* self_pawn = controller->GetPawn();

	// 캐릭터
	ADNCommonCharacter* self_actor = Cast<ADNCommonCharacter>(self_pawn);

	if (self_actor->get_status_component().Get()->_dead)
	{
		return EBTNodeResult::Failed;
	}

	if(nullptr == controller)
		return EBTNodeResult::Failed;
	
	if (controller->_target_array.Num() == 0)		// 저장해둔 타겟이 없으면
	{
		controller->get_blackboard()->SetValueAsBool(all_ai_bb_keys::is_find_target, false);
		controller->get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, nullptr);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("find target is false!"));
		return EBTNodeResult::Failed;
	}
	else
	{
		controller->get_blackboard()->SetValueAsBool(all_ai_bb_keys::is_find_target, true);

		for (auto& target : controller->_target_array) //가드라면 여기서 미사일 우선순위로
		{
			controller->get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, target);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("find target is true!"));
			return EBTNodeResult::Succeeded;
		}
	}

	

	return EBTNodeResult::Succeeded;
}



void UDNSetTargetTask::TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds)
{
	Super::TickTask(owner_comp_in, NodeMemory_in, DeltaSeconds);


}