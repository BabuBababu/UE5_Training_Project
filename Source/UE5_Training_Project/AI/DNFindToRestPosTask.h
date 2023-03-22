

#pragma once

// Engine
#include <CoreMinimal.h>
#include <BehaviorTree/BTTaskNode.h>

// Generated
#include "DNFindToRestPosTask.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UE5_TRAINING_PROJECT_API UDNFindToRestPosTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UDNFindToRestPosTask(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in);


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SearchFromPlayer", meta = (AllowPrivateAccess = "true"))
		float _search_radius = 50.f;
};
