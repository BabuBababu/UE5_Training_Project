


#include "UE5_Training_Project/Core/DNLobbyGameState.h"

// Manager
#include "UE5_Training_Project/Manager/DNQuestManager.h"



ADNLobbyGameState::ADNLobbyGameState()
{
	_quest_uid = -1;	// 퀘스트 선택하지 않음 기본 값
}


void ADNLobbyGameState::BeginPlay()
{
	Super::BeginPlay();
}