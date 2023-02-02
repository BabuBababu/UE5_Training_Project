// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


// Engine
#include <CoreMinimal.h>

// GameMode
#include "UE5_Training_Project/GameMode/DNGameModeBase.h"

// generated
#include "DNStageGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNStageGameMode : public ADNGameModeBase
{
	GENERATED_BODY()
public:
	ADNStageGameMode();


protected:
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
