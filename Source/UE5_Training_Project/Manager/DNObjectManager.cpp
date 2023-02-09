// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5_Training_Project/Manager/DNObjectManager.h"



void UDNObjectManager::initialize()
{
	_manager_type = E_MANAGER_TYPE::MT_OBJECT_MANAGER;

	
	Super::initialize();
}


void UDNObjectManager::destroy()
{

	Super::destroy();

}