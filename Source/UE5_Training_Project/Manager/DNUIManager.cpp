// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5_Training_Project/Manager/DNUIManager.h"

// Manager
#include "UE5_Training_Project/UI/Manager/DNWidgetManager.h"




void UDNUIManager::init_manager()
{
	_manager_type = E_UI_MANAGER_TYPE::UMT_UI_MANAGER;

	if (_widget_manager == nullptr)
	{
		_widget_manager = NewObject<UDNWidgetManager>(this, UDNWidgetManager::StaticClass());
		_widget_manager->initialize();

		UE_LOG(LogTemp, Warning, TEXT("WidgetManager Initialize Succeed"));
	}

}


void UDNUIManager::destroy_manager()
{
	if (_widget_manager != nullptr)
	{
		_widget_manager->destroy();

		_widget_manager = nullptr;
	}

}



TObjectPtr<UDNUIManager> UDNUIManager::get_ui_manager()
{
	TArray<UObject*> object_array;
	GetObjectsOfClass(UDNUIManager::StaticClass(), object_array);

	if (object_array.Num() > 0)
	{
		return Cast<UDNUIManager>(object_array[0]);
	}

	return nullptr;
}