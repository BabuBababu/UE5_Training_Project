


#include "UE5_Training_Project/AI/DNHeliMissileAttackTask.h"

// Engine
#include <BehaviorTree/BlackboardComponent.h>

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// Component
#include <UE5_Training_Project/Component/DNStatusComponent.h>

// BlackBaord
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"

// Character
#include "UE5_Training_Project/Character/DNHeliCommonCharacter.h"


UDNHeliMissileAttackTask::UDNHeliMissileAttackTask(FObjectInitializer const& object_initializer)
{

	NodeName = TEXT("HeliMissileAttackTask");
	//bNotifyTick = true;			// ƽ Ȱ��ȭ
}


EBTNodeResult::Type UDNHeliMissileAttackTask::ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in)
{
	Super::ExecuteTask(owner_comp_in, NodeMemory_in);

	// ��Ʈ�ѷ�
	auto controller = Cast<ADNAIController>(owner_comp_in.GetAIOwner());
	APawn* self_pawn = controller->GetPawn();

	// ĳ����
	ADNHeliCommonCharacter* self_actor = Cast<ADNHeliCommonCharacter>(self_pawn);

	if (self_actor->get_status_component().Get()->_dead)
	{
		return EBTNodeResult::Failed;
	}

	// Ÿ�� ĳ����
	auto target = controller->get_blackboard()->GetValueAsObject(all_ai_bb_keys::target_actor);
	ADNCommonCharacter* target_character = Cast<ADNCommonCharacter>(target);

	if (nullptr == target)											//Ÿ�� ������ ����
	{
		self_actor->set_idle_animation();


		return EBTNodeResult::Failed;
	}

	if (true == target_character->_status->_dead)					//Ÿ���� �׾������� ����
	{
		controller->get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, nullptr);
		self_actor->set_idle_animation();
		return EBTNodeResult::Failed;
	}

	controller->SetFocus(target_character);		// Ÿ�� �ٶ󺸱�
	self_actor->fire_missile(target_character);			// �̻��� �߻�

	return EBTNodeResult::Succeeded;
}


void UDNHeliMissileAttackTask::TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds)
{
	Super::TickTask(owner_comp_in, NodeMemory_in, DeltaSeconds);

}