

#pragma once

// Engine
#include <CoreMinimal.h>
#include <Components/SphereComponent.h>

// Character
#include "UE5_Training_Project/Character/DNEnemyCharacter.h"

// Generated
#include "DNDogEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNDogEnemyCharacter : public ADNEnemyCharacter
{
	GENERATED_BODY()

public:
	ADNDogEnemyCharacter();

public:
	void BeginPlay() override;

	void add_event() override;
	void remove_event() override;

	void fire() override;

private:
	void init_base() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* AttackHead;


public:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
