


#include "UE5_Training_Project/AI/DNMeleeRangeCheckServiceTask.h"

// Engine
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>
#include <Runtime/Engine/Classes/Engine/World.h>
#include <BehaviorTree/BlackboardComponent.h>


#include "UE5_Training_Project/Controller/DNAIController.h"
#include "UE5_Training_Project/Character/DNDogEnemyCharacter.h"
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"



UDNMeleeRangeCheckServiceTask::UDNMeleeRangeCheckServiceTask()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("MeleeRangeCheckServiceTask");
}

void UDNMeleeRangeCheckServiceTask::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(owner_comp, NodeMemory);

	ADNAIController* const Cont = Cast<ADNAIController>(owner_comp.GetAIOwner());
	ADNDogEnemyCharacter* const dog = Cast<ADNDogEnemyCharacter>(Cont->GetPawn());


	ADNCommonCharacter* target = Cast<ADNCommonCharacter>(Cont->get_blackboard()->GetValueAsObject(all_ai_bb_keys::target_actor));
	if (nullptr == target)
		return;
	float temp = dog->GetDistanceTo(target);

	if(temp <= MeleeRange)
		Cont->get_blackboard()->SetValueAsBool(all_ai_bb_keys::enemy_is_in_melee_range, true);
	else
		Cont->get_blackboard()->SetValueAsBool(all_ai_bb_keys::enemy_is_in_melee_range, false);

	if (all_ai_bb_keys::enemy_is_in_melee_range)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Range is : %f"), temp));
	}
}