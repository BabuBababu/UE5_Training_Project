

#pragma once

// Engine
#include <CoreMinimal.h>
#include <UObject/NoExportTypes.h>

// Data
#include "UE5_Training_Project/Data/DNItemData.h"

// generated
#include "DNEnemyLineTrace.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnETargetLimitAmmoDelegate);

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


public:
	FOnETargetLimitAmmoDelegate OnTargetHit;
};
