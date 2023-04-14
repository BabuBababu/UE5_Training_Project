

#pragma once

// Engine
#include <CoreMinimal.h>

// Core
#include "UE5_Training_Project/Core/DNGameState.h"

// Generated
#include "DNLobbyGameState.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNLobbyGameState : public ADNGameState
{
	GENERATED_BODY()
public:
	ADNLobbyGameState();

protected:
	void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quest)
	int64		_quest_uid;
};
