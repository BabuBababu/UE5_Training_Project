

#pragma once

// Engine
#include <CoreMinimal.h>
#include <BehaviorTree/BTTaskNode.h>

#include "DNAirRaptrueCheckMoveToTask.generated.h"

/**
 * 
 */

class ADNAirRaptureCharacter;
class ADNAIController;


UCLASS(Blueprintable)
class UE5_TRAINING_PROJECT_API UDNAirRaptrueCheckMoveToTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UDNAirRaptrueCheckMoveToTask(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in);
	void TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds);
	bool is_moving_complete(UBehaviorTreeComponent& owner_comp_in);


public:
	FVector target_location;
	
};
