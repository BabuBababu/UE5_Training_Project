


#include "UE5_Training_Project/Character/Animation/DNAirRaptureAnimInstance.h"


// Engine
#include <Camera/CameraComponent.h>
#include <GameFramework/PawnMovementComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <KismetAnimationLibrary.h>

// Character
#include "UE5_Training_Project/Character/DNAirRaptureCharacter.h"

// Component
#include "UE5_Training_Project/Component/DNStatusComponent.h"


UDNAirRaptureAnimInstance::UDNAirRaptureAnimInstance()
{

}





void UDNAirRaptureAnimInstance::NativeBeginPlay()
{

	ADNAirRaptureCharacter* character = Cast<ADNAirRaptureCharacter>(TryGetPawnOwner());

	if (nullptr != character)
		_owner = character;

	add_event();
}

void UDNAirRaptureAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (false == IsValid(TryGetPawnOwner()))
		return;

	if (nullptr == _owner)
		return;

	// Gun
	FRotator rotate = FRotator(_pitch, _yaw, 0.f);
	FRotator target = UKismetMathLibrary::NormalizedDeltaRotator(_owner->GetControlRotation(), _owner->GetActorRotation());


	FRotator result = UKismetMathLibrary::RInterpTo(rotate, target, DeltaSeconds, 15.f);

	_pitch = UKismetMathLibrary::ClampAngle(result.Pitch, _pitch_min, _pitch_max);
	_yaw = result.Yaw;
	_firing = _owner->_is_fire;

	//UE_LOG(LogTemp, Warning, TEXT(" Spider pitch is %f"), _pitch);
	//UE_LOG(LogTemp, Warning, TEXT(" Spider yaw is %f"), _yaw);

	// Legs
	calculate_speed_direction(TryGetPawnOwner());
	_bIsInAir = TryGetPawnOwner()->GetMovementComponent()->IsFalling();


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

}



void UDNAirRaptureAnimInstance::add_event()
{
	// 다양한 공격 기능 넣기 위해서는
	// OnFire 브로드캐스트하면 커먼보스캐릭터에서 다시 변수 여러개 만들고 브로드캐스팅해야할듯
	_owner->OnFire.AddDynamic(this, &UDNAirRaptureAnimInstance::play_fire_1_montage);

}

void UDNAirRaptureAnimInstance::remove_event()
{

}


void UDNAirRaptureAnimInstance::calculate_speed_direction(APawn* pawn_in)
{
	_speed = pawn_in->GetVelocity().Length();

	_direction = UKismetAnimationLibrary::CalculateDirection(pawn_in->GetVelocity(), pawn_in->GetActorRotation());

}

void UDNAirRaptureAnimInstance::play_fire_1_montage()
{
	Montage_Play(fire_1_montage);
}




void UDNAirRaptureAnimInstance::on_die_montage_ended()
{
	_playing_die_montage = false;
	OnDieEnd.Broadcast();
}
