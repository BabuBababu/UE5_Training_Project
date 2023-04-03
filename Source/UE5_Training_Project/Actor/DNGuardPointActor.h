

#pragma once

// Engine
#include <CoreMinimal.h>

// Actor
#include "UE5_Training_Project/Actor/DNCommonActor.h"

// Generated
#include "DNGuardPointActor.generated.h"

/**
 * 
 */

UCLASS()
class UE5_TRAINING_PROJECT_API ADNGuardPointActor : public ADNCommonActor
{
	GENERATED_BODY()

public:
	ADNGuardPointActor();

protected:
	virtual void BeginPlay() override;

	virtual void add_event() override;
	virtual void remove_event() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
		int64	_index;

};
