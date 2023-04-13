


#include "UE5_Training_Project/Core/DNStageGameState.h"

// Manager
#include "UE5_Training_Project/Manager/DNQuestManager.h"



ADNStageGameState::ADNStageGameState()
{
	_quest_uid = -1;	// 퀘스트 선택하지 않음 기본 값
}


void ADNStageGameState::BeginPlay()
{
	Super::BeginPlay();

	if(_quest_uid != -1)
		QUEST_MANAGER->start_quest(_quest_uid);
}