// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine
#include <CoreMinimal.h>
#include <GameFramework/PlayerController.h>

// Data
#include "UE5_Training_Project/Data/DNInputConfigData.h"


// generated
#include "DNPlayerController.generated.h"

/**
 *  플레이어가 조종하게 될 컨트롤러입니다.
 */

//DECLARE_DYNAMIC_DELEGATE(FJumpInputEvent);


class UInputMappingContext;
class UDNInputConfigData;

UCLASS()
class UE5_TRAINING_PROJECT_API ADNPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADNPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Fire(const FInputActionValue& Value);
	void Reload(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void StopJumping(const FInputActionValue& Value);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UDNInputConfigData* InputActions;


//////////////////////////////////////////////////////////////////////////
// delegate
//////////////////////////////////////////////////////////////////////////



};
