

#pragma once

// Engine
#include <CoreMinimal.h>

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// Generated
#include "DNHeliAIController.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNHeliAIController : public ADNAIController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* pawn_in) override;


public:
	void OnTargetDetected(AActor* actor, FAIStimulus const Stimulus) override;
};
