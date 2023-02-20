


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

	ACharacter* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"),Enemy->GetDistanceTo(Player)));


	Cont->get_blackboard()->SetValueAsBool(all_ai_bb_keys::enemy_is_in_melee_range, dog->GetDistanceTo(Player) <= MeleeRange);

	if (all_ai_bb_keys::enemy_is_in_melee_range)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("range is true!"));
	}
}