// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


// Engine
#include <CoreMinimal.h>

// generated
#include "DNDefs.generated.h"



/**
 *  현재 프로젝트에 필요한 대부분의 정의를 담은 헤더파일이에요!
 */






 //////////////////////////////////////////////////////////
 //
 //  Character
 //
 //////////////////////////////////////////////////////////

UENUM(BlueprintType)
enum class E_CHARACTER_TYPE : uint8
{
	CT_NONE = 0		UMETA(DisplayName = "None"),
	CT_PLAYER		UMETA(DisplayName = "Player"),
	CT_GRIFFIN		UMETA(DisplayName = "Griffin"),
	CT_HELI			UMETA(DisplayName = "HeliCoptor"),
	CT_ENEMY		UMETA(DisplayName = "Enemy"),

	CT_COUNT
};



UENUM(BlueprintType)
enum class E_CHARACTER_SPAWN_LEVEL_TYPE : uint8
{
	CSLT_NONE = 0	UMETA(DisplayName = "None"),
	CSLT_LOBBY		UMETA(DisplayName = "Lobby"),
	CSLT_STAGE		UMETA(DisplayName = "Stage"),

	CT_COUNT
};



UENUM(BlueprintType)
enum class E_CHARACTER_STATE : uint8
{
	CS_NONE = 0		UMETA(DisplayName = "None"),					//비어있음
	CS_IDLE			UMETA(DisplayName = "Idle"),					//기본, 총을 들지 않음
	CS_ATTACK		UMETA(DisplayName = "Attack"),					//사격
	CS_RELOAD		UMETA(DisplayName = "Reload"),					//장전
	CS_INTERACTION	UMETA(DisplayName = "Interaction"),				//상호작용
	CS_AIM			UMETA(DisplayName = "Aimming"),					//조준
	CS_ARM			UMETA(DisplayName = "Armed"),					//총을 들고 있음
	CS_COVER		UMETA(DisplayName = "Cover"),					//커버 모드
	CS_DEAD			UMETA(DisplayName = "Dead"),					//사망
	CS_SLEEP		UMETA(DisplayName = "Sleep"),					//수면
	CS_REST			UMETA(DisplayName = "Rest"),					//휴식
	CS_POST			UMETA(DisplayName = "Post"),					//당직
	CS_PATROL		UMETA(DisplayName = "Patrol"),					//순찰
	CS_GUARD		UMETA(DisplayName = "Guard"),					//가드
	CS_CREATING		UMETA(DisplayName = "Creating"),				//생산중


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
enum class E_ENEMY_TYPE : uint8
{
	ET_NONE = 0			UMETA(DisplayName = "None"),				//비어있음
	ET_MELEE			UMETA(DisplayName = "Melee"),				//근접 공격 몬스터
	ET_MELEE_SHIELD		UMETA(DisplayName = "Melee Shield"),		//근접 방패 몬스터
	ET_RANGER_AR		UMETA(DisplayName = "Ranger AR"),			//AR 사격 몬스터
	ET_RANGER_LC		UMETA(DisplayName = "Ranger LC"),			//LC 사격 몬스터
	ET_BOSS				UMETA(DisplayName = "Boss"),				//보스


	CG_COUNT
};











//////////////////////////////////////////////////////////
//
//  System
//
//////////////////////////////////////////////////////////
UENUM(BlueprintType)
enum class E_GAME_MODE_TYPE : uint8
{
	GMT_NONE = 0			UMETA(DisplayName = "None"),
	GMT_LOBBY_MODE			UMETA(DisplayName = "LobbyMode"),
	GMT_COMBAT_MODE			UMETA(DisplayName = "CombatMode"),


	GMT_COUNT
};




UENUM()
enum class E_MANAGER_TYPE : uint8
{
	MT_NONE = 0,
	MT_UI_MANAGER,
	MT_WIDGET_MANAGER,
	MT_OBJECT_MANAGER,
	MT_SOUND_MANAGER,
	MT_LOBBY_NPC_MANAGER,

	MT_COUNT
};



//////////////////////////////////////////////////////////
//
//  UI
//
//////////////////////////////////////////////////////////



UENUM()
enum class E_UI_HUD_TYPE : uint8
{
	UHT_NONE = 0,
	UHT_INTRO,
	UHT_LOBBY_HUD,
	UHT_COMBAT_HUD,

	UHT_COUNT
};






UENUM()
enum class E_UI_LAYER_TYPE : uint8
{

	ULT_NONE,

	// HUD 패널(체력바, 스킬슬롯 ...)
	ULT_HUD,
	// 알림 패널(지역 입장 정보 ...)
	ULT_NOTICE,
	// 각종 팝업(인벤토리, 장비창 ...)
	ULT_CONTENT,
	// 시스템 팝업(인게임 경고창 ...)
	ULT_SYSTEM,
	// 로그인 페이지
	ULT_INTRO,
	// 캐릭터 선택 페이지
	ULT_SELECT_CHARACTER,
	// 메뉴 페이지
	ULT_MENU,

	// 테스트 
	ULT_COUNT
};



UENUM()
enum class E_UI_GAUGE_TYPE
{
	UGT_NONE,

	UGT_HP,
	UGT_MP,
	UGT_SP,
	UGT_CAST
};



// 사용할지는 미지수
UENUM()
enum class E_UI_GAUGE_STATE
{
	UGS_NONE,

	UGS_HIDE,
	UGS_CLOSE_SHOW,
	UGS_OPEN_SHOW,

	UGT_TEST
};


UENUM()
enum class E_UI_PANEL_TYPE
{
	UPT_NONE,

	UPT_MINIMAP,
	UPT_INTERACTION,
	UPT_SKILL,
	UPT_ITEM,
	UPT_MENU,
	UPT_QUEST,
	UPT_COMBAT,					 //플레이어 패널
	UPT_TARGET_INFORMATION,
	UPT_QUICK_SLOT,
	UPT_SQUAD,
	UPT_DAMAGE_INDICATOR,
	UPT_COMMENT,				//대사
	UPT_PORTRAIT,				//초상화 컷신
	UPT_CROSSHAIR,
	UPT_CHARACTER_SELECT		//캐릭터 선택
};


UENUM()
enum class E_UI_WIDGET_TYPE
{
	UWT_NONE

	
};



UENUM()
enum class E_UI_INTERACTION_TYPE : uint8
{
	UIT_NONE = 0,
	UIT_ITEM,
	UIT_VEHICLE,
	UIT_NPC,

	UIT_COUNT
};



UENUM()
enum class E_UI_BUTTON_STATE : uint8
{
	UBS_NONE = 0,
	UBS_NORMAL,
	UBS_HOVERED,
	UBS_UNHOVERED,
	UBS_PRESSED,
	UBS_RELEASED,
	UBS_DISABLED,

	UBS_COUNT
};


//////////////////////////////////////////////////////////
//
//  Actor
//
//////////////////////////////////////////////////////////
UENUM(BlueprintType)
enum class E_ACTOR_TYPE : uint8
{
	AT_NONE = 0		UMETA(DisplayName = "None"),			//비어있음
	AT_WALL			UMETA(DisplayName = "Wall"),			//벽
	AT_ITEM			UMETA(DisplayName = "Item"),			//아이템
	AT_SHIELD		UMETA(DisplayName = "Shield"),			//쉴드
	AT_VEHICLE		UMETA(DisplayName = "Vehicle"),			//탈것
	AT_FURNITURE	UMETA(DisplayName = "Furniture"),		//가구
	AT_NPC			UMETA(DisplayName = "NPC"),				//NPC

	AT_COUNT
};


UENUM(BlueprintType)
enum class E_ITEM_TYPE : uint8
{
	IT_NONE = 0				UMETA(DisplayName = "None"),		//비어있음
	IT_AMMO					UMETA(DisplayName = "Ammo"),		//총알
	IT_GRENADE				UMETA(DisplayName = "Grenade"),		//수류탄
	IT_HELMET				UMETA(DisplayName = "Helmet"),		//헬멧
	IT_ARMOR				UMETA(DisplayName = "Armor"),		//갑옷
	IT_GLOVE				UMETA(DisplayName = "Glove"),		//장갑
	IT_BOOTS				UMETA(DisplayName = "Boots"),		//신발
	IT_BACK_PACK			UMETA(DisplayName = "BackPack"),	//가방
	IT_WEAPON_ADD_ON_1		UMETA(DisplayName = "add1"),		//무기 부착물 1
	IT_WEAPON_ADD_ON_2		UMETA(DisplayName = "add2"),		//무기 부착물 2
	IT_WEAPON_ADD_ON_3		UMETA(DisplayName = "add3"),		//무기 부착물 3
	
	IT_COUNT
};



UENUM(BlueprintType)
enum class E_ITEM_GRADE : uint8
{
	IG_NONE = 0			UMETA(DisplayName = "None"),			//비어있음
	IG_COMMON			UMETA(DisplayName = "Common"),			//1성
	IG_UNCOMMON			UMETA(DisplayName = "UnCommon"),		//2성
	IG_RARE				UMETA(DisplayName = "Rare"),			//3성
	IG_SUPERRARE		UMETA(DisplayName = "SuperRare"),		//4성
	IG_ULTRARARE		UMETA(DisplayName = "UltraRare"),		//5성



	IG_COUNT
};


UENUM(BlueprintType)
enum class E_FURNITURE_TYPE : uint8
{
	FT_NONE = 0		UMETA(DisplayName = "None"),			//없음
	FT_BED			UMETA(DisplayName = "Bed"),				//침대
	FT_CHAIR		UMETA(DisplayName = "Chair"),			//의자
	FT_COMPUTER		UMETA(DisplayName = "Computer"),		//작전 참가용 컴퓨터


	FT_COUNT
};

UENUM()
enum class E_DAMAGE_TYPE : uint8
{
	DT_NONE = 0,
	DT_NORMAL,		//일반 대미지
	DT_WEAK,		//약점 대미지
	DT_CRITICAL,	//크리티컬
	DT_RESIST,		//저항 대미지 (반감 대미지)

	DT_COUNT
};

//////////////////////////////////////////////////////////
//
//  Sound
//
//////////////////////////////////////////////////////////

UENUM()
enum class E_FIRE_TYPE : uint8
{
	FT_NONE = 0,
	FT_MAIN,		//메인 공격
	FT_SUB,		//서브 공격

	FT_COUNT
};




UENUM()
enum class E_SOUND_TYPE : uint8
{
	ST_NONE = 0,
	ST_BGM,					//BGM
	ST_EFFECT,				//Effect
	ST_UI,					//UI

	ST_COUNT
};


//////////////////////////////////////////////////////////
//
//  Input
//
//////////////////////////////////////////////////////////


UENUM(BlueprintType)
enum class E_INPUT_KEY : uint8
{
	// 1
	IK_1						UMETA(DisplayName = "1"),
	// 2
	IK_2						UMETA(DisplayName = "2"),
	// 3
	IK_3						UMETA(DisplayName = "3"),
	// 4
	IK_4						UMETA(DisplayName = "4"),
	// 5
	IK_5						UMETA(DisplayName = "5"),
	// 6
	IK_6						UMETA(DisplayName = "6"),
	// 7
	IK_7						UMETA(DisplayName = "7"),
	// 8
	IK_8						UMETA(DisplayName = "8"),
	// 9
	IK_9						UMETA(DisplayName = "9"),
	// 0
	IK_0						UMETA(DisplayName = "0"),
	// `
	IK_TILDE					UMETA(DisplayName = "`"),
	// Q
	IK_Q						UMETA(DisplayName = "Q")
};




//////////////////////////////////////////////////////////
//
//  AI Order
//
//////////////////////////////////////////////////////////



UENUM(BlueprintType)
enum class E_ORDER_TYPE : uint8
{

	OT_NONE						UMETA(DisplayName = "None"),		//명령없음
	OT_MOVEHOLD					UMETA(DisplayName = "MoveAndHold"),	//해당 위치 이동 및 사수
	OT_ATTACK					UMETA(DisplayName = "Attack")		//강제 공격

};



UENUM(BlueprintType)
enum class E_LOBBY_AI_TYPE : uint8
{

	LAT_NONE					UMETA(DisplayName = "None"),		//없음
	LAT_PATROL					UMETA(DisplayName = "Patrol"),		//패트롤 (순찰 근무)
	LAT_GUARD					UMETA(DisplayName = "Guard"),		//가드   (입초 근무)
	LAT_POST					UMETA(DisplayName = "Post"),		//당직 부관
	LAT_REST					UMETA(DisplayName = "Rest"),		//전투 가능 ( 근무 투입은 하지 않음)
	LAT_CITIZEN					UMETA(DisplayName = "Citizen")		//민간인

};
