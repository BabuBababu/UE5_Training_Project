
#include "UE5_Training_Project/Character/Animation/DNCharacterAnimInstance.h"

// Engine
#include <GameFramework/PawnMovementComponent.h>
#include <Kismet/KismetMathLibrary.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Component
#include "UE5_Training_Project/Component/DNStatusComponent.h"




UDNCharacterAnimInstance::UDNCharacterAnimInstance()
{

}

void UDNCharacterAnimInstance::NativeBeginPlay()
{

	ADNCommonCharacter* character = dynamic_cast<ADNCommonCharacter*>(TryGetPawnOwner());

	if (nullptr != character)
		_owner = character;

	add_event();
}

void UDNCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (false == IsValid(TryGetPawnOwner()))
		return;

	calculate_speed_direction(TryGetPawnOwner());

	_bIsInAir = TryGetPawnOwner()->GetMovementComponent()->IsFalling();

	if (nullptr == _owner)
		return;

	_character_state = _owner->_character_state ;
	_aiming = _owner->_is_aiming;
	_near_wall = _owner->_is_near_wall;
	_sprinting = _owner->_is_sprint;
	_crouching = _owner->_is_crouch;
	_firing = _owner->_is_fire;
	_climbing = _owner->GetMovementComponent()->IsFlying();




	// 조준할 때 상체 위아래 블렌딩
	if (_aiming)
	{
		float angle = UKismetMathLibrary::ClampAngle(_owner->GetBaseAimRotation().Pitch, -55.f, 55.f);
		FRotator rotator = UKismetMathLibrary::MakeRotator(angle, 0.f, 0.f);

		_aiming_for_spine = rotator.GetInverse();
	}
	else
		_aiming_for_spine = FRotator(0.f, 0.f, 0.f);


	// 사망 몽타쥬 재생 체크
	if (nullptr != _owner->get_status_component())
	{
		if (_owner->get_status_component()->_dead)
		{
			if (false == _playing_die_montage)
			{
				Montage_Play(die_montage);
				_playing_die_montage = true;
			}

			if (false == Montage_IsPlaying(die_montage))
				on_die_montage_ended();
		}


	}


	// 장전 재생 체크
	if (true == _playing_reload_montage)
	{
		if (false == Montage_IsPlaying(reload_montage))
			on_reload_montage_ended();
	}
}

void UDNCharacterAnimInstance::add_event()
{
	_owner->OnFire.AddDynamic(this , &UDNCharacterAnimInstance::play_fire_montage);
	_owner->OnReload.AddDynamic(this, &UDNCharacterAnimInstance::play_reload_montage);

}

void UDNCharacterAnimInstance::remove_event()
{

}

void UDNCharacterAnimInstance::play_reload_montage()
{
	if (false == _playing_reload_montage)
	{
		Montage_Play(reload_montage);
		_playing_reload_montage = true;
	}

}

void UDNCharacterAnimInstance::play_fire_montage()
{
	Montage_Play(fire_montage);
}

void UDNCharacterAnimInstance::calculate_speed_direction(APawn* pawn_in)
{
	_speed = pawn_in->GetVelocity().Length();

	_direction = CalculateDirection(pawn_in->GetVelocity(), pawn_in->GetActorRotation());
	
}

void UDNCharacterAnimInstance::on_die_montage_ended()
{
	_playing_die_montage = false;
	OnDieEnd.Broadcast();
}

void UDNCharacterAnimInstance::on_reload_montage_ended()
{
	_playing_reload_montage = false;
	OnReloadEnd.Broadcast();
}