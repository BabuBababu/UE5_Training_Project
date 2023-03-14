
#include "UE5_Training_Project/Character/Animation/DNCharacterAnimInstance.h"

// Engine
#include <GameFramework/PawnMovementComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <Engine/Classes/Kismet/GameplayStatics.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Controller
#include "UE5_Training_Project/Controller/DNPlayerController.h"

// Component
#include "UE5_Training_Project/Component/DNStatusComponent.h"
#include "UE5_Training_Project/Character/Component/DNPlayerLineTrace.h"




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
	_cover_now = _owner->_cover_now;
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




	// 적군은 여기서 더 이상 계산 X
	if (_owner->_character_type == E_CHARACTER_TYPE::CT_ENEMY)
		return;






	// 해당 몽타쥬 재생시 움직임 멈춤
	if (true == _playing_cover_fire_montage)								// 커버 공격
	{
		_owner->GetMovementComponent()->Deactivate();

		if (false == Montage_IsPlaying(cover_fire_right_montage) &&			//애니메이션 종료시
			false == Montage_IsPlaying(cover_fire_left_montage))
		{
			_owner->GetMovementComponent()->Activate();
			_playing_cover_fire_montage = false;
			_cover_fire_lock = true;										//정상 종료됐으므로 락을 걸어줍니다
		}
	}




	// 이건 일단 아직 적용안함
	if (true == _playing_cover_turn_montage)								// 커버 방향전환
	{
		_owner->GetMovementComponent()->Deactivate();

		if (false == Montage_IsPlaying(cover_turn_right_montage) &&			//애니메이션 종료시
			false == Montage_IsPlaying(cover_turn_left_montage))
		{
			_owner->GetMovementComponent()->Activate();
			_playing_cover_turn_montage = false;
		}
	}


}

void UDNCharacterAnimInstance::add_event()
{
	_owner->OnFire.AddDynamic(this , &UDNCharacterAnimInstance::play_fire_montage);
	_owner->StopFire.AddDynamic(this, &UDNCharacterAnimInstance::unlock_cover_animation);
	_owner->OnCoverFire.AddDynamic(this, &UDNCharacterAnimInstance::play_cover_fire_montage);
	_owner->OnReload.AddDynamic(this, &UDNCharacterAnimInstance::play_reload_montage);

}

void UDNCharacterAnimInstance::remove_event()
{

}

void UDNCharacterAnimInstance::unlock_cover_animation()
{
	_cover_fire_lock = false;
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
	if (false == _cover_now)
	{
		Montage_Play(fire_montage);
	}
	
}

void UDNCharacterAnimInstance::calculate_speed_direction(APawn* pawn_in)
{
	_speed = pawn_in->GetVelocity().Length();

	_direction = CalculateDirection(pawn_in->GetVelocity(), pawn_in->GetActorRotation());
	
}

void UDNCharacterAnimInstance::play_cover_fire_montage()
{

	if (_cover_now)
	{
		if (_cover_fire_lock)
		{
			Montage_Play(fire_montage);

			_owner->_line_trace->OnFire(_owner);
			ADNPlayerController* controller = dynamic_cast<ADNPlayerController*>(_owner->GetController());
			UGameplayStatics::PlaySoundAtLocation(this, _owner->_fire_soundcue, _owner->GetActorLocation());
			if (controller->get_camera_shake() != nullptr)
				controller->ClientStartCameraShake(controller->get_camera_shake());

			
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Character::Cover Fire"));

			return;
		}

		if (false == _playing_cover_fire_montage)
		{
			Montage_Play(cover_fire_right_montage);
			_playing_cover_fire_montage = true;
		}
	}
	

	// 일단 하나만 해보자
	/*if (false == cover_fire_left_montage)
	{
		Montage_Play(cover_fire_left_montage);
		_playing_cover_fire_montage = true;
	}*/
}


void UDNCharacterAnimInstance::play_cover_turn_left_montage()
{
	if (false == cover_turn_left_montage)
	{
		Montage_Play(cover_turn_left_montage);
		_playing_cover_turn_montage = true;
	}
}

void UDNCharacterAnimInstance::play_cover_turn_right_montage()
{
	if (false == cover_turn_right_montage)
	{
		Montage_Play(cover_turn_right_montage);
		_playing_cover_turn_montage = true;
	}
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