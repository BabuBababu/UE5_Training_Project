


#include "UE5_Training_Project/Actor/Item/DNCommonItem.h"


// Engine
#include <Components/BoxComponent.h>


ADNCommonItem::ADNCommonItem()
{
	// 캐릭터 데이터 테이블 초기화
	static ConstructorHelpers::FObjectFinder<UDataTable> ItemDataObject(TEXT("/Game/Blueprint/Data/DT_DNItemData"));
	if (ItemDataObject.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable Succeed!"));
		_item_datatable = ItemDataObject.Object;
	}
}

void ADNCommonItem::BeginPlay()
{
	Super::BeginPlay();

	add_event();
	item_init();
}


void ADNCommonItem::add_event()
{

}


void ADNCommonItem::remove_event()
{

}

void ADNCommonItem::Tick(float DeltaTime)
{

}


void ADNCommonItem::item_init()
{
	if (nullptr == _item_datatable)
		return;

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

