

#pragma once


// Engine
#include <CoreMinimal.h>
#include <BehaviorTree/BTTaskNode.h>

// Generated
#include "DNHeliMoveToTask.generated.h"

/**
 * 
 */

class ADNHeliCommonCharacter;
class ADNAIController;

UCLASS(Blueprintable)
class UE5_TRAINING_PROJECT_API UDNHeliMoveToTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UDNHeliMoveToTask(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in) override;
	void TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds) override;


	bool is_moving_complete(UBehaviorTreeComponent& owner_comp_in);

public:
	FVector target_location;
	ADNHeliCommonCharacter* self_actor;
	ADNAIController* controller;
};
