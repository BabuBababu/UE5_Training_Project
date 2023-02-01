
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
}

void UDNCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(TryGetPawnOwner()) == false)
		return;

	calculate_speed_direction(TryGetPawnOwner());

	_bIsInAir = TryGetPawnOwner()->GetMovementComponent()->IsFalling();

	ADNCommonCharacter* character = dynamic_cast<ADNCommonCharacter*>(TryGetPawnOwner());

	if (character == nullptr)
		return;


	_character_state = character->_character_state ;
	_aiming = character->_is_aiming;
	_near_wall = character->_is_near_wall;
	_sprinting = character->_is_sprint;
	_crouching = character->_is_crouch;
	_firing = character->_is_fire;
	_climbing = character->GetMovementComponent()->IsFlying();




	// 조준할 때 상체 위아래 블렌딩
	if (_aiming)
	{
		float angle = UKismetMathLibrary::ClampAngle(character->GetBaseAimRotation().Pitch, -55.f, 55.f);
		FRotator rotator = UKismetMathLibrary::MakeRotator(angle, 0.f, 0.f);

		_aiming_for_spine = rotator.GetInverse();
	}
	else
		_aiming_for_spine = FRotator(0.f, 0.f, 0.f);


	// 사망 몽타쥬 재생 체크
	if (nullptr != character->get_status_component())
	{
		if (character->get_status_component()->_dead)
		{
			on_die_montage_ended();

			if (false == _playing_die_montage)
			{
				Montage_Play(die_montage);
				_playing_die_montage = true;
			}
		}
	}

}



void UDNCharacterAnimInstance::calculate_speed_direction(APawn* pawn_in)
{
	_speed = pawn_in->GetVelocity().Length();

	_direction = CalculateDirection(pawn_in->GetVelocity(), pawn_in->GetActorRotation());
	
}

void UDNCharacterAnimInstance::on_die_montage_ended()
{
	if (false == Montage_IsPlaying(die_montage))
		return;

	_playing_die_montage = false;
	OnDieEnd.Broadcast();
}