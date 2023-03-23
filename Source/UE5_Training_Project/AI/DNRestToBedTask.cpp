


#include "UE5_Training_Project/AI/DNRestToBedTask.h"


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
// 해당 몽타쥬가 끝났다면 틱에서 체크하고 성공을 반환하도록 합니다.
//


UDNRestToBedTask::UDNRestToBedTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("RestToBedTask");
	bNotifyTick = true;			// 틱 활성화
}

EBTNodeResult::Type UDNRestToBedTask::ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in)
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


	// 침대 바라보기 애니메이션 상태에 따라 변경될수있음
	UObject* Object = controller->get_blackboard()->GetValueAsObject(all_ai_bb_keys::house_bed);
	if (nullptr != Object)
	{
		AActor* rest_object = Cast<AActor>(Object);
		if(nullptr != rest_object)
			controller->SetFocus(rest_object);		

	}


	// 애니메이션 실행
	UDNCharacterAnimInstance* anim = Cast<UDNCharacterAnimInstance>(self_actor->_character_skeletal_mesh->GetAnimInstance());
	if (nullptr != anim)
	{
		anim->play_sleep_montage();
		_is_play_animation = true;
	}


	// 자막 실행


	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Task::Fire"));

	return EBTNodeResult::InProgress;
}

void UDNRestToBedTask::TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds)
{
	Super::TickTask(owner_comp_in, NodeMemory_in, DeltaSeconds);

	// 애니메이션 끝났는지 체크
	if (_is_play_animation)
	{
		// 컨트롤러
		auto controller = Cast<ADNLobbyAIController>(owner_comp_in.GetAIOwner());
		APawn* self_pawn = controller->GetPawn();

		// 캐릭터
		ADNCommonCharacter* self_actor = Cast<ADNCommonCharacter>(self_pawn);
		UDNCharacterAnimInstance* anim = Cast<UDNCharacterAnimInstance>(self_actor->_character_skeletal_mesh->GetAnimInstance());
		if (nullptr != anim)
		{
			if (anim->_check_sleep_ended)
			{
				_is_play_animation = false;
				anim->_check_sleep_ended = false;
				self_actor->SetActorLocation( self_actor->_character_skeletal_mesh->GetSocketLocation("Hips"));
				
				FinishLatentTask(owner_comp_in, EBTNodeResult::Succeeded);		// 끝났다면 성공 반환
			}
		}
	}

}