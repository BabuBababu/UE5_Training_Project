

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBaseManager.h"

// Generated
#include "DNQuestManager.generated.h"

/**
 * 
 */


#define QUEST_MANAGER			UDNObjectManager::get_quest_manager()


class ADNQuestItem;
class ADNPlayerCharacter;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNQuestManager : public UDNBaseManager
{
	GENERATED_BODY()

public:
	void initialize() override;
	void destroy() override;


public:
	static TObjectPtr<UDNQuestManager> get_quest_manager();


public:
	TObjectPtr<ADNPlayerCharacter>	 _player;

	TArray<ADNQuestItem*>	_quest_item_array;
};
