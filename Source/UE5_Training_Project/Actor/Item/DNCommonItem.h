

#pragma once

// Engine
#include <CoreMinimal.h>
#include <NiagaraSystem.h>
#include <NiagaraFunctionLibrary.h>

// Actor
#include "UE5_Training_Project/Actor/DNCommonActor.h"

// Data
#include "UE5_Training_Project/Data/DNItemData.h"

// Generated
#include "DNCommonItem.generated.h"



/**
 * 
 */

class UNiagaraComponent;

UCLASS()
class UE5_TRAINING_PROJECT_API ADNCommonItem : public ADNCommonActor
{
	GENERATED_BODY()
public:
	ADNCommonItem();

protected:
	virtual void BeginPlay() override;

	virtual void add_event() override;
	virtual void remove_event() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void item_init();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<UNiagaraComponent> _item_niagara_particle;


	UPROPERTY(EditAnywhere, Category = "Particle Effects")					//아이템 파티클
	UNiagaraSystem* _spawn_particle;


public:
	//데이터
	UDataTable* _item_datatable;
	FDNItemData* _item_data;
	E_ITEM_TYPE _item_type = E_ITEM_TYPE::IT_NONE;

	bool _is_selected;

public:
	UFUNCTION()
	void destroy_item_handler(ADNCommonItem* actor_in);

};
