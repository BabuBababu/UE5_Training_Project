

#pragma once

// Engine
#include <CoreMinimal.h>
#include <UObject/NoExportTypes.h>

// generated
#include "DNPlayerLineTrace.generated.h"

/**
 * 
 */


class ADNCommonCharacter;

 UCLASS(Transient, Blueprintable, HideCategories = AnimInstance, BlueprintType)
class UE5_TRAINING_PROJECT_API UDNPlayerLineTrace : public UObject
{
	GENERATED_BODY()
		
public:
	UDNPlayerLineTrace();

public:
	UPROPERTY(EditAnywhere, Category = "Blood Particle Effects")
		UParticleSystem* blood_particle;

	UPROPERTY(EditAnywhere, Category = "Block Particle Effects")
		UParticleSystem* block_particle;

public:
	UFUNCTION(BlueprintCallable)
	void OnFire(ADNCommonCharacter* player_in);
};
