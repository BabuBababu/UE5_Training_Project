

#pragma once

// Engine
#include <CoreMinimal.h>

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNLobbyAIController.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNLobbyAIController : public ADNAIController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* pawn_in) override;


public:
	void OnTargetDetected(AActor* actor, FAIStimulus const Stimulus) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIType)
	E_LOBBY_AI_TYPE _ai_type = E_LOBBY_AI_TYPE::LAT_NONE;
};
