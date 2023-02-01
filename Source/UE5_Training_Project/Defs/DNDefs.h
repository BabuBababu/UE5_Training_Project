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
	CS_NONE = 0		UMETA(DisplayName = "None"),	//비어있음
	CS_IDLE			UMETA(DisplayName = "Idle"),	//기본, 총을 들지 않음
	CS_ATTACK		UMETA(DisplayName = "Attack"),	//사격
	CS_RELOAD		UMETA(DisplayName = "Reload"),	//장전
	CS_INTERACTION	UMETA(DisplayName = "Interaction"),	//상호작용
	CS_AIM			UMETA(DisplayName = "Aimming"),	//조준
	CS_ARM			UMETA(DisplayName = "Armed"),	//총을 들고 있음
	CS_DEAD			UMETA(DisplayName = "Dead"),	//사망

	CS_COUNT
};




UENUM(BlueprintType)
enum class E_CHARACTER_INTERACTION : uint8
{
	CI_NONE = 0		UMETA(DisplayName = "None"),	//비어있음
	CI_PICKUP		UMETA(DisplayName = "PickUp"),	//줍기
	CI_CLIMB		UMETA(DisplayName = "Climb"),	//벽오르기
	CI_TALK			UMETA(DisplayName = "Talk"),	//대화하기


	CI_COUNT
};




UENUM(BlueprintType)
enum class E_CHARACTER_POSITION : uint8
{
	CP_NONE = 0		UMETA(DisplayName = "None"),	//비어있음
	CP_RUSH			UMETA(DisplayName = "Rush"),	//전위
	CP_GUARD		UMETA(DisplayName = "Guard"),	//간위
	CP_SUPPORT		UMETA(DisplayName = "Support"),	//후위


	CP_COUNT
};


UENUM(BlueprintType)
enum class E_CHARACTER_MOS : uint8
{
	CM_NONE = 0		UMETA(DisplayName = "None"),	//비어있음
	CM_HG			UMETA(DisplayName = "HG"),		//권총
	CM_SMG			UMETA(DisplayName = "SMG"),		//기관단총
	CM_AR			UMETA(DisplayName = "AR"),		//돌격소총
	CM_SR			UMETA(DisplayName = "SR"),		//저격소총
	CM_SG			UMETA(DisplayName = "SG"),		//샷건


	CM_COUNT
};



UENUM(BlueprintType)
enum class E_CHARACTER_GRADE : uint8
{
	CG_NONE = 0			UMETA(DisplayName = "None"),			//비어있음
	CG_COMMON			UMETA(DisplayName = "Common"),			//1성
	CG_UNCOMMON			UMETA(DisplayName = "UnCommon"),		//2성
	CG_RARE				UMETA(DisplayName = "Rare"),			//3성
	CG_SUPERRARE		UMETA(DisplayName = "SuperRare"),		//4성
	CG_ULTRARARE		UMETA(DisplayName = "UltraRare"),		//5성



	CG_COUNT
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

