


#include "UE5_Training_Project/AI/DNMeleeRangeCheckServiceTask.h"

// Engine
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>
#include <Runtime/Engine/Classes/Engine/World.h>
#include <BehaviorTree/BlackboardComponent.h>


#include "UE5_Training_Project/Controller/DNAIController.h"
#include "UE5_Training_Project/Character/DNDogEnemyCharacter.h"
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"



//
//		모든 캐리겉의 근접 공격 사거리 체크용이지만 현재 적군만 이 서비스를 사용하기위해 작성되었습니다.
//


UDNMeleeRangeCheckServiceTask::UDNMeleeRangeCheckServiceTask()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("MeleeRangeCheckServiceTask");
}

void UDNMeleeRangeCheckServiceTask::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(owner_comp, NodeMemory);

	ADNAIController* const Cont = Cast<ADNAIController>(owner_comp.GetAIOwner());
	ADNEnemyCharacter* const melee_enemy = Cast<ADNEnemyCharacter>(Cont->GetPawn());


	ADNCommonCharacter* target = Cast<ADNCommonCharacter>(Cont->get_blackboard()->GetValueAsObject(all_ai_bb_keys::target_actor));
	if (nullptr == target)
		return;
	float temp = melee_enemy->GetDistanceTo(target);

	if(temp <= MeleeRange)
		Cont->get_blackboard()->SetValueAsBool(all_ai_bb_keys::enemy_is_in_melee_range, true);
	else
		Cont->get_blackboard()->SetValueAsBool(all_ai_bb_keys::enemy_is_in_melee_range, false);

}