


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

// AnimInstance
#include "UE5_Training_Project/Character/Animation/DNCharacterAnimInstance.h"


// BlackBaord
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"



UDNAttackEnemyTask::UDNAttackEnemyTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("AttackEnemyPosTask");
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
	
	// 타겟 캐릭터
	auto target = controller->get_blackboard()->GetValueAsObject(all_ai_bb_keys::target_actor);

	UDNCharacterAnimInstance* anim = dynamic_cast<UDNCharacterAnimInstance*>(self_actor->_character_skeletal_mesh->GetAnimInstance());

	
	if (nullptr == target)					//타겟 없으면 실패
	{
		self_actor->set_idle_animation();
		

		return EBTNodeResult::Failed;
	}

	if (false == self_actor->_is_armed_weapon) // 무기를 들고 있지않으면 실패
	{
		self_actor->set_idle_animation();

		return EBTNodeResult::Failed;
	}

	//장전해야하면 실패

	AActor* target_actor = dynamic_cast<AActor*>(target);
	controller->SetFocus(target_actor);		// 타겟 바라보기
	if (false == self_actor->_is_attacking)
	{
		self_actor->_is_fire = true;			// 사격 조건 On
		self_actor->fire();						// 사격
		self_actor->_is_attacking = true;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attack Now"));


	//if (nullptr != anim)
	//	anim->OnAttackEnd.AddLambda([self_actor]()->void {self_actor->_is_attacking = false; });		//람다로 델리게이트 추가하는 방법



	return EBTNodeResult::Succeeded;		//프로그레스로해야하는데 일단 성공으로 놓고 테스트
}

void UDNAttackEnemyTask::TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds)
{
	Super::TickTask(owner_comp_in, NodeMemory_in, DeltaSeconds);

	//if (!_is_attacking)			//몬스터가 죽거나 뭐 어떤경우에 성공해야할지 고민해봐야함
	//{
	//	FinishLatentTask(owner_comp_in, EBTNodeResult::Succeeded);
	//}
}