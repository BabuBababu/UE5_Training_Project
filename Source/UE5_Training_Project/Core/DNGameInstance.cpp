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

	if (nullptr == _object_manager)
	{
		_object_manager = NewObject<UDNObjectManager>(this, UDNObjectManager::StaticClass());
		_object_manager->initialize();

		UE_LOG(LogTemp, Warning, TEXT("Object_Manager Initialize Succeed"));
	}

	if (nullptr == _sound_manager)
	{
		_sound_manager = NewObject<UDNSoundManager>(this, UDNSoundManager::StaticClass());
		_sound_manager->initialize();

		UE_LOG(LogTemp, Warning, TEXT("Sound_Manager Initialize Succeed"));
	}
	
	if (nullptr == _lobby_npc_manager)
	{
		_lobby_npc_manager = NewObject<UDNLobbyNPCManager>(this, UDNLobbyNPCManager::StaticClass());
		_lobby_npc_manager->initialize();

		UE_LOG(LogTemp, Warning, TEXT("Lobby_NPC_Manager Initialize Succeed"));
	}

	if (nullptr == _quest_manager)
	{
		_quest_manager = NewObject<UDNQuestManager>(this, UDNQuestManager::StaticClass());
		_quest_manager->initialize();

		UE_LOG(LogTemp, Warning, TEXT("QuestManager Initialize Succeed"));
	}


	_is_initialize = true;

}

void UDNGameInstance::Shutdown()
{
	if (false == _is_initialize)
		return;

	Super::Shutdown();

	// UI 매니저
	if (_ui_manager)
	{
		_ui_manager->destroy();
		_ui_manager = nullptr;
	}

	if (_object_manager)
	{
		_object_manager->destroy();
		_object_manager = nullptr;
	}

	if (_sound_manager)
	{
		_sound_manager->destroy();
		_sound_manager = nullptr;
	}

	if (_lobby_npc_manager)
	{
		_lobby_npc_manager->destroy();
		_lobby_npc_manager = nullptr;
	}

	if (_quest_manager)
	{
		_quest_manager->destroy();
		_quest_manager = nullptr;
	}

	UE_LOG(LogTemp, Warning, TEXT("GameInstance Destroy Succeed"));
}

void UDNGameInstance::go_to_combat_level()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("CombatStage"));
}
