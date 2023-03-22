


#include "UE5_Training_Project/AI/DNReportToPlayerTask.h"


// Engine
#include <NavigationSystem.h>
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Vector.h>
#include <BehaviorTree/BlackboardComponent.h>

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// Character
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"
#include "UE5_Training_Project/Character/DNPlayerCharacter.h"

// Component
#include <UE5_Training_Project/Component/DNStatusComponent.h>

// AnimInstance
#include "UE5_Training_Project/Character/Animation/DNLobbyCharacterAnimInstance.h"


// BlackBaord
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"




//
// 플레이어를 바라보고 대화하는 애니메이션 및 자막이 들어가야합니다.
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
	ADNCommonCharacter* self_actor = dynamic_cast<ADNCommonCharacter*>(self_pawn);


	if (self_actor->get_status_component().Get()->_dead)
	{
		return EBTNodeResult::Failed;
	}



	// 플레이어 캐릭터
	auto target = controller->get_blackboard()->GetValueAsObject(all_ai_bb_keys::target_actor);

	ADNCommonCharacter* target_character = Cast<ADNCommonCharacter>(target);


	
	if (nullptr == target)											//플레이어가 없으면 실패
	{
		self_actor->set_idle_animation();


		return EBTNodeResult::Failed;
	}


	if (true == target_character->_status->_dead)					//플레이어가 죽어있으면 실패
	{
		controller->get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, nullptr);
		self_actor->set_idle_animation();
		return EBTNodeResult::Failed;
	}


	controller->SetFocus(target_character);		// 타겟 바라보기

	// 애니메이션 실행
	UDNLobbyCharacterAnimInstance* anim = Cast<UDNLobbyCharacterAnimInstance>(self_actor->_character_skeletal_mesh->GetAnimInstance());


	// 자막 실행


	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Task::Fire"));

	return EBTNodeResult::InProgress;
}

void UDNReportToPlayerTask::TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds)
{
	Super::TickTask(owner_comp_in, NodeMemory_in, DeltaSeconds);

	// 애니메이션 끝났는지 체크
	// 끝났다면 성공 반환
	// return EBTNodeResult::Succeeded;
}