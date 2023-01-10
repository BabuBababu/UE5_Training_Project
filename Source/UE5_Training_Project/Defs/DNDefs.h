// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


// Engine
#include <CoreMinimal.h>

// generated
#include "DNDefs.generated.h"



/**
 *  현재 프로젝트에 필요한 대부분의 정의를 담은 헤더파일이에요!
 */



UENUM(BlueprintType)
enum class E_CHARACTER_TYPE : uint8
{
	CT_NONE = 0		UMETA(DisplayName = "None"),
	CT_PLAYER		UMETA(DisplayName = "Player"),
	CT_GRIFFIN		UMETA(DisplayName = "Griffin"),
	CT_ENEMY		UMETA(DisplayName = "Enemy"),

	CT_COUNT
};




UENUM(BlueprintType)
enum class E_CHARACTER_STATE : uint8
{
	CS_NONE = 0		UMETA(DisplayName = "None"),
	CS_IDLE			UMETA(DisplayName = "Idle"),
	CS_ATTACK		UMETA(DisplayName = "Attack"),
	CS_WALK			UMETA(DisplayName = "Walk"),
	CS_Sprint		UMETA(DisplayName = "Sprint"),
	CS_RELOAD		UMETA(DisplayName = "Reload"),

	CS_COUNT
};






UENUM(BlueprintType)
enum class E_UI_HUD_TYPE : uint8
{
	UHT_NONE = 0		UMETA(DisplayName = "None"),
	UHT_LOBBY_HUD		UMETA(DisplayName = "LobbyHUD"),
	UHT_COMBAT_HUD		UMETA(DisplayName = "CombatHUD"),

	UHT_COUNT
};






UENUM(BlueprintType)
enum class E_UI_LAYER_TYPE : uint8
{
	ULT_NONE = 0			UMETA(DisplayName = "None"),

	ULT_PANEL_LAYER			UMETA(DisplayName = "PanelLayer"),


	ULT_COUNT
};






UENUM(BlueprintType)
enum class E_GAME_MODE_TYPE : uint8
{
	GMT_NONE = 0			UMETA(DisplayName = "None"),
	GMT_LOBBY_MODE			UMETA(DisplayName = "LobbyMode"),
	GMT_COMBAT_MODE			UMETA(DisplayName = "CombatMode"),


	GMT_COUNT
};

