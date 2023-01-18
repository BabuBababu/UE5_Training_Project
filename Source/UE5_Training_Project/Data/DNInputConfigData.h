// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine
#include <CoreMinimal.h>
#include <Engine/DataAsset.h>
#include <EnhancedInput/Public/InputAction.h>

// Generated
#include "DNInputConfigData.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API UDNInputConfigData : public UDataAsset
{
	GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputMove;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputLook;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputFire;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputReload;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputJump;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputCrouch;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputSprint;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputAiming;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputArmed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputInterRaction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputCameraRotate;

};
