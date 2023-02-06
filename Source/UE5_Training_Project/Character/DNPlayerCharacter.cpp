﻿


#include "UE5_Training_Project/Character/DNPlayerCharacter.h"

// Engine
#include <Engine/Classes/Kismet/GameplayStatics.h>

// Controller
#include "UE5_Training_Project/Controller/DNPlayerController.h"

// Component
#include "UE5_Training_Project/Character/Component/DNPlayerLineTrace.h"
#include <UE5_Training_Project/Component/DNStatusComponent.h>

void ADNPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ADNPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	_line_trace->OnInteraction(this);
}


void ADNPlayerCharacter::start_fire()
{
	_is_fire = true;
	fire();

	
}


void ADNPlayerCharacter::reload()
{
	if (_status->_has_ammo == 0)																//총알이 없다면 장전 불가능
		return;

	if (_status->_current_ammo == _status->_chartacter_data->character_status_data.max_ammo)	//총알이 꽉찼다면 장전 불가능
		return;

	if (false == _is_armed_weapon)																//총을 들고 있지 않다면 장전 불가능
		return;

	if (_is_reloading == false)
	{

		_is_reloading = true;
		_character_state = E_CHARACTER_STATE::CS_RELOAD;
		UGameplayStatics::PlaySoundAtLocation(this, _reload_soundcue, GetActorLocation());
		OnReload.Broadcast();
	}

}


void ADNPlayerCharacter::fire()
{
	if (_is_reloading)			//장전중이면 사격 안됨
		return;

	if (_is_sprint)				//전력질주할때 사격 안됨
		return;

	if (false == _is_armed_weapon)	//총을 들고 있지 않으면 사격 안됨
		return;

	if (_status->get_current_ammo() == 0) //총알이 0발이면 사격 안됨
		return;

	if (_is_fire)
	{
		
		_line_trace->OnFire(this);
		OnFire.Broadcast();
		ADNPlayerController* controller = dynamic_cast<ADNPlayerController*>(GetController());
		UGameplayStatics::PlaySoundAtLocation(this, _fire_soundcue,GetActorLocation());
		if (controller->get_camera_shake() != nullptr)
			controller->ClientStartCameraShake(controller->get_camera_shake());


		UE_LOG(LogTemp, Warning, TEXT("Player Timer : %s"), *_fire_timer.ToString());
		GetWorld()->GetTimerManager().SetTimer(_fire_timer, this, &ADNPlayerCharacter::fire, _status->_chartacter_data->character_status_data.fire_speed, true);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Attack Now"));

	}

}


void ADNPlayerCharacter::armed()
{
	Super::armed();

	player_arm_event(_is_armed_weapon);
}


void ADNPlayerCharacter::crouch()
{
	Super::crouch();
	player_crouch_event(_is_crouch);
}


void ADNPlayerCharacter::player_arm_event(bool armed_in)
{
	on_armed.Broadcast(armed_in);
}

void ADNPlayerCharacter::player_crouch_event(bool crouch_in)
{
	//on_crouch.Broadcast(crouch_in);		일단 기능을 꺼둡니다. 플레이어가 숙일 때 다른 인형들도 숙이는 기능
}