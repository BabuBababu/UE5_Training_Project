﻿

#pragma once

// Engine
#include <CoreMinimal.h>
#include <GameFramework/PlayerController.h>

// Data
#include "UE5_Training_Project/Data/DNInputConfigData.h"

// Generated
#include "DNLobbyController.generated.h"

/**
 *	로비에서 캐릭터 선택할 때 사용하게될 컨트롤러입니다.
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDNSelectEvent, bool, selected);


class UInputMappingContext;
class UDNInputConfigData;
class ADNPlayerCharacter;
class ADNPlayerController;
class ADNStageHUD;

UCLASS()
class UE5_TRAINING_PROJECT_API ADNLobbyController : public APlayerController
{
	GENERATED_BODY()

public:
	ADNLobbyController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;


public:
	void OnMouseClicked();


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UDNInputConfigData* InputActions;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameMode")
	TSubclassOf<ADNPlayerCharacter> _change_character;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameMode")
	TSubclassOf<ADNPlayerController> _change_controller;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameMode")
	TSubclassOf<ADNStageHUD> _change_hud;

public:
	UPROPERTY()
	FDNSelectEvent	OnSelected;

private:
	ADNPlayerCharacter* _lobby_character;

public:
	UFUNCTION()
	void change_controller_character_handler();
};
