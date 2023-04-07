


#include "UE5_Training_Project/Actor/Item/DNCommonItem.h"

// Engine
#include <Components/BoxComponent.h>
#include <NiagaraComponent.h>
#include <NiagaraSystem.h>

// Character
#include "UE5_Training_Project/Character/DNPlayerCharacter.h"


ADNCommonItem::ADNCommonItem()
{
	// 캐릭터 데이터 테이블 초기화
	static ConstructorHelpers::FObjectFinder<UDataTable> ItemDataObject(TEXT("/Game/Blueprint/Data/DT_DNItemData"));
	if (ItemDataObject.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable Succeed!"));
		_item_datatable = ItemDataObject.Object;
	}

	_item_niagara_particle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Particle"));
	_item_niagara_particle->SetupAttachment(RootComponent);


}

void ADNCommonItem::BeginPlay()
{
	Super::BeginPlay();

	add_event();
	item_init();
}


void ADNCommonItem::add_event()
{

	ADNPlayerCharacter* player = Cast<ADNPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	player->OnItemPickup.AddDynamic(this, &ADNCommonItem::destroy_item_handler);
}


void ADNCommonItem::remove_event()
{

}

void ADNCommonItem::Tick(float DeltaTime)
{

}


void ADNCommonItem::item_init()
{
	_is_selected = false;

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

	if (IsValid(_spawn_particle))
	{
		if (IsValid(_item_niagara_particle))
		{
			_item_niagara_particle->SetAsset(_spawn_particle);
			_item_niagara_particle->Activate();
		}

	}

}


void ADNCommonItem::destroy_item_handler(ADNCommonItem* actor_in)
{
	if (this != actor_in)
		return;

	UE_LOG(LogTemp, Warning, TEXT("Destroy this Item"));
	Destroy();
}