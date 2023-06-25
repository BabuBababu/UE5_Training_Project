


#include "UE5_Training_Project/Character/DNAirRaptureCharacter.h"


// Engine
#include <GameFramework/FloatingPawnMovement.h>
#include <Engine/Classes/Kismet/GameplayStatics.h>
#include <Components/AudioComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <NiagaraComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <Components/CapsuleComponent.h>

// Actor
#include "UE5_Training_Project/Actor/DNBossMissile.h"

// Animation
#include "UE5_Training_Project/Character/Animation/DNAirRaptureAnimInstance.h"

// Component
#include "UE5_Training_Project/Character/Component/DNEnemyLineTrace.h"
#include "UE5_Training_Project/Component/DNStatusComponent.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"




ADNAirRaptureCharacter::ADNAirRaptureCharacter()
{

	_audio_component = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	_audio_component->SetupAttachment(RootComponent);

	_floting_movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
	_floting_movement->SetUpdatedComponent(RootComponent);


	_enemy_type = E_ENEMY_TYPE::ET_AIR_LC;
}

void ADNAirRaptureCharacter::BeginPlay()
{
	Super::BeginPlay();


	init_base();
}

void ADNAirRaptureCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	set_flying_move(DeltaTime);

	// 미사일 쿨타임 계산
	if (_fire_1_cool_time_start)
	{
		_fire_1_current_time += DeltaTime;
		if (_fire_1_current_time >= _fire_1_cool_time)
		{
			_fire_1_cool_time_start = false;
			_fire_1_current_time = 0.f;
		}
	}

}



void ADNAirRaptureCharacter::add_event()
{
	UDNAirRaptureAnimInstance* anim_instance = Cast<UDNAirRaptureAnimInstance>(_character_skeletal_mesh->GetAnimInstance());
	if (nullptr == anim_instance)
		return;

	anim_instance->OnDieEnd.AddDynamic(this, &ADNCommonCharacter::destroy_object_handler);
	
	OnDead.AddDynamic(this, &ADNCommonCharacter::reset_fire_state_handler);
	_enemy_line_trace->OnTargetHit.AddDynamic(this, &ADNCommonCharacter::ammo_hit_handler);


}

void ADNAirRaptureCharacter::remove_event()
{

}


void ADNAirRaptureCharacter::init_base()
{

	_fire_1_current_time = 0.f;
	_fire_1_cool_time = 10.f;	//이것도 다 데이터테이블로 옮길예정
	_fire_1_cool_time_start = false;



}


void ADNAirRaptureCharacter::set_flying_move(float DeltaTime)
{
	if (_status->_dead)
	{
		return;
	}

	// 공중에 떠있는 것
	FVector NewLocation = GetActorLocation();

	float DeltaHeight = (FMath::Sin(_running_time + DeltaTime) - FMath::Sin(_running_time));

	NewLocation.X += DeltaHeight * XValue;
	NewLocation.Y += DeltaHeight * YValue;
	NewLocation.Z += DeltaHeight * ZValue;

	_running_time += DeltaTime;

	SetActorLocation(NewLocation);

}

void ADNAirRaptureCharacter::init_missile()
{
	//임시 사용중단
}


void ADNAirRaptureCharacter::fire_1(ADNCommonCharacter* target_in)
{
	if (nullptr == _fire_1_class)
		return;

	FVector socket_location = _character_skeletal_mesh->GetSocketLocation(FName("FirePoint"));

	if (OBJECT_MANAGER->_enemy_missile_array.Num() < 1000)				//1000발까지는 그냥 생성, 1001발째부터는 생성안하고 기존의 500발중 언액티브된 미사일 발사
	{

		ADNBossMissile* bullet = GetWorld()->SpawnActor<ADNBossMissile>(_fire_1_class, socket_location, GetActorRotation()); // 미사일 생성


		bullet->_fire_type = E_FIRE_TYPE::FT_DISCUS;
		bullet->SetActorLocation(socket_location);
		bullet->init();
		bullet->active_bullet();
		bullet->_owner = this;
		bullet->_target = target_in;
		bullet->fire(socket_location);


		OBJECT_MANAGER->_enemy_missile_array.Add(bullet);

		_fire_1_cool_time_start = true;

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Now Missile Array Count : %d"), OBJECT_MANAGER->_enemy_missile_array.Num()));

	}
	else
	{
		for (auto& un_active_missile : OBJECT_MANAGER->_enemy_missile_array)
		{
			if (false == un_active_missile->_is_active && un_active_missile->_fire_type == E_FIRE_TYPE::FT_DISCUS)
			{
				un_active_missile->init();
				un_active_missile->_owner = this;
				un_active_missile->SetActorLocation(socket_location);
				un_active_missile->active_bullet();
				un_active_missile->_target = target_in;
				un_active_missile->fire(socket_location);



				/*un_active_missile->_actor_static_mesh->SetComponentLocation(socket_location);
				un_active_missile->_box_collision->SetComponentLocation(socket_location);*/
				_fire_1_cool_time_start = true;
				break;
			}
		}
	}

	OnFire.Broadcast();
}



void ADNAirRaptureCharacter::destroy_object_handler()
{
	GetCapsuleComponent()->SetEnableGravity(true);
	GetCharacterMovement()->GravityScale = 0.f;
	_floting_movement->SetActive(true);

	Super::destroy_object_handler();
}