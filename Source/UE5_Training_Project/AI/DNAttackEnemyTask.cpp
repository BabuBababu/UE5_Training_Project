


#include "UE5_Training_Project/AI/DNAttackEnemyTask.h"

// Engine
#include <NavigationSystem.h>
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Vector.h>
#include <BehaviorTree/BlackboardComponent.h>

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// Actor
#include "UE5_Training_Project/Actor/DNBossMissile.h"

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Component
#include <UE5_Training_Project/Component/DNStatusComponent.h>

// AnimInstance
#include "UE5_Training_Project/Character/Animation/DNCharacterAnimInstance.h"


// BlackBaord
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"



UDNAttackEnemyTask::UDNAttackEnemyTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("AttackEnemyTask");
	bNotifyTick = false;			// 틱 비활성화
}

EBTNodeResult::Type UDNAttackEnemyTask::ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in)
{
	Super::ExecuteTask(owner_comp_in, NodeMemory_in);

	// 컨트롤러
	auto controller = Cast<ADNAIController>(owner_comp_in.GetAIOwner());
	APawn* self_pawn = controller->GetPawn();
	
	// 캐릭터
	ADNCommonCharacter* self_actor = Cast<ADNCommonCharacter>(self_pawn);

	
	if (self_actor->get_status_component().Get()->_dead)
	{
		return EBTNodeResult::Failed;
	}

	if (false == self_actor->_is_armed_weapon)						// 무기를 들고 있지않으면 실패
	{
		controller->ClearFocus(EAIFocusPriority::Gameplay);
		self_actor->set_idle_animation();
		return EBTNodeResult::Failed;
	}


	// 사격하려고 봤더니 타겟 액터가 미사일인데 비활성화 된 녀석이다? 그럼 nullptr로 다시 변경
	auto* target = controller->get_blackboard()->GetValueAsObject(all_ai_bb_keys::target_actor);

	ADNBossMissile* missile_check = Cast<ADNBossMissile>(target);
	if (nullptr != missile_check)
	{
		if (false == missile_check->_is_active)
		{
			controller->get_blackboard()->SetValueAsBool(all_ai_bb_keys::is_find_target, false);
			controller->get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, nullptr);
			return EBTNodeResult::Failed;
		}
		
	}



	// 타겟 캐릭터
	ADNCommonCharacter* target_character = Cast<ADNCommonCharacter>(target);
	// 미사일
	ADNBossMissile* missile = Cast<ADNBossMissile>(target);

	if (nullptr == target)											//타겟 없으면 실패
	{
		return EBTNodeResult::Failed;
	}

	if(nullptr == missile && nullptr == target_character)			// 미사일도 캐릭터도 아니라면 실패
		return EBTNodeResult::Failed;

	if (nullptr != target_character)								// 캐릭터라면
	{
		if (true == target_character->_status->_dead)					//타겟이 죽어있으면 실패
		{
			controller->get_blackboard()->SetValueAsBool(all_ai_bb_keys::is_find_target, false);
			controller->get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, nullptr);
			controller->ClearFocus(EAIFocusPriority::Gameplay);
			return EBTNodeResult::Failed;
		}


		controller->SetFocus(target_character);		// 타겟 바라보기

	}

	if (nullptr != missile)											// 미사일이라면
	{
		controller->SetFocus(missile);		// 타겟 바라보기
	}
	

	self_actor->_is_fire = true;			// 사격 조건 On
	self_actor->fire();						// 사격
	self_actor->_is_attacking = true;


		

	return EBTNodeResult::Succeeded;		
}

void UDNAttackEnemyTask::TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds)
{
	Super::TickTask(owner_comp_in, NodeMemory_in, DeltaSeconds);


}