

#pragma once

#include "CoreMinimal.h"

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Item
#include "UE5_Training_Project/Actor/Item/DNQuestItem.h"

// Manager
#include "UE5_Training_Project/Manager/DNQuestManager.h"

/**
 *	원래 구현 방식은
 *	몬스터 종류별로 아이템 테이블을 만들어서 드랍목록을 만들고
 *  해당 목록의 모든 아이템들을 한번씩 돌려서 확률에 맞게 스폰이 되도록 하려고 했지만
 * 그 정도까지 작정(?)하고 만들 것은 아니므로 아이템 별로 메서드 호출 하는 방식으로 작성합니다.
 * 
 */



class UE5_TRAINING_PROJECT_API DNItemSpawnSystem
{
public:
	static void spawn_item_with_random(ADNCommonCharacter* character_in, const FVector& location_in, const FRotator& rotation_in)
	{
		int result = FMath::FRandRange(1.0, 100.0);

		if (result == 1.0)		//일단 확률 1%로 설정
		{
			spawn_quest_item(character_in, location_in, rotation_in);
		}

	}


	static void spawn_quest_item(ADNCommonCharacter* character_in, const FVector & location_in, const FRotator & rotation_in)
	{
		if(nullptr != QUEST_MANAGER->_quest_item_class)
			ADNQuestItem* quest_item = character_in->GetWorld()->SpawnActor<ADNQuestItem>(QUEST_MANAGER->_quest_item_class, location_in, rotation_in);
		
	}
};
