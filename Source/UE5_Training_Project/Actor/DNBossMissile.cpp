


#include "UE5_Training_Project/Actor/DNBossMissile.h"

// Engine
#include <Components/SplineComponent.h>
#include <Engine/Classes/Kismet/GameplayStatics.h>
#include <Perception/AIPerceptionStimuliSourceComponent.h>


// Util
#include "UE5_Training_Project/Util/DNDamageOperation.h"





ADNBossMissile::ADNBossMissile()
{

	_spline_component = CreateDefaultSubobject<USplineComponent>(TEXT("SplineForMove"));

	_perception_stimuli_source = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("PerceptionStimuliSource"));
	// 감각 등록 및 실행은 BP에서 합니다

	_is_active = false;
	_boost_time = 10.f;
	_boost_current_time = 0.f;
	_is_boost = false;
	
}

void ADNBossMissile::BeginPlay()
{
	Super::BeginPlay();

}

void ADNBossMissile::Tick(float DeltaTime)
{
	if (false == _is_active)
		return;

	if(_fire_type == E_FIRE_TYPE::FT_MAIN)
		Super::Tick(DeltaTime);

	if (_fire_type == E_FIRE_TYPE::FT_SUB)
	{
		if (false == _is_boost)
		{
			_boost_current_time = _boost_current_time + DeltaTime;
			if (_boost_current_time > _boost_time)
			{
				_projectile_movement_component->MaxSpeed = 2000.f;
				fire(GetActorLocation());
				_boost_current_time = 0.f;
				_is_boost = true;
			}

		}
	}
	


}


void ADNBossMissile::add_event()
{
	Super::add_event();
}

void ADNBossMissile::remove_event()
{

	Super::remove_event();
}


void ADNBossMissile::init()
{
	_current_hp = _max_hp;

	if (_fire_type == E_FIRE_TYPE::FT_SUB)
	{
		_projectile_movement_component->MaxSpeed = 10.0f;
	}
}

void ADNBossMissile::play_damaged_sound()
{

}

void ADNBossMissile::destroy_object()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _bomb_particle, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, _bomb_soundcue, GetActorLocation());

	non_active_bullet();

	if (_fire_type == E_FIRE_TYPE::FT_SUB)
	{
		_projectile_movement_component->MaxSpeed = 10.0f;
		_is_boost = false;
	}
	
	OnDestroyMissile.Broadcast(this);
}


void ADNBossMissile::overlap_actor_handler(class UPrimitiveComponent* selfComp, class AActor* otherActor, UPrimitiveComponent* otherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


	ADNCommonCharacter* actor = Cast<ADNCommonCharacter>(otherActor);
	ADNBossMissile* missle = Cast<ADNBossMissile>(otherActor);

	ADNEnemyCharacter* enemy = Cast<ADNEnemyCharacter>(_owner);


	
	if (nullptr == actor)
	{
		// 나머지
		if (IsValid(_bomb_soundcue) && nullptr != _bomb_particle)				// 파티클 및 사운드
		{

			if (_fire_type == E_FIRE_TYPE::FT_SUB)
			{
				DNDamageOperation::radial_damage_to_all(GetWorld(), 25.f, GetActorLocation(), 100.f, _owner);		// fire 2
				destroy_object();
			}
			else if (_fire_type == E_FIRE_TYPE::FT_MAIN)															// fire 1
			{
				if (nullptr != enemy)
				{
					if (enemy->_enemy_type == E_ENEMY_TYPE::ET_BOSS)
						DNDamageOperation::radial_damage_to_all(GetWorld(), 100.f, GetActorLocation(), 500.f, _owner);		// 보스
					else if (enemy->_enemy_type == E_ENEMY_TYPE::ET_RANGER_LC)
						DNDamageOperation::radial_damage_to_all(GetWorld(), 20.f, GetActorLocation(), 100.f, _owner);		// 랩쳐 큐브 


					destroy_object();
				}
				
			}
			else if (_fire_type == E_FIRE_TYPE::FT_NONE)
			{
				DNDamageOperation::radial_damage_to_all(GetWorld(), 25.f, GetActorLocation(), 200.f, _owner);		// fire 1 고정 하지만 딜은 약하게
				destroy_object();
			}
		}

		
	}
	else
	{
		if (E_CHARACTER_TYPE::CT_ENEMY != actor->_character_type)					// 자신,아군 충돌 체크
		{
			if (IsValid(_bomb_soundcue) && nullptr != _bomb_particle)				// 파티클 및 사운드
			{
				if (_fire_type == E_FIRE_TYPE::FT_SUB)
				{
					DNDamageOperation::radial_damage_to_all(GetWorld(), 25.f, GetActorLocation(), 100.f, _owner);		// fire 2
					destroy_object();
				}
				else if (_fire_type == E_FIRE_TYPE::FT_MAIN)
				{
					if (nullptr != enemy)
					{
						if (enemy->_enemy_type == E_ENEMY_TYPE::ET_BOSS)
							DNDamageOperation::radial_damage_to_all(GetWorld(), 100.f, GetActorLocation(), 500.f, _owner);		// 보스
						else if (enemy->_enemy_type == E_ENEMY_TYPE::ET_RANGER_LC)
							DNDamageOperation::radial_damage_to_all(GetWorld(), 20.f, GetActorLocation(), 100.f, _owner);		// 랩쳐 큐브 

						destroy_object();
					}
				}
			}
		}
	}

}
