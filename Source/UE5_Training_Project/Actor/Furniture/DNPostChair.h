

#pragma once

// Engine
#include <CoreMinimal.h>

// Actor
#include "UE5_Training_Project/Actor/Furniture/DNCommonChair.h"

// Generated
#include "DNPostChair.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNPostChair : public ADNCommonChair
{
	GENERATED_BODY()
public:
	ADNPostChair();

protected:
	virtual void BeginPlay() override;

	virtual void add_event() override;
	virtual void remove_event() override;

public:
	virtual void Tick(float DeltaTime) override;
};
