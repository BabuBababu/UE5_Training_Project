


#include "UE5_Training_Project/AI/DNBossAttackTask.h"

// Engine
#include <BehaviorTree/BlackboardComponent.h>

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// Component
#include <UE5_Training_Project/Component/DNStatusComponent.h>

// BlackBaord
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"

// Character
#include "UE5_Training_Project/Character/DNCommonBossCharacter.h"


UDNBossAttackTask::UDNBossAttackTask(FObjectInitializer const& object_initializer)
{

	NodeName = TEXT("BossAttackTask");
}


EBTNodeResult::Type UDNBossAttackTask::ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in)
{
	Super::ExecuteTask(owner_comp_in, NodeMemory_in);

	bNotifyTick = true; //틱 태스크 활성화

	// 컨트롤러
	auto controller = Cast<ADNAIController>(owner_comp_in.GetAIOwner());
	APawn* self_pawn = controller->GetPawn();

	// 캐릭터
	ADNCommonBossCharacter* self_actor = Cast<ADNCommonBossCharacter>(self_pawn);

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


		return EBTNodeResult::Failed;
	}

	if (true == target_character->_status->_dead)					//타겟이 죽어있으면 실패
	{
		controller->get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, nullptr);
		self_actor->set_idle_animation();
		return EBTNodeResult::Failed;
	}
	

	if (self_actor->_fire_2_current_time <= 1.f)
	{
		self_actor->fire_2(target_character);			// 쿨타임 없으면 미사일 발사
		return EBTNodeResult::InProgress;
	}
	else if (self_actor->_fire_1_current_time <= 1.f)
	{
		self_actor->fire_1(target_character);			// 쿨타임 있으면 거대 미사일 발사
		return EBTNodeResult::InProgress;
	}
	else
		return EBTNodeResult::InProgress;
}


void UDNBossAttackTask::TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds)
{
	Super::TickTask(owner_comp_in, NodeMemory_in, DeltaSeconds);

	// 공격시 자연스럽게 헤드를 돌림
	
	auto controller = Cast<ADNAIController>(owner_comp_in.GetAIOwner());
	APawn* self_pawn = controller->GetPawn();
	// 타겟 캐릭터
	auto target = controller->get_blackboard()->GetValueAsObject(all_ai_bb_keys::target_actor);
	ADNCommonCharacter* target_character = Cast<ADNCommonCharacter>(target);

	// 캐릭터
	ADNCommonBossCharacter* self_actor = Cast<ADNCommonBossCharacter>(self_pawn);
	self_actor->rotate_head(DeltaSeconds, target_character);

	// 머리 돌리기전과 후를 비교해서 같으면 성공 반환해야할듯
	//FinishLatentTask(owner_comp_in, EBTNodeResult::Succeeded);		
}