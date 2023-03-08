#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

// Engine
#include <CoreMinimal.h>
#include <Engine/DataTable.h>

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// generated
#include "DNCharacterData.generated.h"





USTRUCT(Atomic, BlueprintType)
struct FDNCharacterStatusData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	float							hp=0.f;
	// 공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	float							damage=0.f;
	// 방어력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	float							armor=0.f;
	// 장탄 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	int64							max_ammo=0;

	// 장전 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	float							reload_speed = 0.f;

	// 사격 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	float							fire_speed = 0.f;


	// 병과
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	E_CHARACTER_MOS					mos = E_CHARACTER_MOS::CM_NONE;
	// 추천 포지션
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	E_CHARACTER_POSITION			recommend_position = E_CHARACTER_POSITION::CP_NONE;
	// 캐릭터 등급
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	E_CHARACTER_GRADE				grade = E_CHARACTER_GRADE::CG_NONE;
	// 레벨업시 오르는 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	float							hp_up=0.f;
	// 레벨업시 오르는 공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	float							damage_up=0.f;
	// 레벨업시 오르는 방어력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	float							armor_up=0.f;


	FDNCharacterStatusData& operator=(const FDNCharacterStatusData& data)
	{
		hp = data.hp;
		damage = data.damage;
		armor = data.armor;
		max_ammo = data.max_ammo;
		reload_speed = data.reload_speed;
		fire_speed = data.fire_speed;
		mos = data.mos;
		recommend_position = data.recommend_position;
		grade = data.grade;
		hp_up = data.hp_up;
		damage_up = data.damage_up;
		armor_up = data.armor_up;

		return *this;
	}


};


USTRUCT(Atomic, BlueprintType)
struct FDNCharacterMentalData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 침착성
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Mental Data")
	int64			composure = 0;
	// 적극성
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Mental Data")
	int64			positiveness = 0;
	// 도덕성
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Mental Data")
	int64			morality = 0;
	// 호감도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Mental Data")
	int64			friendship = 0;

	FDNCharacterMentalData& operator=(const FDNCharacterMentalData& data)
	{
		composure = data.composure;
		positiveness = data.positiveness;
		morality = data.morality;
		friendship = data.friendship;

		return *this;
	}
};




USTRUCT(Atomic, BlueprintType)
struct FDNCharacterDialogData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog Data")
		int64							character_id = 0;										// 캐릭터 ID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog Data")
		FString							gain = TEXT("");										// 캐릭터 획득

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog Data")
		FString							rein_force = TEXT("");									// 캐릭터 강화

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog Data")
		FString							go_out = TEXT("");										// 캐릭터 방출

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog Data")
		FString							encounter = TEXT("");									// 캐릭터 적 만남

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog Data")
		FString							attack = TEXT("");										// 캐릭터 적 공격

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog Data")
		FString							reload = TEXT("");										// 캐릭터 장전

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog Data")
		FString							ordered = TEXT("");										// 캐릭터 명령 응답

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog Data")
		FString							un_ordered = TEXT("");									// 캐릭터 명령 취소

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog Data")
		FString							skill_1 = TEXT("");										// 캐릭터 스킬 1

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog Data")
		FString							skill_2 = TEXT("");										// 캐릭터 스킬 2

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog Data")
		FString							worry = TEXT("");										// 지휘관 걱정

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog Data")
		FString							dead = TEXT("");										// 캐릭터 사망

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog Data")
		FString							lobby_1 = TEXT("");										// 캐릭터 로비 대화 1

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog Data")
		FString							lobby_2 = TEXT("");										// 캐릭터 로비 대화 2

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog Data")
		FString							lobby_3 = TEXT("");										// 캐릭터 로비 대화 3

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog Data")
		FString							lobby_4 = TEXT("");										// 캐릭터 로비 대화 4

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog Data")
		FString							lobby_5 = TEXT("");										// 캐릭터 로비 대화 5


	FDNCharacterDialogData& operator=(const FDNCharacterDialogData& data)
	{
		gain = data.gain;
		rein_force = data.rein_force;
		go_out = data.go_out;
		encounter = data.encounter;
		attack = data.attack;
		reload = data.reload;
		ordered = data.ordered;
		un_ordered = data.un_ordered;
		skill_1 = data.skill_1;
		skill_2 = data.skill_2;
		worry = data.worry;
		dead = data.dead;
		lobby_1 = data.lobby_1;
		lobby_2 = data.lobby_2;
		lobby_3 = data.lobby_3;
		lobby_4 = data.lobby_4;
		lobby_5 = data.lobby_5;


		return *this;
	}
};




USTRUCT(Atomic, BlueprintType)
struct FDNEXPTableData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EXP Data")		//해당 레벨
	int64			level = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EXP Data")		//필요 경험치
	int64			exp = 0;

};











USTRUCT(Atomic, BlueprintType)
struct FDNCharacterData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	int64							character_id = 0;												// 캐릭터 ID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	FString							character_name = TEXT("");										// 캐릭터 이름

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	FDNCharacterStatusData			character_status_data;											// 캐릭터 스테이터스 데이터

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	FDNCharacterMentalData			character_mental_data;											//  캐릭터 멘탈 데이터

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	FDNCharacterDialogData			character_dialog_data;											//  캐릭터 다이얼로그 데이터

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	FString			character_main_image_path = TEXT("");											//  캐릭터 메인 이미지

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	FString			character_dead_image_path = TEXT("");											//  캐릭터 사망 이미지

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	FString			character_portrait_image_path = TEXT("");										//  캐릭터 프로필 이미지

	FDNCharacterData& operator=(const FDNCharacterData& data)
	{
		character_id = data.character_id;
		character_name = data.character_name;
		character_status_data = data.character_status_data;
		character_mental_data = data.character_mental_data;
		character_dialog_data = data.character_dialog_data;
		character_main_image_path = data.character_main_image_path;
		character_dead_image_path = data.character_dead_image_path;
		character_portrait_image_path = data.character_portrait_image_path;


		return *this;
	}
};





USTRUCT(Atomic, BlueprintType)
struct FDNCharacterPositionData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position Data")
		FVector						rush_7;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position Data")
		FVector						rush_8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position Data")
		FVector						rush_9;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position Data")
		FVector						guard_4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position Data")
		FVector						guard_6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position Data")
		FVector						support_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position Data")
		FVector						support_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position Data")
		FVector						support_3;
};


