

#pragma once

// Engine
#include <CoreMinimal.h>
#include <BehaviorTree/Services/BTService_BlackboardBase.h>

// Generated
#include "DNMeleeRangeCheckServiceTask.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UE5_TRAINING_PROJECT_API UDNMeleeRangeCheckServiceTask : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UDNMeleeRangeCheckServiceTask();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
	float MeleeRange = 40.f;
};
