﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "UE5_Training_Project/Controller/DNPlayerController.h"

// Engine
#include "Kismet/GameplayStatics.h"
#include <GameFramework/CharacterMovementComponent.h>

// GameMode
#include "UE5_Training_Project/GameMode/DNGameModeBase.h"

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"


// EnhancedInput
#include "EnhancedInput/Public/InputMappingContext.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "EnhancedInput/Public/InputActionValue.h"


// Character
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"


ADNPlayerController::ADNPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}


void ADNPlayerController::BeginPlay()
{
	Super::BeginPlay();
	

}

void ADNPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ADNPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADNPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	// Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	// Get the EnhancedInputComponent
	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(InputComponent);

	// Bind the actions

	// Completed : 눌렀다 뗐을 때, Triggered : 누르고 있을 때 
	PEI->BindAction(InputActions->InputMove, ETriggerEvent::Triggered, this, &ADNPlayerController::Move);
	PEI->BindAction(InputActions->InputLook, ETriggerEvent::Triggered, this, &ADNPlayerController::Look);
	
	PEI->BindAction(InputActions->InputJump, ETriggerEvent::Triggered, this, &ADNPlayerController::Jump);
	PEI->BindAction(InputActions->InputJump, ETriggerEvent::Completed, this, &ADNPlayerController::StopJumping);
	PEI->BindAction(InputActions->InputFire, ETriggerEvent::Triggered, this, &ADNPlayerController::Fire);
	PEI->BindAction(InputActions->InputFire, ETriggerEvent::Completed, this, &ADNPlayerController::StopFire);
	PEI->BindAction(InputActions->InputReload, ETriggerEvent::Completed, this, &ADNPlayerController::Reload);
	PEI->BindAction(InputActions->InputAiming, ETriggerEvent::Triggered, this, &ADNPlayerController::Aiming);
	PEI->BindAction(InputActions->InputAiming, ETriggerEvent::Completed, this, &ADNPlayerController::StopAiming);
	PEI->BindAction(InputActions->InputArmed, ETriggerEvent::Completed, this, &ADNPlayerController::Armed);
	PEI->BindAction(InputActions->InputCrouch, ETriggerEvent::Completed, this, &ADNPlayerController::Crouch);
	PEI->BindAction(InputActions->InputSprint, ETriggerEvent::Triggered, this, &ADNPlayerController::Sprint);
	PEI->BindAction(InputActions->InputSprint, ETriggerEvent::Completed, this, &ADNPlayerController::StopSprint);
	
	PEI->BindAction(InputActions->InputInterRaction, ETriggerEvent::Completed, this, &ADNPlayerController::Interaction);

	PEI->BindAction(InputActions->InputCameraRotate, ETriggerEvent::Triggered, this, &ADNPlayerController::CameraRotate);
	PEI->BindAction(InputActions->InputCameraRotate, ETriggerEvent::Completed, this, &ADNPlayerController::StopCameraRotate);
	
}


void ADNPlayerController::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();


	// find out which way is forward
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// add movement 
	GetCharacter()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetCharacter()->AddMovementInput(RightDirection, MovementVector.X);
}


void ADNPlayerController::Sprint(const FInputActionValue& Value)
{
	ADNCommonCharacter* character = dynamic_cast<ADNCommonCharacter*>(GetCharacter());
	character->sprint();
	UE_LOG(LogTemp, Warning, TEXT("Sprint"));
}

void ADNPlayerController::StopSprint(const FInputActionValue& Value)
{
	ADNCommonCharacter* character = dynamic_cast<ADNCommonCharacter*>(GetCharacter());
	character->stop_sprint();
	UE_LOG(LogTemp, Warning, TEXT("StopSprint"));
}

void ADNPlayerController::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	

	// add yaw and pitch input to controller
	GetCharacter()->AddControllerYawInput(LookAxisVector.X);
	GetCharacter()->AddControllerPitchInput(LookAxisVector.Y);
}

void ADNPlayerController::Jump(const FInputActionValue& Value)
{
	GetCharacter()->Jump();
	UE_LOG(LogTemp, Warning, TEXT("Jump"));
}

void ADNPlayerController::StopJumping(const FInputActionValue& Value)
{
	GetCharacter()->StopJumping();
	UE_LOG(LogTemp, Warning, TEXT("StopJumping"));
}

void ADNPlayerController::Fire(const FInputActionValue& Value)
{
	ADNCommonCharacter* character = dynamic_cast<ADNCommonCharacter*>(GetCharacter());

	if (character == nullptr)
		return;

	character->fire();

	UE_LOG(LogTemp, Warning, TEXT("Fire"));
}


void ADNPlayerController::StopFire(const FInputActionValue& Value)
{
	ADNCommonCharacter* character = dynamic_cast<ADNCommonCharacter*>(GetCharacter());

	if (character == nullptr)
		return;

	character->stop_fire();
	UE_LOG(LogTemp, Warning, TEXT("StopFire"));
}


void ADNPlayerController::Reload(const FInputActionValue& Value)
{
	ADNCommonCharacter* character = dynamic_cast<ADNCommonCharacter*>(GetCharacter());

	if (character == nullptr)
		return;

	character->reload();
	UE_LOG(LogTemp, Warning, TEXT("Reload"));
}

void ADNPlayerController::Armed(const FInputActionValue& Value)
{
	ADNCommonCharacter* character = dynamic_cast<ADNCommonCharacter*>(GetCharacter());

	if (character == nullptr)
		return;

	character->armed();
	UE_LOG(LogTemp, Warning, TEXT("Armed"));
}

void ADNPlayerController::Crouch(const FInputActionValue& Value)
{
	ADNCommonCharacter* character = dynamic_cast<ADNCommonCharacter*>(GetCharacter());

	if (character == nullptr)
		return;

	character->crouch();
	UE_LOG(LogTemp, Warning, TEXT("Crouch"));
}

void ADNPlayerController::Aiming(const FInputActionValue& Value)
{
	ADNCommonCharacter* character = dynamic_cast<ADNCommonCharacter*>(GetCharacter());

	if (character == nullptr)
		return;

	character->aiming();
	UE_LOG(LogTemp, Warning, TEXT("Aiming"));
}


void ADNPlayerController::StopAiming(const FInputActionValue& Value)
{
	ADNCommonCharacter* character = dynamic_cast<ADNCommonCharacter*>(GetCharacter());

	if (character == nullptr)
		return;

	character->stop_aiming();
	UE_LOG(LogTemp, Warning, TEXT("StopAiming"));
}


void ADNPlayerController::Interaction(const FInputActionValue& Value)
{
	ADNCommonCharacter* character = dynamic_cast<ADNCommonCharacter*>(GetCharacter());

	if (character == nullptr)
		return;

	character->interaction();
	UE_LOG(LogTemp, Warning, TEXT("Interaction"));
}




void ADNPlayerController::CameraRotate(const FInputActionValue& Value)
{
	ADNCommonCharacter* character = dynamic_cast<ADNCommonCharacter*>(GetCharacter());

	if (character == nullptr)
		return;

	character->bUseControllerRotationYaw = false;

	UE_LOG(LogTemp, Warning, TEXT("CameraRotate"));
}


void ADNPlayerController::StopCameraRotate(const FInputActionValue& Value)
{
	ADNCommonCharacter* character = dynamic_cast<ADNCommonCharacter*>(GetCharacter());

	if (character == nullptr)
		return;

	character->bUseControllerRotationYaw = true;

	UE_LOG(LogTemp, Warning, TEXT("StopCameraRotate"));
}
