﻿


#include "UE5_Training_Project/Character/DNRaptureResVolitansCharacter.h"


// Engine
#include <NiagaraComponent.h>
#include <Kismet/KismetMathLibrary.h>

// Animation
#include "UE5_Training_Project/Character/Animation/DNAirRaptureAnimInstance.h"


// Actor
#include "UE5_Training_Project/Actor/DNBossMissile.h"

// Component
#include "UE5_Training_Project/Character/Component/DNEnemyLineTrace.h"
#include "UE5_Training_Project/Component/DNStatusComponent.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"



ADNRaptureResVolitansCharacter::ADNRaptureResVolitansCharacter()
{
	_flying_niagara_component = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Flying NiagaraComponent"));
	_flying_niagara_component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	_attack_niagara_component = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Attack NiagaraComponent"));
	_attack_niagara_component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

void ADNRaptureResVolitansCharacter::BeginPlay()
{
	Super::BeginPlay();

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
	_enemy_type = E_ENEMY_TYPE::ET_BOSS_RESVOLITAN;

	_fire_1_current_time = 0.f;
	_fire_1_cool_time = 10.f;	//이것도 다 데이터테이블로 옮길예정
	_fire_1_cool_time_start = false;

	_fire_2_current_time = 0.f;
	_fire_2_cool_time = 6.f;	//이것도 다 데이터테이블로 옮길예정
	_fire_2_cool_time_start = false;

	_fire_3_current_time = 0.f;
	_fire_3_cool_time = 8.f;	//이것도 다 데이터테이블로 옮길예정
	_fire_3_cool_time_start = false;

	if (IsValid(_danger_particle))
	{
		_niagara_component->SetAsset(_danger_particle);
		_niagara_component->Deactivate();
	}

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
