#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

// Engine
#include <CoreMinimal.h>
#include <Engine/DataTable.h>

// Actor
#include "UE5_Training_Project/Actor/DNCommonActor.h"
#include "UE5_Training_Project/Actor/Item/DNQuestItem.h"

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// generated
#include "DNQuestData.generated.h"




//
// 원래는 메인 퀘스트 데이터, 서브 퀘스트 데이터 따로 해서 
// 메인 퀘스트 데이터 안에 서브 퀘스트 데이터를 집어넣어줘야하는데 
// 그렇게까지 복잡하게 만들 볼륨이 아니므로 그냥 이렇게 작성했습니다.
//

USTRUCT(Atomic, BlueprintType)
struct FDNQuestData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 퀘스트 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Data")
	E_UI_QUEST_TYPE						quest_type = E_UI_QUEST_TYPE::UQT_NONE;

	// 퀘스트 UID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Data")
	int64								quest_uid = 0;

	// 퀘스트 메인 제목
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Data")
	FString								quest_main_name = TEXT("");

	// 퀘스트 서브 제목
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Data")
	FString								quest_sub_name = TEXT("");

	// 퀘스트 설명
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Data")
	FString								quest_description = TEXT("");

	// 아이템 수집 퀘스트일 경우 사용할 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Request Data")
	int64								quest_need_item_count = 0;

	//  아이템 수집 퀘스트일 경우 사용할 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Request Data")
	TSubclassOf<ADNQuestItem>			quest_item;

	// 지점 이동, 점령, 방어 퀘스트일 경우 사용할 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Request Data")
	TSubclassOf<ADNCommonActor>			quest_location;

	// 목표 제거 퀘스트일 경우 사용할 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Request Data")
	TSubclassOf<ADNCommonCharacter>		quest_eliminate_character;

	// 퀘스트 서브 아이콘 경로
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Data")
	FString								quest_sub_icon_path = TEXT("");





	FDNQuestData& operator=(const FDNQuestData& data)
	{
		quest_type = data.quest_type;
		quest_uid = data.quest_uid;
		quest_main_name = data.quest_main_name;
		quest_sub_name = data.quest_sub_name;
		quest_description = data.quest_description;
		quest_need_item_count = data.quest_need_item_count;
		quest_item = data.quest_item;
		quest_location = data.quest_location;
		quest_eliminate_character = data.quest_eliminate_character;
		quest_sub_icon_path = data.quest_sub_icon_path;

		return *this;
	}

	void reset()
	{
		quest_type = E_UI_QUEST_TYPE::UQT_NONE;
		quest_uid = 0;
		quest_main_name = TEXT("");
		quest_sub_name = TEXT("");
		quest_description = TEXT("");
		quest_need_item_count = 0;
		quest_item = nullptr;
		quest_location = nullptr;
		quest_eliminate_character = nullptr;
		quest_sub_icon_path = TEXT("");
	}
};
