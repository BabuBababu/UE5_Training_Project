

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBaseManager.h"

// Data
#include "UE5_Training_Project/Data/DNQuestData.h"

// Generated
#include "DNQuestManager.generated.h"

/**
 * 
 */


#define QUEST_MANAGER			UDNQuestManager::get_quest_manager()


class ADNQuestItem;
class ADNPlayerCharacter;


UCLASS()
class UE5_TRAINING_PROJECT_API UDNQuestManager : public UDNBaseManager
{
	GENERATED_BODY()
public:
	UDNQuestManager();

public:
	void initialize() override;
	void destroy() override;


public:
	static TObjectPtr<UDNQuestManager> get_quest_manager();

	void start_quest(int64 quest_uid_in);			// 이걸 게임모드에다 박을지 어디다가 박을지
	void init_data(int64 quest_uid_in);

public:
	TObjectPtr<ADNPlayerCharacter>	 _player;
	UDataTable*						 _quest_datatable;
	FDNQuestData*					 _quest_data;


	// 아이템 수집
	TSubclassOf<ADNQuestItem>		 _quest_item_class;
	int64							 _current_item_count;
	int64							 _request_item_count;

	// 목표 지점
	TSubclassOf<ADNCommonActor>		 _target_location;

	// 목표 액터
	TSubclassOf<ADNCommonCharacter>  _target_actor;




};
