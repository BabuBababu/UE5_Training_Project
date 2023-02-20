

#pragma once

// Engine
#include <CoreMinimal.h>
#include <BehaviorTree/BTTaskNode.h>

// Generated
#include "DNChaseEnemyTask.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UE5_TRAINING_PROJECT_API UDNChaseEnemyTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UDNChaseEnemyTask(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
		float _search_radius = 20.f;
};
