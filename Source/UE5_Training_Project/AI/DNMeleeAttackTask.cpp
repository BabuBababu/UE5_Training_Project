


#include "UE5_Training_Project/AI/DNMeleeAttackTask.h"


// Engine
#include <NavigationSystem.h>
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Vector.h>
#include <BehaviorTree/BlackboardComponent.h>

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"
#include "UE5_Training_Project/Character/DNEnemycharacter.h"

// Component
#include <UE5_Training_Project/Component/DNStatusComponent.h>

// AnimInstance
#include "UE5_Training_Project/Character/Animation/DNCharacterAnimInstance.h"


// BlackBaord
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"



UDNMeleeAttackTask::UDNMeleeAttackTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("MeleeAttackEnemyTask");
	bNotifyTick = true;			// 틱 활성화
}

EBTNodeResult::Type UDNMeleeAttackTask::ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in)
{
	Super::ExecuteTask(owner_comp_in, NodeMemory_in);

	// 컨트롤러
	auto controller = Cast<ADNAIController>(owner_comp_in.GetAIOwner());
	APawn* self_pawn = controller->GetPawn();

	// 캐릭터
	ADNEnemyCharacter* self_actor = Cast<ADNEnemyCharacter>(self_pawn);


	if (self_actor->get_status_component().Get()->_dead)
	{
		return EBTNodeResult::Failed;
	}



	// 타겟 캐릭터
	auto target = controller->get_blackboard()->GetValueAsObject(all_ai_bb_keys::target_actor);

	ADNCommonCharacter* target_character = dynamic_cast<ADNCommonCharacter*>(target);

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

	if (false == controller->get_blackboard()->GetValueAsBool(all_ai_bb_keys::enemy_is_in_melee_range))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Task::fail"));
		self_actor->set_idle_animation();
		return EBTNodeResult::Failed;
	}


	controller->SetFocus(target_character);		// 타겟 바라보기

	self_actor->_is_fire = true;			// 사격 조건 On
	self_actor->fire();						// 사격
	self_actor->_is_attacking = true;


	// 만약 공격받은 대상의 target actor가 nullptr일 경우 
	// 공격한 캐릭터를 넣어줍니다.
	ADNAIController* ai_controller = Cast<ADNAIController>(target_character->GetController());
	if (nullptr != ai_controller)
	{
		if (nullptr == ai_controller->get_blackboard()->GetValueAsObject(all_ai_bb_keys::target_actor))
		{
			ai_controller->get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, self_actor);
		}
	}



	return EBTNodeResult::Succeeded;		//프로그레스로해야하는데 일단 성공으로 놓고 테스트
}

void UDNMeleeAttackTask::TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds)
{
	Super::TickTask(owner_comp_in, NodeMemory_in, DeltaSeconds);

	//if (!_is_attacking)			//몬스터가 죽거나 뭐 어떤경우에 성공해야할지 고민해봐야함
	//{
	//	FinishLatentTask(owner_comp_in, EBTNodeResult::Succeeded);
	//}
}