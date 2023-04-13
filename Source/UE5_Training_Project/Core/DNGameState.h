

#pragma once

// Engine
#include <CoreMinimal.h>
#include <GameFramework/GameStateBase.h>

// Generated
#include "DNGameState.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNGameState : public AGameStateBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	bool _is_completed;					// 미션 클리어
	bool _is_failed;					// 미션 실패
};
