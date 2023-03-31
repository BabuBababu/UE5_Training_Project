// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine
#include <CoreMinimal.h>
#include <GameFramework/PlayerController.h>

// Data
#include "UE5_Training_Project/Data/DNInputConfigData.h"

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// generated
#include "DNPlayerController.generated.h"

/**
 *  플레이어가 조종하게 될 컨트롤러입니다.
 */

//DECLARE_DYNAMIC_DELEGATE(FJumpInputEvent);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSquadPositionDelegate, int32, squad_inex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSquadPositionStopDelegate);

class UInputMappingContext;
class UDNInputConfigData;
class ADNPlayerCharacter;

UCLASS()
class UE5_TRAINING_PROJECT_API ADNPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADNPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	 void Move(const FInputActionValue& Value);
	 void Sprint(const FInputActionValue& Value);
	 void StopSprint(const FInputActionValue& Value);
	 void Look(const FInputActionValue& Value);
	 void Fire(const FInputActionValue& Value);
	 void StopFire(const FInputActionValue& Value);
	 void Reload(const FInputActionValue& Value);
	 void Jump(const FInputActionValue& Value);
	 void StopJumping(const FInputActionValue& Value);
	 void Armed(const FInputActionValue& Value);
	 void Crouch(const FInputActionValue& Value);
	 void Cover(const FInputActionValue& Value);
	 void Aiming(const FInputActionValue& Value);
	 void Knife(const FInputActionValue& Value);
	 void Throw(const FInputActionValue& Value);
	 void StopAiming(const FInputActionValue& Value);
	 void Interaction(const FInputActionValue& Value);
	 void CameraRotate(const FInputActionValue& Value);
	 void StopCameraRotate(const FInputActionValue& Value);
	

	 void OpenWorkSchedule(const FInputActionValue& Value);

	template<E_INPUT_KEY Key>
	void SelectCharacter(const FInputActionValue& Value);

	template<E_INPUT_KEY Key>
	void ActiveSkill(const FInputActionValue& Value);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;


public:
	TSubclassOf<UCameraShakeBase> get_camera_shake() const { return CameraShake; };

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UDNInputConfigData* InputActions;

	// 카메라 셰이크
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Shake")
	TSubclassOf<UCameraShakeBase> CameraShake;



private:
	bool		_selected_first;
	int32		_selected_num_first;
	int32		_selected_num_second;
	bool		_open_widget;

	ADNPlayerCharacter* _owner;


//////////////////////////////////////////////////////////////////////////
// delegate
//////////////////////////////////////////////////////////////////////////
public:
	FOnSquadPositionDelegate	OnSquadPosition;
	FOnSquadPositionStopDelegate OnStopAnimation;



};
