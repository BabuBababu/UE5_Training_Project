

#pragma once

// Engine
#include <CoreMinimal.h>

// Actor
#include "UE5_Training_Project/Actor/Item/DNCommonGrenade.h"

// Generated
#include "DNNormalGrenade.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNNormalGrenade : public ADNCommonGrenade
{
	GENERATED_BODY()

public:
	ADNNormalGrenade();

protected:
	virtual void BeginPlay() override;

	virtual void add_event() override;
	virtual void remove_event() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void item_init() override;
};
