

#pragma once

// Engine
#include <CoreMinimal.h>

// Actor
#include "UE5_Training_Project/Actor/DNBullet.h"

// Generated
#include "DNTargetCircleMissile.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNTargetCircleMissile : public ADNBullet
{
	GENERATED_BODY()

public:
	ADNTargetCircleMissile();

protected:
	virtual void BeginPlay() override;

public:
	void Tick(float DeltaTime) override;
	void fire(FVector location_in) override;

	void add_event() override;
	void remove_event() override;

	void init() override;

	virtual void destroy_object();

public:
	void overlap_actor_handler(class UPrimitiveComponent* selfComp, class AActor* otherActor, UPrimitiveComponent* otherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
