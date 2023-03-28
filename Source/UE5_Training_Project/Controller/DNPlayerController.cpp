// Fill out your copyright notice in the Description page of Project Settings.

#include "UE5_Training_Project/Controller/DNPlayerController.h"

// Engine
#include <Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>

// GameMode
#include "UE5_Training_Project/GameMode/DNGameModeBase.h"

// Character
#include "UE5_Training_Project/Character/DNPlayerCharacter.h"
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"


// Component
#include "UE5_Training_Project/Character/Component/DNPlayerLineTrace.h"


// EnhancedInput
#include "EnhancedInput/Public/InputMappingContext.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "EnhancedInput/Public/InputActionValue.h"

// Manager
#include "UE5_Training_Project/Manager/DNUIManager.h"
#include "UE5_Training_Project/Manager/DNObjectManager.h"
#include "UE5_Training_Project/UI/Manager/DNWidgetManager.h"

// UI
#include "UE5_Training_Project/UI/Widget/Panel/DNSquadPanel.h"


ADNPlayerController::ADNPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	_selected_first = false;
	_selected_num_first = -1;
	_selected_num_second = -1;

	_owner = nullptr;
}


void ADNPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ADNPlayerCharacter* character = Cast<ADNPlayerCharacter>(GetCharacter());

	if(nullptr != character)
		_owner = character;
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
	PEI->BindAction(InputActions->InputKnife, ETriggerEvent::Completed, this, &ADNPlayerController::Knife);
	PEI->BindAction(InputActions->InputThrow, ETriggerEvent::Completed, this, &ADNPlayerController::Throw);
	PEI->BindAction(InputActions->InputReload, ETriggerEvent::Completed, this, &ADNPlayerController::Reload);
	PEI->BindAction(InputActions->InputAiming, ETriggerEvent::Triggered, this, &ADNPlayerController::Aiming);
	PEI->BindAction(InputActions->InputAiming, ETriggerEvent::Completed, this, &ADNPlayerController::StopAiming);
	PEI->BindAction(InputActions->InputArmed, ETriggerEvent::Completed, this, &ADNPlayerController::Armed);
	PEI->BindAction(InputActions->InputCrouch, ETriggerEvent::Completed, this, &ADNPlayerController::Crouch);
	PEI->BindAction(InputActions->InputSprint, ETriggerEvent::Triggered, this, &ADNPlayerController::Sprint);
	PEI->BindAction(InputActions->InputSprint, ETriggerEvent::Completed, this, &ADNPlayerController::StopSprint);
	PEI->BindAction(InputActions->InputCover, ETriggerEvent::Completed, this, &ADNPlayerController::Cover);
	
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
	PEI->BindAction(InputActions->IA_Q, ETriggerEvent::Completed, this, &ADNPlayerController::SelectCharacter<E_INPUT_KEY::IK_Q>);
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

	if (MovementVector.X > 0)
	{
		_owner->_moving_right = true;
		_owner->_moving_left = false;
	}
	else if (MovementVector.X < 0)
	{
		_owner->_moving_right = false;
		_owner->_moving_left = true;

	}
	else
	{
		_owner->_moving_right = false;
		_owner->_moving_left = false;
	}
	
	// 뒤로 가는 경우 속도 감소
	if (MovementVector.Y < 0)
	{
		_owner->GetCharacterMovement()->MaxWalkSpeed = _owner->_back_move_max_walk_speed;
	}
	else
	{
		if (_owner->_is_sprint)
			_owner->GetCharacterMovement()->MaxWalkSpeed = _owner->_sprint_max_walk_speed;
		else
			_owner->GetCharacterMovement()->MaxWalkSpeed = _owner->_default_max_speed;
	}

}


void ADNPlayerController::Sprint(const FInputActionValue& Value)
{
	

	if (nullptr == _owner)
		return;

	_owner->sprint();
}

void ADNPlayerController::StopSprint(const FInputActionValue& Value)
{
	if (nullptr == _owner)
		return;

	_owner->stop_sprint();

}

void ADNPlayerController::Look(const FInputActionValue& Value)
{

	if (nullptr == _owner)
		return;

	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	

	// add yaw and pitch input to controller
	_owner->AddControllerYawInput(LookAxisVector.X);
	_owner->AddControllerPitchInput(LookAxisVector.Y);
}

void ADNPlayerController::Jump(const FInputActionValue& Value)
{
	if (nullptr == _owner)
		return;


	if (_owner->_is_near_wall)
		_owner->wall_jump();
	else
		_owner->Jump();


}

void ADNPlayerController::StopJumping(const FInputActionValue& Value)
{
	if (nullptr == _owner)
		return;

	_owner->StopJumping();


}

void ADNPlayerController::Fire(const FInputActionValue& Value)
{
	if (nullptr == _owner)
		return;


	_owner->start_fire();

}

void ADNPlayerController::Knife(const FInputActionValue& Value)
{
	if (nullptr == _owner)
		return;


	_owner->attack_knife();

}

void ADNPlayerController::Throw(const FInputActionValue& Value)
{
	if (nullptr == _owner)
		return;

	_owner->throw_grenade();

}

void ADNPlayerController::StopFire(const FInputActionValue& Value)
{
	if (nullptr == _owner)
		return;


	_owner->stop_fire();

}


void ADNPlayerController::Reload(const FInputActionValue& Value)
{
	if (nullptr == _owner)
		return;

	_owner->reload();
	

}

void ADNPlayerController::Armed(const FInputActionValue& Value)
{
	if (nullptr == _owner)
		return;

	_owner->armed();

}

void ADNPlayerController::Crouch(const FInputActionValue& Value)
{
	if (nullptr == _owner)
		return;


	_owner->crouch();

}

void ADNPlayerController::Cover(const FInputActionValue& Value)
{
	if (nullptr == _owner)
		return;

	_owner->cover();
}

void ADNPlayerController::Aiming(const FInputActionValue& Value)
{
	if (nullptr == _owner)
		return;

	_owner->aiming();
}


void ADNPlayerController::StopAiming(const FInputActionValue& Value)
{
	if (nullptr == _owner)
		return;

	_owner->stop_aiming();
}


void ADNPlayerController::Interaction(const FInputActionValue& Value)
{
	if (nullptr == _owner)
		return;

	_owner->interaction();
}




void ADNPlayerController::CameraRotate(const FInputActionValue& Value)
{
	if (nullptr == _owner)
		return;

	_owner->bUseControllerRotationYaw = false;

}


void ADNPlayerController::StopCameraRotate(const FInputActionValue& Value)
{
	if (nullptr == _owner)
		return;

	_owner->bUseControllerRotationYaw = true;

}

template<E_INPUT_KEY Key>
void ADNPlayerController::SelectCharacter(const FInputActionValue& Value)
{
	// 5번은 플레이어이므로 제외

	if (_selected_num_first == -1 )			//첫번째로 키입력
		_selected_first = true;

	if (Key == E_INPUT_KEY::IK_1)
	{
		if (true == _selected_first)		//첫번째로 키입력을 했을 때
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
	else if (Key == E_INPUT_KEY::IK_Q)		//명령 취소
	{
		if (false == _selected_first)			//두번째 키 입력 때 눌렀을 경우
		{


			OBJECT_MANAGER->_in_squad_doll_array[_selected_num_first]->order_stop_handler();		// 해당 인형 명령 취소
			_selected_first = false;
			_selected_num_first = -1;
			_selected_num_second = -1;
			OnStopAnimation.Broadcast();
		}
	}

	OnSquadPosition.Broadcast(_selected_num_first);





	// 두번의 숫자를 눌렀다면 
	if (-1 != _selected_num_first && -1 != _selected_num_second)
	{

		if (_selected_num_first == _selected_num_second)			//숫자가 같은거면 개인 명령
		{
			//오더할 내용 추가
			if (nullptr == _owner)
				return;

			// 키입력 -> 라인트레이스 실행 -> 플레이어에서 해당 명령 실행 -> 다시 인형의 AI컨트롤러에서 실행
			_owner->_line_trace->OnOrder(_owner, OBJECT_MANAGER->_in_squad_doll_array[_selected_num_first]);
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


template<E_INPUT_KEY Key>
void ADNPlayerController::ActiveSkill(const FInputActionValue& Value)
{
	if (Key == E_INPUT_KEY::IK_F)
	{

	}
	else if (Key == E_INPUT_KEY::IK_G)
	{

	}
	else if (Key == E_INPUT_KEY::IK_H)
	{

	}
}