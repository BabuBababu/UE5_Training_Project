


#include "UE5_Training_Project/AI/DNSetTargetTask.h"

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

// BlackBaord
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"

//
// 가드는 미사일 우선 공격
// 그 이외 포지션은 나머지 타겟을 우선 공격
//

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
	
	// 타겟 자체가 배열에 없다면 실패 반환
	if (OBJECT_MANAGER->_enemy_missile_array.IsEmpty() && controller->_target_array.IsEmpty())
	{
		controller->ClearFocus(EAIFocusPriority::Gameplay);
		self_actor->set_idle_animation();
		return EBTNodeResult::Failed;
	}

	// 이미 타겟이 있다면 성공 반환
	if(controller->get_blackboard()->GetValueAsObject(all_ai_bb_keys::target_actor))
		return EBTNodeResult::Succeeded;

	
	if (self_actor->get_character_position() == E_CHARACTER_POSITION::CP_GUARD)		// 가드일 경우
	{
		
		if (set_first_target_missile(self_pawn,_max_distance))
		{
			ADNBossMissile* missile = set_first_target_missile(self_pawn, _max_distance);

			controller->get_blackboard()->SetValueAsBool(all_ai_bb_keys::is_find_target, true);
			controller->get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, missile);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("guard0000000000000000"));
			return EBTNodeResult::Succeeded;
		}

		// 위 조건에서 적합한 미사일이 없다면
		if (controller->_target_array.Num() == 0)		// 저장해둔 적 타겟이 없으면
		{
			controller->get_blackboard()->SetValueAsBool(all_ai_bb_keys::is_find_target, false);
			controller->get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, nullptr);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("guard111111111111"));
			return EBTNodeResult::Failed;
		}
		else
		{

			for (auto& target : controller->_target_array)
			{
				AActor* actor = Cast<AActor>(target);
				if (nullptr == actor)
					return EBTNodeResult::Failed;

				controller->get_blackboard()->SetValueAsBool(all_ai_bb_keys::is_find_target, true);
				controller->get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, target);
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("guard2222222222222"));
				return EBTNodeResult::Succeeded;
			}
		}
		


	}
	else                                                                            // 나머지 포지션일 경우
	{
		if (controller->_target_array.Num() == 0)		// 저장해둔 타겟이 없으면
		{

			if (set_first_target_missile(self_pawn, _max_distance))
			{
				ADNBossMissile* missile = set_first_target_missile(self_pawn, _max_distance);

				controller->get_blackboard()->SetValueAsBool(all_ai_bb_keys::is_find_target, true);
				controller->get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, missile);
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("guard0000000000000000"));
				return EBTNodeResult::Succeeded;
			}


			controller->get_blackboard()->SetValueAsBool(all_ai_bb_keys::is_find_target, false);
			controller->get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, nullptr);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("other111111111111"));
			return EBTNodeResult::Failed;
		}
		else
		{

			for (const auto& target : controller->_target_array)
			{
				if (nullptr != target)
				{
					AActor* actor = Cast<AActor>(target);
					if (nullptr == actor)
						return EBTNodeResult::Failed;

					controller->get_blackboard()->SetValueAsBool(all_ai_bb_keys::is_find_target, true);
					controller->get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, target);
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("other22222222222"));
					return EBTNodeResult::Succeeded;
				}
				
			}
		}
	}


	

	

	return EBTNodeResult::Succeeded;
}




void UDNSetTargetTask::TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds)
{
	Super::TickTask(owner_comp_in, NodeMemory_in, DeltaSeconds);


}

ADNBossMissile* UDNSetTargetTask::set_first_target_missile(APawn* pawn_in, float max_distance_in)
{

	for (auto& missile : OBJECT_MANAGER->_enemy_missile_array)
	{
		// 활성화된 미사일이 존재한다면
		if (missile->_is_active)
		{
			if (max_distance_in > pawn_in->GetDistanceTo(missile))
			{
				return missile;
			}
		}
	}

	// 적합한 미사일이 없다면
	return nullptr;		
}