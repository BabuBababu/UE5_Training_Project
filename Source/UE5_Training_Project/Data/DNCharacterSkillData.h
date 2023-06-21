#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

// Engine
#include <CoreMinimal.h>
#include <Engine/DataTable.h>
#include <CameraAnimationSequence.h>

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// generated
#include "DNCharacterSkillData.generated.h"





USTRUCT(Atomic, BlueprintType)
struct FDNCharacterSkillData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 캐릭터 ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	int32							id = -1;
	// 스킬 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	FString                         name = TEXT("");
	// 스킬 쿨타임
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	float							cool_time = 0.f;
	// 스킬 대미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	float							damage_tweak = 0.f;

	// 스킬 방어력 증가
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	float							armor_tweak = 0.f;

	// 스킬 회복 hp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	float							recovery_hp = 0.f;
	// 스킬 요구 SP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	float							sp = 0.f;
	// 스킬 계수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")		// level * level_tweak * damage_tweak 가 최종 대미지가 됩니다.
	float							level_tweak = 0.f;
	// 스킬 레벨
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	int32							level = 0;
	// 스킬 종류
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	E_SKILL_TYPE					type = E_SKILL_TYPE::ST_NONE;

	// 스킬 아이콘 경로
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	FString                         icon_path = TEXT("");
	// 스킬 애니메이션 몽타주 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	TObjectPtr<UAnimMontage>        montage;
	// 스킬 카메라 시퀀서 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Data")
	FString							camera_path = TEXT("");


	FDNCharacterSkillData& operator=(const FDNCharacterSkillData& data)
	{
		id = data.id;
		name = data.name;
		cool_time = data.cool_time;
		damage_tweak = data.damage_tweak;
		armor_tweak = data.armor_tweak;
		recovery_hp = data.recovery_hp;
		sp = data.sp;
		level_tweak = data.level_tweak;
		level = data.level;
		type = data.type;
		icon_path = data.icon_path;
		montage = data.montage;
		camera_path = data.camera_path;

		return *this;
	}

	void reset()
	{
		id = 0;
		name = TEXT("");
		cool_time = 0.f;
		damage_tweak = 0.f;
		armor_tweak = 0.f;
		recovery_hp = 0.f;
		sp = 0.f;
		level_tweak = 0.f;
		level = 0;
		type = E_SKILL_TYPE::ST_NONE;
		icon_path = TEXT("");
		montage = nullptr;
		camera_path = TEXT("");
	}
};