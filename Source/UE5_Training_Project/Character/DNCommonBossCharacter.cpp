


#include "UE5_Training_Project/Character/DNCommonBossCharacter.h"

// Engine
#include <NiagaraComponent.h>
#include <Kismet/KismetMathLibrary.h>

// Animation
#include "UE5_Training_Project/Character/Animation/DNGunSpiderBossAnimInstance.h"

// Component
#include "UE5_Training_Project/Character/Component/DNEnemyLineTrace.h"

// Actor
#include "UE5_Training_Project/Actor/DNBossMissile.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"


ADNCommonBossCharacter::ADNCommonBossCharacter()
{

	_character_sub_skeletal_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SubBodySkeletalMesh"));
	_character_sub_skeletal_mesh->SetupAttachment(_character_skeletal_mesh);


	_niagara_component = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	_niagara_component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


	_enemy_type = E_ENEMY_TYPE::ET_BOSS;
}

void ADNCommonBossCharacter::add_event()
{
	UDNGunSpiderBossAnimInstance* anim_instance = Cast<UDNGunSpiderBossAnimInstance>(_character_skeletal_mesh->GetAnimInstance());
	if (nullptr == anim_instance)
		return;

	anim_instance->OnDieEnd.AddDynamic(this, &ADNCommonCharacter::destroy_object_handler);
	anim_instance->OnReloadEnd.AddDynamic(this, &ADNCommonCharacter::return_to_armed_handler);

	OnDead.AddDynamic(this, &ADNCommonCharacter::reset_fire_state_handler);
	_enemy_line_trace->OnTargetHit.AddDynamic(this, &ADNCommonCharacter::ammo_hit_handler);


}

void ADNCommonBossCharacter::remove_event()
{

	Super::remove_event();
}


void ADNCommonBossCharacter::BeginPlay()
{
	Super::BeginPlay();

	init_base();
}

void ADNCommonBossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 미사일 쿨타임 계산
	if (_fire_2_cool_time_start)
	{
		_fire_2_current_time += DeltaTime;
		if (_fire_2_current_time >= _fire_2_cool_time)
		{
			_fire_2_cool_time_start = false;
			_fire_2_current_time = 0.f;
		}
	}

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

void ADNCommonBossCharacter::init_base()
{

	_fire_1_current_time = 0.f;
	_fire_2_current_time = 0.f;

	_fire_1_cool_time = 12.f;
	_fire_2_cool_time = 8.f;	//이것도 다 데이터테이블로 옮길예정, 근데 공격task에서 쿨타임으로 맞추니 우선적으로 적용됨....
	
	_fire_1_cool_time_start = false;
	_fire_2_cool_time_start = false;

	_missile_array.Empty();

	if (IsValid(_danger_particle))
	{
		_niagara_component->SetAsset(_danger_particle);
		_niagara_component->Deactivate();
	}

}


void ADNCommonBossCharacter::fire_1(ADNCommonCharacter* target_in)
{
	if (nullptr == _fire_1_class)
		return;

	FVector socket_location = _character_sub_skeletal_mesh->GetSocketLocation(FName("FirePoint"));

	if (OBJECT_MANAGER->_enemy_missile_array.Num() < 500)				//500발까지는 그냥 생성, 501발째부터는 생성안하고 기존의 500발중 언액티브된 미사일 발사
	{
		
		ADNBossMissile* bullet = GetWorld()->SpawnActor<ADNBossMissile>(_fire_1_class, socket_location, GetActorRotation()); // 미사일 생성


		bullet->_fire_type = E_FIRE_TYPE::FT_MAIN;
		bullet->SetActorLocation(socket_location);
		bullet->init(); 
		bullet->active_bullet();
		bullet->_owner = this;
		bullet->fire(target_in, socket_location);

		_fire_1_missile = bullet;

		OBJECT_MANAGER->_enemy_missile_array.Add(bullet);

		_fire_1_cool_time_start = true;
	}
	else
	{
		for (auto& un_active_missile : OBJECT_MANAGER->_enemy_missile_array)
		{
			if (false == un_active_missile->_is_active && un_active_missile->_fire_type == E_FIRE_TYPE::FT_MAIN)
			{
				un_active_missile->init();
				un_active_missile->_owner = this;
				un_active_missile->active_bullet();
				un_active_missile->fire(target_in, socket_location);
				_fire_1_missile = un_active_missile;
				_fire_1_cool_time_start = true;
				break;
			}
		}
	}
	

}

void ADNCommonBossCharacter::fire_2(ADNCommonCharacter* target_in)
{
	if (nullptr == _fire_2_class)
		return;

	

	if (OBJECT_MANAGER->_enemy_missile_array.Num() < 500)				//500발까지는 그냥 생성, 501발째부터는 생성안하고 기존의 500발중 언액티브된 미사일 발사
	{
		for (int i = 0; i < 10; ++i)
		{
			FString socket_string = "Rocket_Muzzle_";
			FString num = FString::FromInt(i);
			socket_string.Append(num);
			FVector socket_location = _character_sub_skeletal_mesh->GetSocketLocation(FName(socket_string));

			ADNBossMissile* bullet = GetWorld()->SpawnActor<ADNBossMissile>(_fire_2_class, socket_location, GetActorRotation()); // 미사일 생성

			bullet->_fire_type = E_FIRE_TYPE::FT_SUB;
			bullet->SetActorLocation(socket_location);
			bullet->init();
			bullet->active_bullet();
			bullet->_owner = this;
			bullet->fire(target_in, socket_location);

			_missile_array.Add(bullet);

		}

		_fire_2_cool_time_start = true;
	}
	else
	{
		for (int i = 0; i < 10; ++i)
		{

			FString socket_string = "Rocket_Muzzle_";
			FString num = FString::FromInt(i);
			socket_string.Append(num);
			FVector socket_location = _character_sub_skeletal_mesh->GetSocketLocation(FName(socket_string));

			for (auto& un_active_missile : OBJECT_MANAGER->_enemy_missile_array)
			{
				if (false == un_active_missile->_is_active && un_active_missile->_fire_type == E_FIRE_TYPE::FT_SUB)
				{
					un_active_missile->init();
					un_active_missile->_owner = this;
					un_active_missile->active_bullet();
					un_active_missile->fire(target_in, socket_location);
					_fire_1_missile = un_active_missile;
					_fire_1_cool_time_start = true;
					break;
				}
			}

		}
		
	}
	

}

void ADNCommonBossCharacter::melee_1(ADNCommonCharacter* target_in)
{

}

void ADNCommonBossCharacter::melee_2(ADNCommonCharacter* target_in)
{

}

void ADNCommonBossCharacter::rotate_head(float deleta_time_in, ADNCommonCharacter* target_in)
{
	// 타겟 바라보기
	if (nullptr == target_in)
		return;

	FVector target_location = target_in->GetActorLocation();
	FVector self_actor_location = _character_sub_skeletal_mesh->GetComponentLocation();
	FRotator FocusRotation = UKismetMathLibrary::FindLookAtRotation(self_actor_location, target_location);

	FRotator current_rotation = _character_sub_skeletal_mesh->GetComponentRotation();

	FRotator NewRotation = FMath::RInterpTo(current_rotation, FocusRotation, deleta_time_in, 2.f);

	_character_sub_skeletal_mesh->SetWorldRotation(NewRotation);

}

void ADNCommonBossCharacter::show_smoke()
{
	if (IsValid(_danger_particle))
	{
		if (false == _niagara_component->IsActive())
		{
			_niagara_component->Activate();
		}
	}
		
}

void ADNCommonBossCharacter::hide_smoke()
{
	if (IsValid(_danger_particle))
	{
		if (_niagara_component->IsActive())
		{
			_niagara_component->Deactivate();
		}
	}

}

void ADNCommonBossCharacter::destroy_object_handler()
{
	Super::destroy_object_handler();
	hide_smoke();

}