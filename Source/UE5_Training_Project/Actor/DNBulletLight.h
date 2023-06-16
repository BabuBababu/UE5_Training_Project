

#pragma once

// Engine
#include <CoreMinimal.h>

// Actor
#include "UE5_Training_Project/Actor/DNBullet.h"

// Generated
#include "DNBulletLight.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNBulletLight : public ADNBullet
{
	GENERATED_BODY()

public:
	ADNBulletLight();

protected:
	virtual void BeginPlay() override;
public:
	void fire(FVector location_in) override;
	virtual void Tick(float DeltaTime) override;
	virtual void active_bullet() override;
	virtual void non_active_bullet() override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Life time")
	float _life_time;


private:
	float _life_current_time;



};
