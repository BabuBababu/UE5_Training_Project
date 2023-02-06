


#include "UE5_Training_Project/Actor/Item/DNCommonItem.h"


// Engine
#include <Components/BoxComponent.h>


void ADNCommonItem::BeginPlay()
{
	Super::BeginPlay();

	add_event();
	item_init();
}


void ADNCommonItem::add_event()
{
	if (nullptr == _box_collision)
		return;

	_box_collision->OnComponentBeginOverlap.AddDynamic(this, &ADNCommonItem::overlap_item_handler);

}


void ADNCommonItem::remove_event()
{

}

void ADNCommonItem::Tick(float DeltaTime)
{

}


void ADNCommonItem::item_init()
{
	TArray<FDNItemData*> data_array;
	_item_datatable->GetAllRows<FDNItemData>("", data_array);

	for (auto& data : data_array)
	{
		if (data->id == _actor_id)
		{
			_item_data = data;
		}
	}
}


void ADNCommonItem::overlap_item_handler(class UPrimitiveComponent* selfComp, class AActor* otherActor, UPrimitiveComponent* otherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnOverlapItemInteraction.Broadcast(*_item_data);

	UE_LOG(LogTemp, Warning, TEXT("Item Overlap actor is %s"), *otherActor->GetName());
}
