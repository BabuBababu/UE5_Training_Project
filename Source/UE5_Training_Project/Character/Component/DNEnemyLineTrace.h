

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
	UPROPERTY(EditAnywhere, Category = "Blood Particle Effects")
		UParticleSystem* blood_particle;

	UPROPERTY(EditAnywhere, Category = "Block Particle Effects")
		UParticleSystem* block_particle;

public:
	UFUNCTION(BlueprintCallable)
		void OnFire(ADNCommonCharacter* player_in);
};
