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
    UInputAction* InputCover;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputInterRaction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputCameraRotate;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* IA_Num_1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* IA_Num_2;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* IA_Num_3;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* IA_Num_4;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* IA_Num_5;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* IA_Num_6;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* IA_Num_7;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* IA_Num_8;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* IA_Num_9;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* IA_Q;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* IA_F;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* IA_G;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* IA_H;
};
