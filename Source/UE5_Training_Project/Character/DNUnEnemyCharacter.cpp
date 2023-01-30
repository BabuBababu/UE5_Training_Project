// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"

// Character
#include "UE5_Training_Project/Character/DNPlayerCharacter.h"

// AnimInstance
#include "UE5_Training_Project/Character/Animation/DNCharacterAnimInstance.h"

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"


ADNUnEnemyCharacter::ADNUnEnemyCharacter()
{
	init_base();
	init_ai();
}


void ADNUnEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	add_event();

}

void ADNUnEnemyCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	remove_event();
}

void ADNUnEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 이건 원래 여기서 하면 안되는딩
	if (_is_fire)
	{
		_fire_current_time += DeltaTime;
	}
	
	if (_fire_max_time <= _fire_current_time)
	{
		_is_fire = false;
		_is_aiming = false;
		_fire_current_time = 0.f;
		UDNCharacterAnimInstance* anim = dynamic_cast<UDNCharacterAnimInstance*>(this->_character_skeletal_mesh->GetAnimInstance());
		anim->OnAttackEnd.Broadcast();		//원래는 몽타주 기준이지만 여긴 지속 사격 애니메이션이므로 이렇게 했음
	}
}

void ADNUnEnemyCharacter::add_event()
{
	ADNPlayerCharacter* player = dynamic_cast<ADNPlayerCharacter*>(GetWorld()->GetFirstPlayerController()->GetPawn());
	player->on_armed.AddDynamic(this, &ADNUnEnemyCharacter::change_armed_state_handler);
	player->on_crouch.AddDynamic(this, &ADNUnEnemyCharacter::change_crouch_state_handler);
}

void ADNUnEnemyCharacter::remove_event()
{
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

	_fire_max_time = 0.2f; //일단은 임의로 0.2초
}


void ADNUnEnemyCharacter::fire()
{
	if (_is_armed_weapon == false)
		return;

	_is_fire = true;
	_is_aiming = true;

	Super::fire();		//여기서는 얘를 나중에 호출

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