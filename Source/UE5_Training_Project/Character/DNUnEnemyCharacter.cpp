// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"

// Character
#include "UE5_Training_Project/Character/DNPlayerCharacter.h"

// AnimInstance
#include "UE5_Training_Project/Character/Animation/DNCharacterAnimInstance.h"

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// Component
#include "UE5_Training_Project/Character/Component/DNPlayerLineTrace.h"


ADNUnEnemyCharacter::ADNUnEnemyCharacter()
{
	init_base();
	init_ai();
}


void ADNUnEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	_is_attacking = false;
}

void ADNUnEnemyCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	remove_event();
}

void ADNUnEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADNUnEnemyCharacter::add_event()
{
	Super::add_event();

	ADNPlayerCharacter* player = dynamic_cast<ADNPlayerCharacter*>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (nullptr == player)
		return;

	player->on_armed.AddDynamic(this, &ADNUnEnemyCharacter::change_armed_state_handler);
	player->on_crouch.AddDynamic(this, &ADNUnEnemyCharacter::change_crouch_state_handler);
}

void ADNUnEnemyCharacter::remove_event()
{
	Super::remove_event();
	//ADNPlayerCharacter* player = dynamic_cast<ADNPlayerCharacter*>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//player->on_armed.RemoveDynamic(this, &ADNUnEnemyCharacter::change_armed_state_handler);
	//player->on_crouch.RemoveDynamic(this, &ADNUnEnemyCharacter::change_crouch_state_handler);
}



void ADNUnEnemyCharacter::init_ai()
{
	AIControllerClass = ADNAIController::StaticClass();		//엔진 초기화 단계에서 생성해줘야하므로 StaticClass
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}


void ADNUnEnemyCharacter::init_base()
{
	_character_type = E_CHARACTER_TYPE::CT_GRIFFIN;
}


void ADNUnEnemyCharacter::fire()
{
	// 여기엔 다른 효과나 기능들을 넣으면 될듯
	Super::fire();
}

void ADNUnEnemyCharacter::set_attack_finish()
{

}


void ADNUnEnemyCharacter::change_armed_state_handler(bool armed_in)
{
	if (true == armed_in)
	{
		bUseControllerRotationYaw = true;
		_weapon_armed->SetVisibility(true);
		_weapon_un_armed->SetVisibility(false);
		_is_armed_weapon = true;
		_pre_upper_character_state = _character_state;
		_character_state = E_CHARACTER_STATE::CS_ARM;
	}
	else
	{
		bUseControllerRotationYaw = false;
		_weapon_armed->SetVisibility(false);
		_weapon_un_armed->SetVisibility(true);
		_is_armed_weapon = false;
		_character_state = _pre_upper_character_state;
	}
}


void ADNUnEnemyCharacter::change_crouch_state_handler(bool crouch_in)
{
	_is_crouch = crouch_in;
}

