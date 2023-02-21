// Fill out your copyright notice in the Description page of Project Settings.

#include "UE5_Training_Project/Controller/DNPlayerController.h"

// Engine
#include "Kismet/GameplayStatics.h"
#include <GameFramework/CharacterMovementComponent.h>

// GameMode
#include "UE5_Training_Project/GameMode/DNGameModeBase.h"

// Character
#include "UE5_Training_Project/Character/DNPlayerCharacter.h"


// EnhancedInput
#include "EnhancedInput/Public/InputMappingContext.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "EnhancedInput/Public/InputActionValue.h"

// Manager
#include "UE5_Training_Project/Manager/DNUIManager.h"
#include "UE5_Training_Project/Manager/DNObjectManager.h"
#include "UE5_Training_Project/UI/Manager/DNWidgetManager.h"

// Character
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"


// UI
#include "UE5_Training_Project/UI/Widget/Panel/DNSquadPanel.h"


ADNPlayerController::ADNPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	_order_now = false;
	_selected_first = false;
	_selected_num_first = -1;
	_selected_num_second = -1;
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
	PEI->BindAction(InputActions->InputFire, ETriggerEvent::Started, this, &ADNPlayerController::Fire);
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
	

	// 전투중 스쿼드에서 인형 선택

	PEI->BindAction(InputActions->IA_Num_1, ETriggerEvent::Completed, this, &ADNPlayerController::SelectCharacter<E_INPUT_KEY::IK_1>);
	PEI->BindAction(InputActions->IA_Num_2, ETriggerEvent::Completed, this, &ADNPlayerController::SelectCharacter<E_INPUT_KEY::IK_2>);
	PEI->BindAction(InputActions->IA_Num_3, ETriggerEvent::Completed, this, &ADNPlayerController::SelectCharacter<E_INPUT_KEY::IK_3>);
	PEI->BindAction(InputActions->IA_Num_4, ETriggerEvent::Completed, this, &ADNPlayerController::SelectCharacter<E_INPUT_KEY::IK_4>);
	PEI->BindAction(InputActions->IA_Num_5, ETriggerEvent::Completed, this, &ADNPlayerController::SelectCharacter<E_INPUT_KEY::IK_5>);
	PEI->BindAction(InputActions->IA_Num_6, ETriggerEvent::Completed, this, &ADNPlayerController::SelectCharacter<E_INPUT_KEY::IK_6>);
	PEI->BindAction(InputActions->IA_Num_7, ETriggerEvent::Completed, this, &ADNPlayerController::SelectCharacter<E_INPUT_KEY::IK_7>);
	PEI->BindAction(InputActions->IA_Num_8, ETriggerEvent::Completed, this, &ADNPlayerController::SelectCharacter<E_INPUT_KEY::IK_8>);
	PEI->BindAction(InputActions->IA_Num_9, ETriggerEvent::Completed, this, &ADNPlayerController::SelectCharacter<E_INPUT_KEY::IK_9>);
}


void ADNPlayerController::Move(const FInputActionValue& Value)
{
	if (nullptr == GetCharacter())
		return;

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
	ADNPlayerCharacter* character = dynamic_cast<ADNPlayerCharacter*>(GetCharacter());

	if (nullptr == character)
		return;

	character->sprint();
	UE_LOG(LogTemp, Warning, TEXT("Sprint"));
}

void ADNPlayerController::StopSprint(const FInputActionValue& Value)
{
	ADNPlayerCharacter* character = dynamic_cast<ADNPlayerCharacter*>(GetCharacter());

	if (nullptr == character)
		return;

	character->stop_sprint();
	UE_LOG(LogTemp, Warning, TEXT("StopSprint"));
}

void ADNPlayerController::Look(const FInputActionValue& Value)
{

	if (nullptr == GetCharacter())
		return;

	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	

	// add yaw and pitch input to controller
	GetCharacter()->AddControllerYawInput(LookAxisVector.X);
	GetCharacter()->AddControllerPitchInput(LookAxisVector.Y);
}

void ADNPlayerController::Jump(const FInputActionValue& Value)
{
	if (nullptr == GetCharacter())
		return;

	GetCharacter()->Jump();
	UE_LOG(LogTemp, Warning, TEXT("Jump"));
}

void ADNPlayerController::StopJumping(const FInputActionValue& Value)
{
	if (nullptr == GetCharacter())
		return;

	GetCharacter()->StopJumping();
	UE_LOG(LogTemp, Warning, TEXT("StopJumping"));
}

void ADNPlayerController::Fire(const FInputActionValue& Value)
{
	ADNPlayerCharacter* character = dynamic_cast<ADNPlayerCharacter*>(GetCharacter());

	if (character == nullptr)
		return;

	character->start_fire();

	UE_LOG(LogTemp, Warning, TEXT("Fire"));
}


void ADNPlayerController::StopFire(const FInputActionValue& Value)
{
	ADNPlayerCharacter* character = dynamic_cast<ADNPlayerCharacter*>(GetCharacter());

	if (character == nullptr)
		return;

	character->stop_fire();
	UE_LOG(LogTemp, Warning, TEXT("StopFire"));
}


void ADNPlayerController::Reload(const FInputActionValue& Value)
{
	ADNPlayerCharacter* character = dynamic_cast<ADNPlayerCharacter*>(GetCharacter());

	if (character == nullptr)
		return;

	character->reload();
	UE_LOG(LogTemp, Warning, TEXT("Reload"));
}

void ADNPlayerController::Armed(const FInputActionValue& Value)
{
	ADNPlayerCharacter* character = dynamic_cast<ADNPlayerCharacter*>(GetCharacter());

	if (character == nullptr)
		return;

	character->armed();
	UE_LOG(LogTemp, Warning, TEXT("Armed"));
}

void ADNPlayerController::Crouch(const FInputActionValue& Value)
{
	ADNPlayerCharacter* character = dynamic_cast<ADNPlayerCharacter*>(GetCharacter());

	if (character == nullptr)
		return;

	character->crouch();
	UE_LOG(LogTemp, Warning, TEXT("Crouch"));
}

void ADNPlayerController::Aiming(const FInputActionValue& Value)
{
	ADNPlayerCharacter* character = dynamic_cast<ADNPlayerCharacter*>(GetCharacter());

	if (character == nullptr)
		return;

	character->aiming();
	UE_LOG(LogTemp, Warning, TEXT("Aiming"));
}


void ADNPlayerController::StopAiming(const FInputActionValue& Value)
{
	ADNPlayerCharacter* character = dynamic_cast<ADNPlayerCharacter*>(GetCharacter());

	if (character == nullptr)
		return;

	character->stop_aiming();
	UE_LOG(LogTemp, Warning, TEXT("StopAiming"));
}


void ADNPlayerController::Interaction(const FInputActionValue& Value)
{
	ADNPlayerCharacter* character = dynamic_cast<ADNPlayerCharacter*>(GetCharacter());

	if (character == nullptr)
		return;

	character->interaction();
	UE_LOG(LogTemp, Warning, TEXT("Interaction"));
}




void ADNPlayerController::CameraRotate(const FInputActionValue& Value)
{
	ADNPlayerCharacter* character = dynamic_cast<ADNPlayerCharacter*>(GetCharacter());

	if (character == nullptr)
		return;

	character->bUseControllerRotationYaw = false;

	UE_LOG(LogTemp, Warning, TEXT("CameraRotate"));
}


void ADNPlayerController::StopCameraRotate(const FInputActionValue& Value)
{
	ADNPlayerCharacter* character = dynamic_cast<ADNPlayerCharacter*>(GetCharacter());

	if (character == nullptr)
		return;

	character->bUseControllerRotationYaw = true;

	UE_LOG(LogTemp, Warning, TEXT("StopCameraRotate"));
}

template<E_INPUT_KEY Key>
void ADNPlayerController::SelectCharacter(const FInputActionValue& Value)
{
	// 5번은 플레이어이므로 제외

	if (_selected_num_first == -1 )
		_selected_first = true;


	if (Key == E_INPUT_KEY::IK_1)
	{
		if (true == _selected_first)
		{
			_selected_num_first = 1;
			_selected_first = false;
		}
		else
		{
			_selected_num_second = 1;
		}
	}
	else if (Key == E_INPUT_KEY::IK_2)
	{
		if (true == _selected_first)
		{
			_selected_num_first = 2;
			_selected_first = false;
		}
		else
		{
			_selected_num_second = 2;
		}
	}
	else if (Key == E_INPUT_KEY::IK_3)
	{
		if (true == _selected_first)
		{
			_selected_num_first = 3;
			_selected_first = false;
		}
		else
		{
			_selected_num_second = 3;
		}
	}
	else if (Key == E_INPUT_KEY::IK_4)
	{
		if (true == _selected_first)
		{
			_selected_num_first = 4;
			_selected_first = false;
		}
		else
		{
			_selected_num_second = 4;
		}
	}
	
	else if (Key == E_INPUT_KEY::IK_6)
	{
		if (true == _selected_first)
		{
			_selected_num_first = 6;
			_selected_first = false;
		}
		else
		{
			_selected_num_second = 6;
		}
	}
	else if (Key == E_INPUT_KEY::IK_7)
	{
		if (true == _selected_first)
		{
			_selected_num_first = 7;
			_selected_first = false;
		}
		else
		{
			_selected_num_second = 7;
		}
	}
	else if (Key == E_INPUT_KEY::IK_8)
	{
		if (true == _selected_first)
		{
			_selected_num_first = 8;
			_selected_first = false;
		}
		else
		{
			_selected_num_second = 8;
		}
	}
	else if (Key == E_INPUT_KEY::IK_9)
	{
		if (true == _selected_first)
		{
			_selected_num_first = 9;
			_selected_first = false;
		}
		else
		{
			_selected_num_second = 9;
		}
	}

	OnSquadPosition.Broadcast(_selected_num_first);





	// 두번의 숫자를 눌렀다면 
	if (-1 != _selected_num_first && -1 != _selected_num_second)
	{

		if (_selected_num_first == _selected_num_second)			//숫자가 같은거면 개인 명령
		{
			//오더할 내용 추가
			_order_now = true;
			return;
		}

		UDNSquadPanel* panel = Cast<UDNSquadPanel>(WIDGET_MANAGER->get_panel(E_UI_PANEL_TYPE::UPT_SQUAD));

		if (IsValid(panel))
		{
			panel->update_squad(_selected_num_first, _selected_num_second);								//UI 업데이트
			OBJECT_MANAGER->update_combat_squad_postion(_selected_num_first, _selected_num_second);		//오브젝트 업데이트
			OnStopAnimation.Broadcast();
		}



		_selected_first = false;
		_selected_num_first = -1;
		_selected_num_second = -1;

	}




}