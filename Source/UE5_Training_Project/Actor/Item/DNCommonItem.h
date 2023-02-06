

#pragma once

// Engine
#include <CoreMinimal.h>

// Actor
#include "UE5_Training_Project/Actor/DNCommonActor.h"

// Data
#include "UE5_Training_Project/Data/DNItemData.h"

// Generated
#include "DNCommonItem.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemDelegate, FDNItemData, data);

/**
 * 
 */


UCLASS()
class UE5_TRAINING_PROJECT_API ADNCommonItem : public ADNCommonActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void add_event() override;
	virtual void remove_event() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	void item_init();


public:
	FOnItemDelegate		OnOverlapItemInteraction;

public:
	//데이터
	UDataTable* _item_datatable;
	FDNItemData* _item_data;
	E_ITEM_TYPE _item_type = E_ITEM_TYPE::IT_NONE;


public:
	UFUNCTION()
	void overlap_item_handler(class UPrimitiveComponent* selfComp, class AActor* otherActor, UPrimitiveComponent* otherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
