﻿

#pragma once

// Engine
#include <CoreMinimal.h>
#include <UObject/NoExportTypes.h>

// generated
#include "DNEnemyLineTrace.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API UDNEnemyLineTrace : public UObject
{
	GENERATED_BODY()

public:
	UDNEnemyLineTrace();

public:
	UPROPERTY(EditAnywhere, Category = "Particle Effects")
		UParticleSystem* blood_particle;

	UPROPERTY(EditAnywhere, Category = "Particle Effects")
		UParticleSystem* block_particle;

	UPROPERTY(EditAnywhere, Category = "Particle Effects")
		UParticleSystem* fire_particle;
public:
	UFUNCTION(BlueprintCallable)
		void OnFire(ADNCommonCharacter* player_in);
};