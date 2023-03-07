﻿

#pragma once

// Engine
#include <CoreMinimal.h>
#include <Components/CapsuleComponent.h>

// Character
#include "UE5_Training_Project/Character/DNEnemyCharacter.h"


// Generated
#include "DNShieldEnemyCharacter.generated.h"

/**
 * 
 */

class ADNCommonCharacter;
class ADNCommonShield;

UCLASS()
class UE5_TRAINING_PROJECT_API ADNShieldEnemyCharacter : public ADNEnemyCharacter
{
	GENERATED_BODY()

public:
	ADNShieldEnemyCharacter();

protected:
	void BeginPlay() override;

	void add_event() override;
	void remove_event() override;

	void Tick(float DeltaSeconds) override;


public:
	void fire() override;

private:
	void init_base() override;

private:
	bool	_is_overlap;
	ADNCommonCharacter* _damaged_character;
	ADNCommonShield*	_shield;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* _attack_sword_collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = shield)
	TSubclassOf<ADNCommonShield> _weapon_left_shield;


	

public:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:
	void destroy_object_handler() override;
};