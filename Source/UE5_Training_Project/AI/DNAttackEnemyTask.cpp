


#include "UE5_Training_Project/AI/DNAttackEnemyTask.h"

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

// AnimInstance
#include "UE5_Training_Project/Character/Animation/DNCharacterAnimInstance.h"


// BlackBaord
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"



UDNAttackEnemyTask::UDNAttackEnemyTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("AttackEnemyTask");
	bNotifyTick = true;			// 틱 활성화
}

EBTNodeResult::Type UDNAttackEnemyTask::ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in)
{
	Super::ExecuteTask(owner_comp_in, NodeMemory_in);

	// 컨트롤러
	auto controller = Cast<ADNAIController>(owner_comp_in.GetAIOwner());
	APawn* self_pawn = controller->GetPawn();
	
	// 캐릭터
	ADNCommonCharacter* self_actor = dynamic_cast<ADNCommonCharacter*>(self_pawn);

	
	if (self_actor->get_status_component().Get()->_dead)
	{
		return EBTNodeResult::Failed;
	}



		// 타겟 캐릭터
		auto target = controller->get_blackboard()->GetValueAsObject(all_ai_bb_keys::target_actor);

		ADNCommonCharacter* target_character = dynamic_cast<ADNCommonCharacter*>(target);

		UDNCharacterAnimInstance* anim = dynamic_cast<UDNCharacterAnimInstance*>(self_actor->_character_skeletal_mesh->GetAnimInstance());


		if (nullptr == target)											//타겟 없으면 실패
		{
			self_actor->set_idle_animation();


			return EBTNodeResult::Failed;
		}


		if (true == target_character->_status->_dead)					//타겟이 죽어있으면 실패
		{
			controller->get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor,nullptr);
			controller->ClearFocus(EAIFocusPriority::Gameplay);
			self_actor->set_idle_animation();
			return EBTNodeResult::Failed;
		}

		

		if (false == self_actor->_is_armed_weapon)						// 무기를 들고 있지않으면 실패
		{
			controller->ClearFocus(EAIFocusPriority::Gameplay);
			self_actor->set_idle_animation();
			return EBTNodeResult::Failed;
		}


		controller->SetFocus(target_character);		// 타겟 바라보기

		self_actor->_is_fire = true;			// 사격 조건 On
		self_actor->fire();						// 사격
		self_actor->_is_attacking = true;

		return EBTNodeResult::Succeeded;		
}

void UDNAttackEnemyTask::TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds)
{
	Super::TickTask(owner_comp_in, NodeMemory_in, DeltaSeconds);


}