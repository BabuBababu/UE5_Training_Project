// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine
#include <CoreMinimal.h>
#include <Engine/GameInstance.h>

#include "UE5_Training_Project/Manager/DNUIManager.h"
#include "UE5_Training_Project/Manager/DNObjectManager.h"
#include "UE5_Training_Project/Manager/DNSoundManager.h"

// generated
#include "DNGameInstance.generated.h"

/**
 * 
 */

class UDNUIManager;
class UDNObjectManager;
class UDNSoundManager;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UDNGameInstance(const FObjectInitializer& ObjectInitializer);

public:
	virtual void Init() override;
	virtual void Shutdown() override;

public:
	void go_to_combat_level();

private:
	UPROPERTY()
	UDNUIManager* _ui_manager = nullptr;

	UPROPERTY()
	UDNObjectManager* _object_manager = nullptr;

	UPROPERTY()
	UDNSoundManager* _sound_manager = nullptr;

	bool _is_initialize;
};
