

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DNHeliFindPlayerPosTask.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UE5_TRAINING_PROJECT_API UDNHeliFindPlayerPosTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UDNHeliFindPlayerPosTask(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in);


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SearchFromPlayer", meta = (AllowPrivateAccess = "true"))
		float _search_radius = 2000.f;
};
