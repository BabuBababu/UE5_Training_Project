

#pragma once

// Engine
#include <CoreMinimal.h>
#include <UObject/NoExportTypes.h>

// Data
#include "UE5_Training_Project/Data/DNItemData.h"

// generated
#include "DNPlayerLineTrace.generated.h"

/**
 *	 현재 플레이어 및 전술인형(아군)이 공용으로 사용중입니다.
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionLineDelegate, E_UI_INTERACTION_TYPE, type);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTargetLimitAmmoDelegate);


class ADNCommonCharacter;
class ADNEnemyCharacter;
class ADNCommonItem;

 UCLASS(Transient, Blueprintable, HideCategories = AnimInstance, BlueprintType)
class UE5_TRAINING_PROJECT_API UDNPlayerLineTrace : public UObject
{
	GENERATED_BODY()
		
public:
	UDNPlayerLineTrace();


private:
	ADNEnemyCharacter* _temp_character;

public:
	UPROPERTY(EditAnywhere, Category = "Particle Effects")
	UParticleSystem* blood_particle;

	UPROPERTY(EditAnywhere, Category = "Particle Effects")
	UParticleSystem* block_particle;

	UPROPERTY(EditAnywhere, Category = "Particle Effects")
	UParticleSystem* fire_particle;

	UPROPERTY(EditAnywhere, Category = "Particle Effects")
	UParticleSystem* order_move_particle;

public:
	FOnInteractionLineDelegate OnInteractionLinetrace;
	FOnTargetLimitAmmoDelegate OnTargetHit;

public:
	ADNCommonItem* _item;
	bool		   _is_targeted;
public:
	UFUNCTION(BlueprintCallable)
	void OnFire(ADNCommonCharacter* player_in);

	UFUNCTION(BlueprintCallable)
	void OnInteraction(ADNCommonCharacter* player_in);


	UFUNCTION(BlueprintCallable)
	void OnOrder(ADNCommonCharacter* player_in, ADNUnEnemyCharacter* doll_in);

	UFUNCTION(BlueprintCallable)
	void OnAiming(ADNCommonCharacter* player_in);

};
