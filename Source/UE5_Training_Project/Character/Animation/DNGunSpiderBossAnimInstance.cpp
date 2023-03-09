


#include "UE5_Training_Project/Character/Animation/DNGunSpiderBossAnimInstance.h"

// Engine
#include <Camera/CameraComponent.h>
#include <GameFramework/PawnMovementComponent.h>
#include <Kismet/KismetMathLibrary.h>

// Character
#include "UE5_Training_Project/Character/DNCommonBossCharacter.h"

// Component
#include "UE5_Training_Project/Component/DNStatusComponent.h"



UDNGunSpiderBossAnimInstance::UDNGunSpiderBossAnimInstance()
{

}



void UDNGunSpiderBossAnimInstance::NativeBeginPlay()
{

	ADNCommonBossCharacter* character = Cast<ADNCommonBossCharacter>(TryGetPawnOwner());

	if (nullptr != character)
		_owner = character;

	add_event();
}

void UDNGunSpiderBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (false == IsValid(TryGetPawnOwner()))
		return;

	if (nullptr == _owner)
		return;

	// Gun
	FRotator rotate = FRotator(_pitch, _yaw, 0.f);
	FRotator target = UKismetMathLibrary::NormalizedDeltaRotator(_owner->GetControlRotation(), _owner->GetActorRotation());


	FRotator result = UKismetMathLibrary::RInterpTo(rotate,target,DeltaSeconds,15.f);

	_pitch = UKismetMathLibrary::ClampAngle(result.Pitch,_pitch_min,_pitch_max);
	_yaw = result.Yaw;
	_firing = _owner->_is_fire;

	// Legs
	calculate_speed_direction(TryGetPawnOwner());
	_bIsInAir = TryGetPawnOwner()->GetMovementComponent()->IsFalling();

}



void UDNGunSpiderBossAnimInstance::add_event()
{
	// 다양한 공격 기능 넣기 위해서는
	// OnFire 브로드캐스트하면 커먼보스캐릭터에서 다시 변수 여러개 만들고 브로드캐스팅해야할듯
	_owner->OnFire.AddDynamic(this, &UDNGunSpiderBossAnimInstance::play_fire_1_montage);
	_owner->OnReload.AddDynamic(this, &UDNGunSpiderBossAnimInstance::play_reload_montage);

}

void UDNGunSpiderBossAnimInstance::remove_event()
{

}




void UDNGunSpiderBossAnimInstance::calculate_speed_direction(APawn* pawn_in)
{
	_speed = pawn_in->GetVelocity().Length();

	_direction = CalculateDirection(pawn_in->GetVelocity(), pawn_in->GetActorRotation());

}

void UDNGunSpiderBossAnimInstance::play_fire_1_montage()
{

}


void UDNGunSpiderBossAnimInstance::play_fire_2_montage()
{

}


void UDNGunSpiderBossAnimInstance::play_melee_1_montage()
{

}


void UDNGunSpiderBossAnimInstance::play_melee_2_montage()
{

}



void UDNGunSpiderBossAnimInstance::play_reload_montage()
{

}





void UDNGunSpiderBossAnimInstance::on_die_montage_ended()
{
	_playing_die_montage = false;
	OnDieEnd.Broadcast();
}

void UDNGunSpiderBossAnimInstance::on_reload_montage_ended()
{
	_playing_reload_montage = false;
	OnReloadEnd.Broadcast();
}