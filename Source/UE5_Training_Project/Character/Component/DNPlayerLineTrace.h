

#pragma once

// Engine
#include <CoreMinimal.h>
#include <UObject/NoExportTypes.h>

// Data
#include "UE5_Training_Project/Data/DNItemData.h"

// generated
#include "DNPlayerLineTrace.generated.h"

/**
 * 
 */


class ADNCommonCharacter;
class ADNCommonItem;

 UCLASS(Transient, Blueprintable, HideCategories = AnimInstance, BlueprintType)
class UE5_TRAINING_PROJECT_API UDNPlayerLineTrace : public UObject
{
	GENERATED_BODY()
		
public:
	UDNPlayerLineTrace();

public:
	UPROPERTY(EditAnywhere, Category = "Particle Effects")
		UParticleSystem* blood_particle;

	UPROPERTY(EditAnywhere, Category = "Particle Effects")
		UParticleSystem* block_particle;

	UPROPERTY(EditAnywhere, Category = "Particle Effects")
		UParticleSystem* fire_particle;

public:
	ADNCommonItem* _item;
	bool		   _is_targeted;
public:
	UFUNCTION(BlueprintCallable)
	void OnFire(ADNCommonCharacter* player_in);

	UFUNCTION(BlueprintCallable)
	void OnInteraction(ADNCommonCharacter* player_in);
};
