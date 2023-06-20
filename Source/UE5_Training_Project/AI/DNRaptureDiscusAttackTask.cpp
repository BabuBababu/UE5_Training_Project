


#include "UE5_Training_Project/AI/DNRaptureDiscusAttackTask.h"

// Engine
#include <BehaviorTree/BlackboardComponent.h>

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// Component
#include <UE5_Training_Project/Component/DNStatusComponent.h>

// BlackBaord
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"

// Character
#include "UE5_Training_Project/Character/DNAirRaptureCharacter.h"


UDNRaptureDiscusAttackTask::UDNRaptureDiscusAttackTask(FObjectInitializer const& object_initializer)
{

	NodeName = TEXT("RaptureDiscusAttackTask");
}


EBTNodeResult::Type UDNRaptureDiscusAttackTask::ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in)
{
	Super::ExecuteTask(owner_comp_in, NodeMemory_in);

	bNotifyTick = true; //틱 태스크 활성화

	// 컨트롤러
	auto controller = Cast<ADNAIController>(owner_comp_in.GetAIOwner());
	APawn* self_pawn = controller->GetPawn();

	// 캐릭터
	ADNAirRaptureCharacter* self_actor = Cast<ADNAirRaptureCharacter>(self_pawn);

	if (self_actor->get_status_component().Get()->_dead)
	{
		return EBTNodeResult::Failed;
	}
	// 타겟 캐릭터
	auto target = controller->get_blackboard()->GetValueAsObject(all_ai_bb_keys::target_actor);
	ADNCommonCharacter* target_character = Cast<ADNCommonCharacter>(target);

	if (nullptr == target)											//타겟 없으면 실패
	{
		self_actor->set_idle_animation();
		controller->ClearFocus(EAIFocusPriority::Gameplay);

		return EBTNodeResult::Failed;
	}

	if (true == target_character->_status->_dead)					//타겟이 죽어있으면 실패
	{
		controller->get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, nullptr);
		controller->ClearFocus(EAIFocusPriority::Gameplay);
		self_actor->set_idle_animation();
		return EBTNodeResult::Failed;
	}

	if (self_actor->_fire_1_current_time <= 0.1f)
	{
		controller->SetFocus(target_character);
		self_actor->fire_1(target_character);			// 미사일 발사
	}

	return EBTNodeResult::Succeeded;
}


void UDNRaptureDiscusAttackTask::TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds)
{
	Super::TickTask(owner_comp_in, NodeMemory_in, DeltaSeconds);

	
}