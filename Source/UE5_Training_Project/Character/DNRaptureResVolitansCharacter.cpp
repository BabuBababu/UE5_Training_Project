


#include "UE5_Training_Project/Character/DNRaptureResVolitansCharacter.h"


// Engine
#include <NiagaraComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <Engine/Classes/Kismet/GameplayStatics.h>

// Animation
#include "UE5_Training_Project/Character/Animation/DNAirRaptureAnimInstance.h"


// Actor
#include "UE5_Training_Project/Actor/DNBossMissile.h"
#include "UE5_Training_Project/Actor/DNPatternTargetActor.h"

// Component
#include "UE5_Training_Project/Character/Component/DNEnemyLineTrace.h"
#include "UE5_Training_Project/Component/DNStatusComponent.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"



ADNRaptureResVolitansCharacter::ADNRaptureResVolitansCharacter()
{
	_parts_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Parts Mesh"));
	_parts_mesh->SetupAttachment(_character_skeletal_mesh);

	_danger_component = CreateDefaultSubobject<UNiagaraComponent>(TEXT("danger NiagaraComponent"));
	_danger_component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


	_attack_niagara_component = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Attack NiagaraComponent"));
	_attack_niagara_component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	_damaged_niagara_component = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Damaged NiagaraComponent"));
	_damaged_niagara_component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	_flying_niagara_component = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Flying NiagaraComponent"));
	_flying_niagara_component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	_destroyed_parts = false;
	_enemy_type = E_ENEMY_TYPE::ET_BOSS_RESVOLITAN;

}

void ADNRaptureResVolitansCharacter::BeginPlay()
{
	Super::BeginPlay();

	init_base();
}

void ADNRaptureResVolitansCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	


	// 미사일 쿨타임 계산
	if (_fire_2_cool_time_start)
	{
		_fire_2_current_time += DeltaTime;
		if (_fire_2_current_time >= _fire_1_cool_time)
		{
			_fire_2_cool_time_start = false;
			_fire_2_current_time = 0.f;
		}
	}

	if (_fire_3_cool_time_start)
	{
		_fire_3_current_time += DeltaTime;
		if (_fire_3_current_time >= _fire_1_cool_time)
		{
			_fire_3_cool_time_start = false;
			_fire_3_current_time = 0.f;
		}
	}

	if (_target_circle_cool_time_start)
	{
		_target_circle_current_cool_time += DeltaTime;
		if (_target_circle_current_cool_time >= _target_circle_cool_time)
		{
			_target_circle_cool_time_start = false;
			_target_circle_current_cool_time = 0.f;
		}
	}

	// 타겟서클패턴 공격
	if (_is_target_circle_success)
	{
		//target_circle_pattern_attack();
		_is_target_circle_success = false;
	}


	if (false == _destroyed_parts)
	{
		if (_status->get_current_hp() / _status->get_max_hp() < 0.5f) // 50% 미만
			destroy_parts();
	}
}

void ADNRaptureResVolitansCharacter::add_event()
{
	UDNAirRaptureAnimInstance* anim_instance = Cast<UDNAirRaptureAnimInstance>(_character_skeletal_mesh->GetAnimInstance());
	if (nullptr == anim_instance)
		return;

	anim_instance->OnDieEnd.AddDynamic(this, &ADNCommonCharacter::destroy_object_handler);

	OnDead.AddDynamic(this, &ADNCommonCharacter::reset_fire_state_handler);
	_enemy_line_trace->OnTargetHit.AddDynamic(this, &ADNCommonCharacter::ammo_hit_handler);
}


void ADNRaptureResVolitansCharacter::remove_event()
{


}

void ADNRaptureResVolitansCharacter::init_base()
{

	_fire_1_current_time = 0.f;
	_fire_1_cool_time = 10.f;	//이것도 다 데이터테이블로 옮길예정
	_fire_1_cool_time_start = false;

	_fire_2_current_time = 0.f;
	_fire_2_cool_time = 6.f;	//이것도 다 데이터테이블로 옮길예정
	_fire_2_cool_time_start = false;

	_fire_3_current_time = 0.f;
	_fire_3_cool_time = 8.f;	//이것도 다 데이터테이블로 옮길예정
	_fire_3_cool_time_start = false;

	_target_circle_cool_time_start = false;

	if (IsValid(_danger_particle))
	{
		_danger_component->SetAsset(_danger_particle);
		_danger_component->Deactivate();
	}
	if (IsValid(_attack_particle))
	{
		_attack_niagara_component->SetAsset(_attack_particle);
		_attack_niagara_component->Deactivate();
	}
	if (IsValid(_damaged_particle))
	{
		_damaged_niagara_component->SetAsset(_damaged_particle);
		_damaged_niagara_component->Deactivate();
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("init base")));
}


void ADNRaptureResVolitansCharacter::fire_1(ADNCommonCharacter* target_in)
{
	if (nullptr == _fire_1_class)
		return;

	FVector socket_location = _character_skeletal_mesh->GetSocketLocation(FName("Fire1"));

	if (OBJECT_MANAGER->_enemy_missile_array.Num() < 1000)				//1000발까지는 그냥 생성, 1001발째부터는 생성안하고 기존의 500발중 언액티브된 미사일 발사
	{

		ADNBossMissile* bullet = GetWorld()->SpawnActor<ADNBossMissile>(_fire_1_class, socket_location, GetActorRotation()); // 미사일 생성


		bullet->_fire_type = E_FIRE_TYPE::FT_RESVOLITANS1;
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
			if (false == un_active_missile->_is_active && un_active_missile->_fire_type == E_FIRE_TYPE::FT_RESVOLITANS1)
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


void ADNRaptureResVolitansCharacter::fire_2(ADNCommonCharacter* target_in)
{
	if (nullptr == _fire_2_class)
		return;



	if (OBJECT_MANAGER->_enemy_missile_array.Num() < 1000)				//500발까지는 그냥 생성, 1001발째부터는 생성안하고 기존의 500발중 언액티브된 미사일 발사
	{
		for (int32 count = 0; count < 3; ++count)
		{
			for (int32 i = 0; i < 5; ++i)
			{
				FString socket_string = "FireCannon_";
				FString num = FString::FromInt(i);
				socket_string.Append(num);
				FVector socket_location = _character_skeletal_mesh->GetSocketLocation(FName(socket_string));

				ADNBossMissile* bullet = GetWorld()->SpawnActor<ADNBossMissile>(_fire_2_class, socket_location, GetActorRotation()); // 미사일 생성

				bullet->_fire_type = E_FIRE_TYPE::FT_SUB;
				bullet->SetActorLocation(socket_location);
				bullet->init();
				bullet->active_bullet();
				bullet->_owner = this;
				bullet->_target = target_in;
				bullet->fire(socket_location);

				OBJECT_MANAGER->_enemy_missile_array.Add(bullet);		//이 코드 안넣어서 문제가 있나? 06.23 추가
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Now Missile Array Count : %d"), OBJECT_MANAGER->_enemy_missile_array.Num()));

			}
		}
		

		_fire_2_cool_time_start = true;
	}
	else
	{
		for (int32 count = 0; count < 3; ++count)
		{
			for (int32 i = 0; i < 5; ++i)
			{

				FString socket_string = "FireCannon_";
				FString num = FString::FromInt(i);
				socket_string.Append(num);
				FVector socket_location = _character_skeletal_mesh->GetSocketLocation(FName(socket_string));

				for (auto& un_active_missile : OBJECT_MANAGER->_enemy_missile_array)
				{
					if (false == un_active_missile->_is_active && un_active_missile->_fire_type == E_FIRE_TYPE::FT_SUB)
					{
						un_active_missile->init();
						un_active_missile->_owner = this;
						un_active_missile->SetActorLocation(socket_location);
						un_active_missile->active_bullet();
						un_active_missile->_target = target_in;
						un_active_missile->fire(socket_location);
						_fire_2_cool_time_start = true;
						break;
					}
				}

			}
		}

	}


}

void ADNRaptureResVolitansCharacter::fire_3(ADNCommonCharacter* target_in)
{
	if (nullptr == _fire_3_class)
		return;

	FVector socket_location = _character_skeletal_mesh->GetSocketLocation(FName("Fire1"));

	if (OBJECT_MANAGER->_enemy_missile_array.Num() < 1000)				//1000발까지는 그냥 생성, 1001발째부터는 생성안하고 기존의 500발중 언액티브된 미사일 발사
	{

		ADNBossMissile* bullet = GetWorld()->SpawnActor<ADNBossMissile>(_fire_3_class, socket_location, GetActorRotation()); // 미사일 생성


		bullet->_fire_type = E_FIRE_TYPE::FT_RESVOLITANS3;
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
			if (false == un_active_missile->_is_active && un_active_missile->_fire_type == E_FIRE_TYPE::FT_RESVOLITANS3)
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

void ADNRaptureResVolitansCharacter::target_circle_pattern_spawn()
{
	// 생성 위치
	FVector socket_location = _character_skeletal_mesh->GetSocketLocation(FName("TargetCircle1"));

	// 타겟서클액터 생성
	if (IsValid(_target_circle_class))
	{
		ADNPatternTargetActor* target_actor = GetWorld()->SpawnActor<ADNPatternTargetActor>(_target_circle_class, socket_location, FRotator::ZeroRotator);
		target_actor->set_owner(this);
		target_actor->init();
	}


}

void ADNRaptureResVolitansCharacter::target_circle_pattern_attack(ADNCommonCharacter* target_in)
{

}

void ADNRaptureResVolitansCharacter::play_damaged_parts()
{
	if (IsValid(_damaged_niagara_component))
	{
		if (false == _damaged_niagara_component->IsActive())
		{
			_damaged_niagara_component->Activate();
		}
	}
}


void ADNRaptureResVolitansCharacter::destroy_parts()
{

	if (IsValid(_parts_mesh))
	{
		if(IsValid(_damaged_parts_soundcue))
			UGameplayStatics::PlaySoundAtLocation(this, _damaged_parts_soundcue, GetActorLocation());

		play_damaged_parts();
		_parts_mesh->SetVisibility(false);
		_parts_mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		_destroyed_parts = true;
	}
}


void ADNRaptureResVolitansCharacter::show_smoke()
{
	if (IsValid(_danger_particle) && IsValid(_danger_component))
	{
		if (false == _danger_component->IsActive())
		{
			_danger_component->Activate();
		}
	}

}

void ADNRaptureResVolitansCharacter::hide_smoke()
{
	if (IsValid(_danger_particle) && IsValid(_danger_component))
	{
		if (_danger_component->IsActive())
		{
			_danger_component->Deactivate();
		}
	}

}


void ADNRaptureResVolitansCharacter::destroy_object_handler()
{
	Super::destroy_object_handler();
	hide_smoke();

	_parts_mesh->SetVisibility(true);
	_parts_mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	_destroyed_parts = false;

	// 공격시,부위파괴시 파티클은 한번만 재생이므로 일단 hide,show_smoke처럼 만들진 않았음
}