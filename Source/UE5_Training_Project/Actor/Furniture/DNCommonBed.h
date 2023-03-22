

#pragma once

// Engine
#include <CoreMinimal.h>

// Actor
#include "UE5_Training_Project/Actor/DNCommonActor.h"

// Generated
#include "DNCommonBed.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNCommonBed : public ADNCommonActor
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

public:
	E_FURNITURE_TYPE _furniture_type = E_FURNITURE_TYPE::FT_NONE;		//인터렉션 구분용

};
