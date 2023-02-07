// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5_Training_Project/Core/DNGameInstance.h"

// Engine
#include <Kismet/GameplayStatics.h>






UDNGameInstance::UDNGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	_is_initialize = false;
}

void UDNGameInstance::Init()
{
	Super::Init();

	if (true == _is_initialize)
		return;

	// UI 매니저
	if (nullptr == _ui_manager)
	{
		_ui_manager = NewObject<UDNUIManager>(this, UDNUIManager::StaticClass());
		_ui_manager->initialize();


		UE_LOG(LogTemp, Warning, TEXT("UI_Manager Initialize Succeed"));
	}

}

void UDNGameInstance::Shutdown()
{
	if (false == _is_initialize)
		return;


	// UI 매니저
	if (_ui_manager)
	{
		_ui_manager->destroy();
	}
	_ui_manager = nullptr;

	Super::Shutdown();

	UE_LOG(LogTemp, Warning, TEXT("GameInstance Destroy Succeed"));
}

void UDNGameInstance::go_to_combat_level()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("CombatStage"));
}
