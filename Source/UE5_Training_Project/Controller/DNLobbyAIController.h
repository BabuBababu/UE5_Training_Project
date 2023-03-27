

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

class ADNCommonCharacter;

UCLASS()
class UE5_TRAINING_PROJECT_API ADNLobbyAIController : public ADNAIController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* pawn_in) override;
	virtual void OnUnPossess() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	void OnTargetDetected(AActor* actor, FAIStimulus const Stimulus) override;

	void add_event(ADNCommonCharacter* character_in) override;
	void remove_event(ADNCommonCharacter* character_in) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	E_LOBBY_AI_TYPE _ai_type = E_LOBBY_AI_TYPE::LAT_NONE;

public:
	float _current_time = 0.f;
	bool  _finish_work = false;

};
