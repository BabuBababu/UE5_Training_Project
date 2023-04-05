

#pragma once


// Engine
#include <CoreMinimal.h>
#include <NiagaraSystem.h>
#include <NiagaraFunctionLibrary.h>

// Item
#include "UE5_Training_Project/Actor/Item/DNCommonItem.h"

// Generated
#include "DNQuestItem.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNQuestItem : public ADNCommonItem
{
	GENERATED_BODY()
public:
	ADNQuestItem();

protected:
	void BeginPlay() override;

	void add_event() override;
	void remove_event() override;

public:
	void Tick(float DeltaTime) override;

public:
	void item_init() override;

public:
	UPROPERTY(EditAnywhere, Category = "Particle Effects")					//아이템 파티클
	UNiagaraSystem* _spawn_particle;
};
