// Fill out your copyright notice in the Description page of Project Settings.

#include "UE5_Training_Project/Controller/DNPlayerController.h"

// Engine
#include "Kismet/GameplayStatics.h"

// GameMode
#include "UE5_Training_Project/GameMode/DNGameModeBase.h"


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
	PEI->BindAction(InputActions->InputMove, ETriggerEvent::Triggered, this, &ADNPlayerController::Move);
	PEI->BindAction(InputActions->InputLook, ETriggerEvent::Triggered, this, &ADNPlayerController::Look);
	PEI->BindAction(InputActions->InputJump, ETriggerEvent::Triggered, this, &ADNPlayerController::Jump);
	PEI->BindAction(InputActions->InputJump, ETriggerEvent::Completed, this, &ADNPlayerController::StopJumping);
	PEI->BindAction(InputActions->InputFire, ETriggerEvent::Triggered, this, &ADNPlayerController::Fire);
	PEI->BindAction(InputActions->InputReload, ETriggerEvent::Triggered, this, &ADNPlayerController::Reload);
	
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
	UE_LOG(LogTemp, Warning, TEXT("Fire"));
}

void ADNPlayerController::Reload(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Reload"));
}
