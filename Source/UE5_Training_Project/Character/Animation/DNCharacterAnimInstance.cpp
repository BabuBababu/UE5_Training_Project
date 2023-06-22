
#include "UE5_Training_Project/Character/Animation/DNCharacterAnimInstance.h"

// Engine
#include <GameFramework/PawnMovementComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <KismetAnimationLibrary.h>
#include <Engine/Classes/Kismet/GameplayStatics.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Actor
#include "UE5_Training_Project/Actor/Wall/DNCommonWall.h"

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

	ADNCommonCharacter* character = Cast<ADNCommonCharacter>(TryGetPawnOwner());

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


	_character_state = _owner->_character_state;
	_aiming = _owner->_is_aiming;
	_near_wall = _owner->_is_near_wall;
	_sprinting = _owner->_is_sprint;
	_crouching = _owner->_is_crouch;
	_firing = _owner->_is_fire;
	_cover_now = _owner->_cover_now;
	_climbing = _owner->GetMovementComponent()->IsFlying();
	_input_left = _owner->_moving_left;
	_input_right = _owner->_moving_right;
	_covered_left = _owner->_cover_left;
	_covered_right = _owner->_cover_right;


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
		if (Montage_IsPlaying(reload_montage))
			return;
		if (Montage_IsPlaying(reload_high_cover_left_montage))
			return;
		if (Montage_IsPlaying(reload_high_cover_right_montage))
			return;
		if (Montage_IsPlaying(reload_cover_left_montage))
			return;
		if (Montage_IsPlaying(reload_cover_right_montage))
			return;

		on_reload_montage_ended();
	}



	// 적군은 여기서 더 이상 계산 X
	if (_owner->_character_type == E_CHARACTER_TYPE::CT_ENEMY)
		return;

	//////////////////////////////////////////// 로비 ////////////////////////////////////
	
	// 경례 재생 체크
	if (true == _playing_salute_montage)
	{
		if (false == Montage_IsPlaying(salute_montage))
			on_salute_montage_ended();
	}

	// 수면 재생 체크
	if (true == _playing_start_sleep_montage)
	{
		if (false == Montage_IsPlaying(start_sleep_montage))
			on_start_sleep_montage_ended();
	}

	// 기상 재생 체크
	if (true == _playing_wakeup_montage)
	{
		if (false == Montage_IsPlaying(wakeup_montage))
			on_wakeup_montage_ended();
	}


	//////////////////////////////////////////// 전투 ////////////////////////////////////

	// 나이프 재생 체크
	if (true == _playing_knife_montage)
	{
		if (false == Montage_IsPlaying(knife_montage))
			on_knife_montage_ended();
	}

	// 수류탄 재생 체크
	if (true == _playing_throw_montage)
	{
		if (false == Montage_IsPlaying(throw_montage))
			on_throw_montage_ended();
	}




	// 해당 몽타쥬 재생시 움직임 멈춤
	
	if (true == _playing_idle_to_cover_left_montage)								// 서있다가 왼쪽 엄폐할 때 
	{
		_owner->GetMovementComponent()->Deactivate();

		if (false == Montage_IsPlaying(idle_to_cover_left_montage))					//애니메이션 종료시
		{
			_owner->GetMovementComponent()->Activate();
			_playing_idle_to_cover_left_montage = false;
			_owner->set_cover();
		}
	}

	if (true == _playing_idle_to_cover_right_montage)								// 서있다가 오른쪽 엄폐할 때 
	{
		_owner->GetMovementComponent()->Deactivate();

		if (false == Montage_IsPlaying(idle_to_cover_right_montage))					//애니메이션 종료시
		{
			_owner->GetMovementComponent()->Activate();
			_playing_idle_to_cover_right_montage = false;
			_owner->set_cover();


		}
	}

	if (true == _playing_cover_to_idle_left_montage)								// 오른쪽 엄폐하다가 설 때 
	{
		_owner->GetMovementComponent()->Deactivate();

		if (false == Montage_IsPlaying(cover_to_idle_left_montage))					//애니메이션 종료시
		{
			_owner->GetMovementComponent()->Activate();
			_playing_cover_to_idle_left_montage = false;
			_owner->set_uncover();


		}
	}

	if (true == _playing_cover_to_idle_right_montage)								// 왼쪽 엄폐하다가 설 때 
	{
		_owner->GetMovementComponent()->Deactivate();

		if (false == Montage_IsPlaying(cover_to_idle_right_montage))					//애니메이션 종료시
		{
			_owner->GetMovementComponent()->Activate();
			_playing_cover_to_idle_right_montage = false;
			_owner->set_uncover();


		}
	}

	if (true == _playing_high_idle_to_cover_left_montage)								// 서있다가 왼쪽 엄폐할 때 
	{
		_owner->GetMovementComponent()->Deactivate();

		if (false == Montage_IsPlaying(high_idle_to_cover_left_montage))					//애니메이션 종료시
		{
			_owner->GetMovementComponent()->Activate();
			_playing_high_idle_to_cover_left_montage = false;
			_owner->set_cover();
		}
	}

	if (true == _playing_high_idle_to_cover_right_montage)								// 서있다가 오른쪽 엄폐할 때 
	{
		_owner->GetMovementComponent()->Deactivate();

		if (false == Montage_IsPlaying(high_idle_to_cover_right_montage))					//애니메이션 종료시
		{
			_owner->GetMovementComponent()->Activate();
			_playing_high_idle_to_cover_right_montage = false;
			_owner->set_cover();


		}
	}

	if (true == _playing_high_cover_to_idle_left_montage)								// 오른쪽 엄폐하다가 설 때 
	{
		_owner->GetMovementComponent()->Deactivate();

		if (false == Montage_IsPlaying(high_cover_to_idle_left_montage))					//애니메이션 종료시
		{
			_owner->GetMovementComponent()->Activate();
			_playing_high_cover_to_idle_left_montage = false;
			_owner->set_uncover();


		}
	}

	if (true == _playing_high_cover_to_idle_right_montage)								// 왼쪽 엄폐하다가 설 때 
	{
		_owner->GetMovementComponent()->Deactivate();

		if (false == Montage_IsPlaying(high_cover_to_idle_right_montage))					//애니메이션 종료시
		{
			_owner->GetMovementComponent()->Activate();
			_playing_high_cover_to_idle_right_montage = false;
			_owner->set_uncover();


		}
	}


	if (true == _playing_wall_jump_montage)											// 벽 점프
	{
		_owner->GetMovementComponent()->Deactivate();						//무브먼트 중지
		_owner->bUseControllerRotationYaw = false;							//카메라 회전에 따른 캐릭터 회전 중지

		FVector result_location = _owner->_character_skeletal_mesh->GetSocketLocation("Hips");
		if (false == Montage_IsPlaying(wall_jump_montage)) 					//애니메이션 종료시
		{

			_owner->SetActorLocation(result_location);
			_owner->GetMovementComponent()->Activate();						// 무브먼트 재시작
			_owner->bUseControllerRotationYaw = true;						// 다시 카메라 회전에 따른 캐릭터 회전 허용
			_owner->_is_wall_jump = false;
			_playing_wall_jump_montage = false;
		}
	}

}

void UDNCharacterAnimInstance::add_event()
{
	_owner->OnFire.AddDynamic(this , &UDNCharacterAnimInstance::play_fire_montage);
	_owner->StopFire.AddDynamic(this, &UDNCharacterAnimInstance::unlock_cover_animation);
	_owner->OnIdleToCoverL.AddDynamic(this, &UDNCharacterAnimInstance::play_idle_to_cover_left_montage);
	_owner->OnIdleToCoverR.AddDynamic(this, &UDNCharacterAnimInstance::play_idle_to_cover_right_montage);
	_owner->OnCoverToIdleL.AddDynamic(this, &UDNCharacterAnimInstance::play_cover_to_idle_left_montage);
	_owner->OnCoverToIdleR.AddDynamic(this, &UDNCharacterAnimInstance::play_cover_to_idle_right_montage);
	_owner->OnHighIdleToCoverL.AddDynamic(this, &UDNCharacterAnimInstance::play_high_idle_to_cover_left_montage);
	_owner->OnHighIdleToCoverR.AddDynamic(this, &UDNCharacterAnimInstance::play_high_idle_to_cover_right_montage);
	_owner->OnHighCoverToIdleL.AddDynamic(this, &UDNCharacterAnimInstance::play_high_cover_to_idle_left_montage);
	_owner->OnHighCoverToIdleR.AddDynamic(this, &UDNCharacterAnimInstance::play_high_cover_to_idle_right_montage);
	_owner->OnReload.AddDynamic(this, &UDNCharacterAnimInstance::play_reload_montage);
	_owner->OnWallJump.AddDynamic(this, &UDNCharacterAnimInstance::play_wall_jump_montage);
	_owner->OnKnife.AddDynamic(this, &UDNCharacterAnimInstance::play_knife_montage);
	_owner->OnThrow.AddDynamic(this, &UDNCharacterAnimInstance::play_throw_montage);

}

void UDNCharacterAnimInstance::remove_event()
{

}

void UDNCharacterAnimInstance::unlock_cover_animation()
{
	_cover_fire_lock = false;
}


void UDNCharacterAnimInstance::calculate_speed_direction(APawn* pawn_in)
{
	_speed = pawn_in->GetVelocity().Length();

	_direction = UKismetAnimationLibrary::CalculateDirection(pawn_in->GetVelocity(), pawn_in->GetActorRotation());
	
}







void UDNCharacterAnimInstance::play_reload_montage()
{
	// 일반 상태
	if (false == _owner->_cover_now)
	{
		if (false == _playing_reload_montage)
		{
			Montage_Play(reload_montage);
			_playing_reload_montage = true;
		}
	}
	else    //커버 상태
	{
		if (_owner->_moving_left)
		{
			if (_owner->_near_wall->_wall_type == E_WALL_TYPE::WT_HIGH)
			{
				if (false == _playing_reload_montage)
				{
					Montage_Play(reload_high_cover_left_montage);
					_playing_reload_montage = true;
				}
			}
			else
			{
				if (false == _playing_reload_montage)
				{
					Montage_Play(reload_cover_left_montage);
					_playing_reload_montage = true;
				}

				
			}

		}
		else
		{
			if (_owner->_near_wall->_wall_type == E_WALL_TYPE::WT_LOW)
			{
				if (false == _playing_reload_montage)
				{
					Montage_Play(reload_cover_right_montage);
					_playing_reload_montage = true;
				}
			}
			else
			{
				if (false == _playing_reload_montage)
				{
					Montage_Play(reload_high_cover_right_montage);
					_playing_reload_montage = true;
				}
			}
		}
	}

}

void UDNCharacterAnimInstance::play_fire_montage()
{
	Montage_Play(fire_montage);
}


void UDNCharacterAnimInstance::play_idle_to_cover_left_montage()
{
	if (false == _playing_idle_to_cover_left_montage)
	{
		Montage_Play(idle_to_cover_left_montage);
		_playing_idle_to_cover_left_montage = true;
	}
}


void UDNCharacterAnimInstance::play_idle_to_cover_right_montage()
{
	if (false == _playing_idle_to_cover_right_montage)
	{
		Montage_Play(idle_to_cover_right_montage);
		_playing_idle_to_cover_right_montage = true;
	}
}



void UDNCharacterAnimInstance::play_cover_to_idle_left_montage()
{
	if (false == _playing_cover_to_idle_left_montage)
	{
		Montage_Play(cover_to_idle_left_montage);
		_playing_cover_to_idle_left_montage = true;
	}
}

void UDNCharacterAnimInstance::play_cover_to_idle_right_montage()
{
	if (false == _playing_cover_to_idle_right_montage)
	{
		Montage_Play(cover_to_idle_right_montage);
		_playing_cover_to_idle_right_montage = true;
	}
}



void UDNCharacterAnimInstance::play_high_idle_to_cover_left_montage()
{
	if (false == _playing_high_idle_to_cover_left_montage)
	{
		Montage_Play(high_idle_to_cover_left_montage);
		_playing_high_idle_to_cover_left_montage = true;
	}
}


void UDNCharacterAnimInstance::play_high_idle_to_cover_right_montage()
{
	if (false == _playing_high_idle_to_cover_right_montage)
	{
		Montage_Play(high_idle_to_cover_right_montage);
		_playing_high_idle_to_cover_right_montage = true;
	}
}



void UDNCharacterAnimInstance::play_high_cover_to_idle_left_montage()
{
	if (false == _playing_high_cover_to_idle_left_montage)
	{
		Montage_Play(high_cover_to_idle_left_montage);
		_playing_high_cover_to_idle_left_montage = true;
	}
}

void UDNCharacterAnimInstance::play_high_cover_to_idle_right_montage()
{
	if (false == _playing_high_cover_to_idle_right_montage)
	{
		Montage_Play(high_cover_to_idle_right_montage);
		_playing_high_cover_to_idle_right_montage = true;
	}
}






void UDNCharacterAnimInstance::play_wall_jump_montage()
{
	if (nullptr != wall_jump_montage)
	{
		if (false == Montage_IsPlaying(wall_jump_montage) && false == _bIsInAir)
		{
			Montage_Play(wall_jump_montage);
			_playing_wall_jump_montage = true;
		}
	}
}

void UDNCharacterAnimInstance::play_knife_montage()
{
	if (nullptr != knife_montage)
	{
		if (false == Montage_IsPlaying(knife_montage))
		{
			Montage_Play(knife_montage);
			_playing_knife_montage = true;
		}
	}
}

void UDNCharacterAnimInstance::play_throw_montage()
{
	if (nullptr != throw_montage)
	{
		if (false == Montage_IsPlaying(throw_montage))
		{
			Montage_Play(throw_montage);
			_playing_throw_montage = true;
		}
	}
}


void UDNCharacterAnimInstance::play_salute_montage()
{
	if (nullptr != salute_montage)
	{
		if (false == Montage_IsPlaying(salute_montage))
		{
			Montage_Play(salute_montage);
			_playing_salute_montage = true;
		}
	}
}

void UDNCharacterAnimInstance::play_start_sleep_montage()
{
	if (nullptr != start_sleep_montage)
	{
		if (false == Montage_IsPlaying(start_sleep_montage))
		{
			Montage_Play(start_sleep_montage);
			_playing_start_sleep_montage = true;
		}
	}
}

void UDNCharacterAnimInstance::play_loop_sleep_montage()
{
	if (nullptr != loop_sleep_montage)
	{
		if (false == Montage_IsPlaying(loop_sleep_montage))
		{
			Montage_Play(loop_sleep_montage);
			_playing_loop_sleep_montage = true;
		}
	}
}


void UDNCharacterAnimInstance::play_wakeup_montage()
{
	if (nullptr != wakeup_montage)
	{
		if (false == Montage_IsPlaying(wakeup_montage))
		{
			Montage_Play(wakeup_montage);
			_playing_wakeup_montage = true;
		}
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


void UDNCharacterAnimInstance::on_knife_montage_ended()
{
	_playing_knife_montage = false;
	OnKnifeEnd.Broadcast();
}

void UDNCharacterAnimInstance::on_throw_montage_ended()
{
	_playing_throw_montage = false;
	OnThrowEnd.Broadcast();
}

void UDNCharacterAnimInstance::on_salute_montage_ended()
{
	_playing_salute_montage = false;
	_check_salute_ended = true;
}

void UDNCharacterAnimInstance::on_start_sleep_montage_ended()
{
	_playing_start_sleep_montage = false;
	_check_start_sleep_ended = true;
}

void UDNCharacterAnimInstance::on_wakeup_montage_ended()
{
	_playing_wakeup_montage = false;
	_check_wakeup_ended = true;
}