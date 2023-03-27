

#pragma once

// Engine
#include <CoreMinimal.h>
#include <BehaviorTree/BTTaskNode.h>

// Generated
#include "DNLobbyAttackEnemyTask.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UE5_TRAINING_PROJECT_API UDNLobbyAttackEnemyTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UDNLobbyAttackEnemyTask(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in);
	void TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds);
};
