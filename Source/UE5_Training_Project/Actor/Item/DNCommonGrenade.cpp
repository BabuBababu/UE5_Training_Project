


#include "UE5_Training_Project/Actor/Item/DNCommonGrenade.h"


ADNCommonGrenade::ADNCommonGrenade()
{


	_item_type = E_ITEM_TYPE::IT_GRENADE;
}

void ADNCommonGrenade::BeginPlay()
{
	Super::BeginPlay();

}



void ADNCommonGrenade::add_event()
{
	Super::add_event();

}



void ADNCommonGrenade::remove_event()
{
	Super::remove_event();

}



void ADNCommonGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ADNCommonGrenade::item_init()
{
	Super::item_init();

	_is_fire = false;
}
