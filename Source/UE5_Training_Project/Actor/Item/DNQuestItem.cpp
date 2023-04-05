


#include "UE5_Training_Project/Actor/Item/DNQuestItem.h"

// Engine
#include <particles/ParticleSystem.h>
#include <NiagaraComponent.h>



ADNQuestItem::ADNQuestItem()
{
	_item_type = E_ITEM_TYPE::IT_QUEST;
}

void ADNQuestItem::BeginPlay()
{
	Super::BeginPlay();

}


void ADNQuestItem::add_event()
{
	Super::add_event();
}


void ADNQuestItem::remove_event()
{
	Super::remove_event();
}

void ADNQuestItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ADNQuestItem::item_init()
{
	Super::item_init();
}