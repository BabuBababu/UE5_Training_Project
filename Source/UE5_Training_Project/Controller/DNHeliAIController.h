

#pragma once

// Engine
#include <CoreMinimal.h>

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// Generated
#include "DNHeliAIController.generated.h"

/**
 *		버그있어서 DNAIController를 BP 인스턴스화해서 따로 사용하는 중
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
