

#pragma once

// Engine
#include <CoreMinimal.h>

// Actor
#include "UE5_Training_Project/Actor/Item/DNCommonItem.h"

// Generated
#include "DNCommonGrenade.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNCommonGrenade : public ADNCommonItem
{
	GENERATED_BODY()

public:
	ADNCommonGrenade();

protected:
	virtual void BeginPlay() override;

	virtual void add_event() override;
	virtual void remove_event() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void item_init() override;


public:
	bool	_is_fire;
};
