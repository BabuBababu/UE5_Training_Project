

#pragma once

// Engine
#include <CoreMinimal.h>

// Actor
#include "UE5_Training_Project/Actor/Furniture/DNCommonFurniture.h"

// Generated
#include "DNCommonChair.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNCommonChair : public ADNCommonFurniture
{
	GENERATED_BODY()
public:
	ADNCommonChair();

protected:
	virtual void BeginPlay() override;

	virtual void add_event() override;
	virtual void remove_event() override;

public:
	virtual void Tick(float DeltaTime) override;


};
