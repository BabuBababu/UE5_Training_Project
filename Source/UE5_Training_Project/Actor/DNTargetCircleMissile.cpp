


#include "UE5_Training_Project/Actor/DNTargetCircleMissile.h"

// Engine
#include <Engine/Classes/Kismet/GameplayStatics.h>
#include <particles/ParticleSystem.h>
#include <NiagaraComponent.h>


// Util
#include "UE5_Training_Project/Util/DNDamageOperation.h"


ADNTargetCircleMissile::ADNTargetCircleMissile()
{
	_fire_type = E_FIRE_TYPE::FT_TARGETCIRCLE;
}

void ADNTargetCircleMissile::BeginPlay()
{
	Super::BeginPlay();

}

void ADNTargetCircleMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ADNTargetCircleMissile::add_event()
{
	if (IsValid(_box_collision))
		_box_collision->OnComponentBeginOverlap.AddDynamic(this, &ADNTargetCircleMissile::overlap_actor_handler);
}

void ADNTargetCircleMissile::remove_event()
{
	if (IsValid(_box_collision))
		_box_collision->OnComponentBeginOverlap.RemoveDynamic(this, &ADNTargetCircleMissile::overlap_actor_handler);
}

void ADNTargetCircleMissile::init()
{

}


void ADNTargetCircleMissile::fire(FVector location_in)
{
	SetActorEnableCollision(true);

	if (nullptr == _owner)
		return;

	// 여기서는 체력 적음용 나이아가라가 아니라 미사일 모습 파티클 역할
	if (IsValid(_niagara_component))
		_niagara_component->Activate();

	if (IsValid(_missile_fire_soundcue))
		UGameplayStatics::PlaySoundAtLocation(this, _missile_fire_soundcue, GetActorLocation());


	float random_position_x = FMath::FRandRange(-250.f, 250.f);
	float random_position_y = FMath::FRandRange(-250.f, 250.f);

	FVector direction_vector = (_target->GetActorLocation() + FVector(random_position_x, random_position_y, 0.f)) - location_in;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Direction Vector :%s"), *direction_vector.ToString()));

	_projectile_movement_component->Velocity = direction_vector * _projectile_movement_component->InitialSpeed;
	//DrawDebugLine(GetWorld(), location_in, target_in->GetActorLocation(), FColor::Cyan, true, -1, 0, 10);

	_is_active = true;


}



void ADNTargetCircleMissile::destroy_object()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _bomb_particle, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, _bomb_soundcue, GetActorLocation());

	non_active_bullet();

}

void ADNTargetCircleMissile::overlap_actor_handler(class UPrimitiveComponent* selfComp, class AActor* otherActor, UPrimitiveComponent* otherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADNCommonCharacter* actor = Cast<ADNCommonCharacter>(otherActor);
	ADNBullet* missile = Cast<ADNBullet>(otherActor);

	ADNEnemyCharacter* enemy = Cast<ADNEnemyCharacter>(_owner);

	if (nullptr == actor)
	{
		// 나머지
		if (IsValid(_bomb_soundcue) && nullptr != _bomb_2_particle)				// 파티클 및 사운드
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _bomb_2_particle, GetActorLocation());

			DNDamageOperation::radial_damage_to_all(GetWorld(), 250.f, GetActorLocation(), 0.f, _owner);		
			destroy_object();
		}
	}
	else
	{
		if (E_CHARACTER_TYPE::CT_ENEMY != actor->_character_type && nullptr == missile)					// 니케,지휘관이면서 미사일이 아닌 경우 충돌
		{
			if (IsValid(_bomb_soundcue) && nullptr != _bomb_2_particle)									// 파티클 및 사운드
			{
				if (nullptr != enemy)
				{
					// 이 미사일 사용할 몬스터들은 이넘값 구분해서 나눠서 사용하기
					if (enemy->_enemy_type == E_ENEMY_TYPE::ET_BOSS)
					{
						UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _bomb_2_particle, GetActorLocation());

						DNDamageOperation::radial_damage_to_all(GetWorld(), 400.f, GetActorLocation(), 0.f, _owner);		// 보스
						destroy_object();
					}
				}
			}
		}
	}
}