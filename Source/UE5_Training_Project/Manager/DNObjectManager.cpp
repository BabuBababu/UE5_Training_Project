// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5_Training_Project/Manager/DNObjectManager.h"



void UDNObjectManager::initialize()
{
	_manager_type = E_MANAGER_TYPE::MT_OBJECT_MANAGER;
	_location_actor_array.Empty();
	
	Super::initialize();
}


void UDNObjectManager::destroy()
{

	Super::destroy();

}



TObjectPtr<UDNObjectManager> UDNObjectManager::get_object_manager()
{
	TArray<UObject*> object_array;
	GetObjectsOfClass(UDNObjectManager::StaticClass(), object_array);

	if (object_array.Num() > 0)
	{
		return Cast<UDNObjectManager>(object_array[0]);
	}

	return nullptr;
}