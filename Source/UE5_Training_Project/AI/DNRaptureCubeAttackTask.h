

#pragma once

// Engine
#include <CoreMinimal.h>
#include <BehaviorTree/BTTaskNode.h>

// Generated
#include "DNRaptureCubeAttackTask.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UE5_TRAINING_PROJECT_API UDNRaptureCubeAttackTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UDNRaptureCubeAttackTask(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in);
	void TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation Gun", meta = (AllowPrivateAccess = "true"))
	float	_limit_time;


	float	_current_time;

};
