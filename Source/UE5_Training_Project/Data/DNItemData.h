#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

// Engine
#include <CoreMinimal.h>
#include <Engine/DataTable.h>

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// generated
#include "DNItemData.generated.h"





USTRUCT(Atomic, BlueprintType)
struct FDNItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// UID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	int64							id;

	// 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	FString							name = TEXT("");

	// 아이템 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	E_ITEM_TYPE						type = E_ITEM_TYPE::IT_NONE;

	// 아이템 등급
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	E_ITEM_GRADE					grade = E_ITEM_GRADE::IG_NONE;

	// 아이콘 경로
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	FString							item_icon_path = TEXT("");

	// 추가 HP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	float							add_hp;

	// 추가 스테미너
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	float							add_sp;

	// 추가 대미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	float							add_damage;

	// 추가 방어력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	float							add_armor;

	// 아이템 개수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
	int64							count;

	FDNItemData& operator=(const FDNItemData& data)
	{
		id = data.id;
		name = data.name;
		type = data.type;
		grade = data.grade;
		item_icon_path = data.item_icon_path;
		add_hp = data.add_hp;
		add_sp = data.add_sp;
		add_damage = data.add_damage;
		add_armor = data.add_armor;
		count = data.count;
		

		return *this;
	}


};

