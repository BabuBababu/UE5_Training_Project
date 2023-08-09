


#include "UE5_Training_Project/Character/DNHeliCommonCharacter.h"

// Engine
#include <GameFramework/FloatingPawnMovement.h>
#include <Engine/Classes/Kismet/GameplayStatics.h>
#include <Components/AudioComponent.h>

// Actor
#include "UE5_Training_Project/Actor/DNBullet.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"

ADNHeliCommonCharacter::ADNHeliCommonCharacter()
{
	// Mesh
	_sub_character_skeletal_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SubSkeletalMesh"));
	_sub_character_skeletal_mesh->SetupAttachment(RootComponent);

	_audio_component = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	_audio_component->SetupAttachment(RootComponent);

	_floting_movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
	_floting_movement->SetUpdatedComponent(RootComponent);


	init_base();
}

void ADNHeliCommonCharacter::BeginPlay()
{
	Super::BeginPlay();

	init_missile();																			//미사일 초기화
	
}

void ADNHeliCommonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	set_flying_move(DeltaTime);

	// 미사일 쿨타임 계산
	if (_missile_cool_time_start)
	{
		_missile_current_time += DeltaTime;
		if (_missile_current_time >= _missile_cool_time)
		{
			_missile_cool_time_start = false;
			_missile_current_time = 0.f;
		}
	}

}

void ADNHeliCommonCharacter::add_event()
{

}

void ADNHeliCommonCharacter::remove_event()
{

}


void ADNHeliCommonCharacter::init_base()
{
	_character_type = E_CHARACTER_TYPE::CT_HELI;

	_rotor_mast = 0.f;
	_rotor_back = 0.f;
	_rotor_minigun = 0.f;
	_missile_current_time = 0.f;
	_missile_cool_time = 10.f;	//이것도 다 데이터테이블로 옮길예정
	_missile_cool_time_start = false;

	_missile = nullptr;

}


void ADNHeliCommonCharacter::set_flying_move(float DeltaTime)
{
	// 공중에 떠있는 것
	FVector NewLocation = GetActorLocation();

	float DeltaHeight = (FMath::Sin(_running_time + DeltaTime) - FMath::Sin(_running_time));

	NewLocation.X += DeltaHeight * XValue;
	NewLocation.Y += DeltaHeight * YValue;
	NewLocation.Z += DeltaHeight * ZValue;

	_running_time += DeltaTime;

	SetActorLocation(NewLocation);

	//날개 움직임

	if (_rotor_mast < -360.f)
	{
		_rotor_mast = 0.f;
	}
	if (_rotor_back < -360.f)
	{
		_rotor_back = 0.f;
	}

	_rotor_mast -= 20.f;
	_rotor_back -= 20.f;

}

void ADNHeliCommonCharacter::init_missile()
{
	//임시 사용중단
}


void ADNHeliCommonCharacter::fire_missile(ADNCommonCharacter* target_in)
{
	if (IsValid(_missile_class))
	{
		FVector socket_location = _character_skeletal_mesh->GetSocketLocation(FName("Rocket_Muzzle_L"));
		ADNBullet* bullet = GetWorld()->SpawnActor<ADNBullet>(_missile_class, socket_location, GetActorRotation()); // 미사일 생성
		bullet->SetActorLocation(socket_location);
		bullet->SetActorRotation(GetActorRotation());
		bullet->_owner = this;
		bullet->_target = target_in;
		bullet->fire(socket_location);
		bullet->_fire_type = E_FIRE_TYPE::FT_HELI;
		_missile_cool_time_start = true;

		_missile = bullet;
	}

}