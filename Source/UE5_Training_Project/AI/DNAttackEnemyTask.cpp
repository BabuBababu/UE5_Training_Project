


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
	_is_attacking = false;
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
		return EBTNodeResult::Failed;

	AActor* target_actor = dynamic_cast<AActor*>(target);
	controller->SetFocus(target_actor);		// 조준! 지금은 발견한 처음만 조준할듯
	self_actor->fire();						// 사격!
	_is_attacking = true;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attack Now"));


	if (nullptr != anim)
		anim->OnAttackEnd.AddLambda([this]()->void {_is_attacking = false; });		//람다로 델리게이트 추가

	return EBTNodeResult::InProgress;
}

void UDNAttackEnemyTask::TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds)
{
	Super::TickTask(owner_comp_in, NodeMemory_in, DeltaSeconds);

	if (!_is_attacking)
	{
		FinishLatentTask(owner_comp_in, EBTNodeResult::Succeeded);
	}
}