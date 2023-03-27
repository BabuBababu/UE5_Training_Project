


#include "UE5_Training_Project/AI/DNReportToPlayerTask.h"


// Engine
#include <NavigationSystem.h>
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Vector.h>
#include <BehaviorTree/BlackboardComponent.h>

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"
#include "UE5_Training_Project/Controller/DNPlayerController.h"

// Character
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"
#include "UE5_Training_Project/Character/DNPlayerCharacter.h"

// Component
#include <UE5_Training_Project/Component/DNStatusComponent.h>

// AnimInstance
#include "UE5_Training_Project/Character/Animation/DNCharacterAnimInstance.h"

// Manager
#include "UE5_Training_Project/Manager/DNLobbyNPCManager.h"

// BlackBaord
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"




//
// 당직부관을 바라보고 대화하는 애니메이션 및 자막이 들어가야합니다.
// 해당 몽타쥬가 끝났다면 틱에서 체크하고 성공을 반환하도록 합니다.
//


UDNReportToPlayerTask::UDNReportToPlayerTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("ReportToPlayerTask");
	bNotifyTick = true;			// 틱 활성화
}

EBTNodeResult::Type UDNReportToPlayerTask::ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in)
{
	Super::ExecuteTask(owner_comp_in, NodeMemory_in);

	// 컨트롤러
	auto controller = Cast<ADNAIController>(owner_comp_in.GetAIOwner());
	APawn* self_pawn = controller->GetPawn();

	// 캐릭터
	ADNUnEnemyCharacter* self_actor = Cast<ADNUnEnemyCharacter>(self_pawn);


	if (self_actor->get_status_component().Get()->_dead)
	{
		return EBTNodeResult::Failed;
	}

	for (auto& doll : LOBBY_MANAGER->_post_doll_array)
	{
		controller->SetFocus(doll.Value);		// 타겟 바라보기
	}



	// 애니메이션 실행
	UDNCharacterAnimInstance* anim = Cast<UDNCharacterAnimInstance>(self_actor->_character_skeletal_mesh->GetAnimInstance());
	if (nullptr != anim)
	{
		LOBBY_MANAGER->hide_weapon(self_actor);
		anim->play_salute_montage();
		//_is_play_animation = true;
	}


	// 자막 실행
	// 나는 이렇게 보고 했다요~

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Task::Fire"));

	return EBTNodeResult::InProgress;
}

void UDNReportToPlayerTask::TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds)
{
	Super::TickTask(owner_comp_in, NodeMemory_in, DeltaSeconds);


	// 컨트롤러
	auto controller = Cast<ADNAIController>(owner_comp_in.GetAIOwner());
	APawn* self_pawn = controller->GetPawn();

	// 캐릭터
	ADNCommonCharacter* self_actor = Cast<ADNCommonCharacter>(self_pawn);
	UDNCharacterAnimInstance* anim = Cast<UDNCharacterAnimInstance>(self_actor->_character_skeletal_mesh->GetAnimInstance());
	if (nullptr != anim)
	{
		if (anim->_check_salute_ended)
		{
			_is_play_animation = false;
			anim->_check_salute_ended = false;
			FinishLatentTask(owner_comp_in, EBTNodeResult::Succeeded);		// 끝났다면 성공 반환
		}
	}

	// 애니메이션 끝났는지 체크
	/*if (_is_play_animation)
	{
		
	}*/
	
}