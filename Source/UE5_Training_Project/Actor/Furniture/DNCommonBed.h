

#pragma once

// Engine
#include <CoreMinimal.h>

// Actor
#include "UE5_Training_Project/Actor/Furniture/DNCommonFurniture.h"

// Generated
#include "DNCommonBed.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNCommonBed : public ADNCommonFurniture
{
	GENERATED_BODY()

public:
	ADNCommonBed();

protected:
	virtual void BeginPlay() override;

	virtual void add_event() override;
	virtual void remove_event() override;

public:
	virtual void Tick(float DeltaTime) override;


};
