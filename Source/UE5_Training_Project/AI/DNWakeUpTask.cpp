


#include "UE5_Training_Project/AI/DNWakeUpTask.h"



// Engine
#include <NavigationSystem.h>
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Vector.h>
#include <BehaviorTree/BlackboardComponent.h>

// Controller
#include "UE5_Training_Project/Controller/DNLobbyAIController.h"
#include "UE5_Training_Project/Controller/DNPlayerController.h"

// Character
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"
#include "UE5_Training_Project/Character/DNPlayerCharacter.h"

// Component
#include <UE5_Training_Project/Component/DNStatusComponent.h>

// AnimInstance
#include "UE5_Training_Project/Character/Animation/DNCharacterAnimInstance.h"


// BlackBaord
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"

// Manager
#include "UE5_Training_Project/Manager/DNLobbyNPCManager.h"



//
// 
// 캐릭터의 피로도가 0이하가 될 때까지 체크하면서 재우는 태스크입니다.
//


UDNWakeUpTask::UDNWakeUpTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("WakeUpTask");
	bNotifyTick = true;			// 틱 활성화
}

EBTNodeResult::Type UDNWakeUpTask::ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in)
{
	Super::ExecuteTask(owner_comp_in, NodeMemory_in);

	// 컨트롤러
	auto controller = Cast<ADNLobbyAIController>(owner_comp_in.GetAIOwner());
	APawn* self_pawn = controller->GetPawn();


	// 캐릭터
	ADNUnEnemyCharacter* self_actor = Cast<ADNUnEnemyCharacter>(self_pawn);



	if (self_actor->get_status_component().Get()->_dead)
	{
		return EBTNodeResult::Failed;
	}



	return EBTNodeResult::InProgress;
}

void UDNWakeUpTask::TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds)
{
	Super::TickTask(owner_comp_in, NodeMemory_in, DeltaSeconds);


	_rest_left_time += DeltaSeconds;

	if (_rest_left_time >= LOBBY_MANAGER->_resting_time)
	{

		_start_wakeup = true;
		_rest_left_time = 0.f;


		// 일정 시간이 지나면
		if (_start_wakeup)
		{

			// 컨트롤러
			auto controller = Cast<ADNLobbyAIController>(owner_comp_in.GetAIOwner());
			APawn* self_pawn = controller->GetPawn();

			// 캐릭터
			ADNUnEnemyCharacter* self_actor = Cast<ADNUnEnemyCharacter>(self_pawn);

			// 침대 포커스 해제
			controller->ClearFocus(EAIFocusPriority::Gameplay);

			// 애니메이션 실행
			UDNCharacterAnimInstance* anim = Cast<UDNCharacterAnimInstance>(self_actor->_character_skeletal_mesh->GetAnimInstance());
			if (nullptr != anim)
			{
				LOBBY_MANAGER->show_weapon(self_actor);
				anim->play_wakeup_montage();
				_start_wakeup = false;
			}
		}
	}

	
	// 컨트롤러
	auto controller = Cast<ADNLobbyAIController>(owner_comp_in.GetAIOwner());
	APawn* self_pawn = controller->GetPawn();

	// 캐릭터
	ADNUnEnemyCharacter* self_actor = Cast<ADNUnEnemyCharacter>(self_pawn);
	UDNCharacterAnimInstance* anim = Cast<UDNCharacterAnimInstance>(self_actor->_character_skeletal_mesh->GetAnimInstance());
	if (nullptr != anim)
	{
		if (anim->_check_wakeup_ended)
		{
			_is_play_animation = false;
			anim->_check_wakeup_ended = false;

			//일어나기로 변경합니다.			
			controller->get_blackboard()->SetValueAsBool(all_ai_bb_keys::is_sleep, false);
			controller->get_blackboard()->SetValueAsBool(all_ai_bb_keys::is_finish_work, false);
			controller->get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, nullptr);
			controller->_finish_work = false;

			// 각자 역할에 맞게 애님인스턴스 재정리
			if (controller->_ai_type == E_LOBBY_AI_TYPE::LAT_PATROL)
				self_actor->_character_state = E_CHARACTER_STATE::CS_PATROL;
			else if (controller->_ai_type == E_LOBBY_AI_TYPE::LAT_GUARD)
				self_actor->_character_state = E_CHARACTER_STATE::CS_GUARD;
			else if (controller->_ai_type == E_LOBBY_AI_TYPE::LAT_POST)
				self_actor->_character_state = E_CHARACTER_STATE::CS_POST;

			FinishLatentTask(owner_comp_in, EBTNodeResult::Succeeded);		// 끝났다면 성공 반환
		}
	}


}