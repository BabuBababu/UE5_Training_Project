﻿


#include "UE5_Training_Project/AI/DNRaptureResVolitansAttackTask.h"

// Engine
#include <BehaviorTree/BlackboardComponent.h>

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// Component
#include <UE5_Training_Project/Component/DNStatusComponent.h>

// BlackBaord
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"

// Character
#include "UE5_Training_Project/Character/DNRaptureResVolitansCharacter.h"


UDNRaptureResVolitansAttackTask::UDNRaptureResVolitansAttackTask(FObjectInitializer const& object_initializer)
{

	NodeName = TEXT("RaptureResVolitansAttackTask");
}


EBTNodeResult::Type UDNRaptureResVolitansAttackTask::ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in)
{
	Super::ExecuteTask(owner_comp_in, NodeMemory_in);

	bNotifyTick = true; //틱 태스크 활성화

	// 컨트롤러
	auto controller = Cast<ADNAIController>(owner_comp_in.GetAIOwner());
	APawn* self_pawn = controller->GetPawn();

	// 캐릭터
	ADNRaptureResVolitansCharacter* self_actor = Cast<ADNRaptureResVolitansCharacter>(self_pawn);

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

		//return EBTNodeResult::Failed;
	}

	if (true == target_character->_status->_dead)					//타겟이 죽어있으면 실패
	{
		controller->get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, nullptr);
		controller->ClearFocus(EAIFocusPriority::Gameplay);
		self_actor->set_idle_animation();
		//return EBTNodeResult::Failed;
	}
	if (self_actor->_fire_1_current_time <= 0.1f)
	{
		controller->SetFocus(target_character);
		self_actor->fire_1(target_character);			// 미사일 발사
	}

	if (self_actor->_fire_2_current_time <= 0.1f)
	{
		controller->SetFocus(target_character);
		self_actor->fire_2(target_character);			// 미사일 발사
	}

	if (self_actor->_fire_3_current_time <= 2.f)
	{
		controller->SetFocus(target_character);
		self_actor->fire_3(target_character);			// 미사일 발사
	}

	if (false == self_actor->_target_circle_cool_time_start) // 보스어택테스크와는 다름. 비헤이비어트리에서 공격방식이 달라서 그런듯
	{
		self_actor->target_circle_pattern_spawn(target_character);	// 타겟 서클 패턴 스폰
	}

	return EBTNodeResult::Succeeded;
}


void UDNRaptureResVolitansAttackTask::TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds)
{
	Super::TickTask(owner_comp_in, NodeMemory_in, DeltaSeconds);


}