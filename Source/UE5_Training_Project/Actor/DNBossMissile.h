

#pragma once

// Engine
#include <CoreMinimal.h>

// Actor
#include "UE5_Training_Project/Actor/DNBullet.h"

// Generated
#include "DNBossMissile.generated.h"

/**
 * 
 */

class USplineComponent;

UCLASS()
class UE5_TRAINING_PROJECT_API ADNBossMissile : public ADNBullet
{
	GENERATED_BODY()

public:
	ADNBossMissile();

protected:
	virtual void BeginPlay() override;

public:
	void Tick(float DeltaTime) override;

	void add_event() override;
	void remove_event() override;

	void init() override;

public:
	// 메쉬
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Move)
	TObjectPtr<USplineComponent> _spline_component;
};
