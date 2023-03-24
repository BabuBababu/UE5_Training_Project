


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
	ADNCommonCharacter* self_actor = Cast<ADNCommonCharacter>(self_pawn);



	if (self_actor->get_status_component().Get()->_dead)
	{
		return EBTNodeResult::Failed;
	}

	// ToDo
	//	일정 시간이 있습니다. (피로도라든가 그런거)
	//  틱 태스크에서 해당 시간을 계속 감소시킵니다.
	//	해당 시간이 0이 되면 true를 반환합니다. 그전까지 inprogress상태
	//  반환하면서 캐릭터 스테이트 및 is_sleep을 false로 바꿉니다.

	//// 침대 바라보기 애니메이션 상태에 따라 변경될수있음
	//UObject* Object = controller->get_blackboard()->GetValueAsObject(all_ai_bb_keys::house_bed);
	//if (nullptr != Object)
	//{
	//	AActor* rest_object = Cast<AActor>(Object);
	//	if (nullptr != rest_object)
	//		controller->SetFocus(rest_object);

	//}


	//// 애니메이션 실행
	//UDNCharacterAnimInstance* anim = Cast<UDNCharacterAnimInstance>(self_actor->_character_skeletal_mesh->GetAnimInstance());
	//if (nullptr != anim)
	//{
	//	anim->play_start_sleep_montage();
	//}


	return EBTNodeResult::InProgress;
}

void UDNWakeUpTask::TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds)
{
	Super::TickTask(owner_comp_in, NodeMemory_in, DeltaSeconds);


}