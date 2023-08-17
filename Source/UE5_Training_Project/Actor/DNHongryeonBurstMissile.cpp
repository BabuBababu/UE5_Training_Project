


#include "UE5_Training_Project/Actor/DNHongryeonBurstMissile.h"


// Engine
#include <Engine/Classes/Kismet/GameplayStatics.h>
#include <particles/ParticleSystem.h>
#include <NiagaraComponent.h>


// Util
#include "UE5_Training_Project/Util/DNDamageOperation.h"


ADNHongryeonBurstMissile::ADNHongryeonBurstMissile()
{
	_fire_type = E_FIRE_TYPE::FT_NIKKE_LC; // 일단 버스트 스킬도 이 타입으로 해놓습니다.
}

void ADNHongryeonBurstMissile::BeginPlay()
{
	Super::BeginPlay();

}

void ADNHongryeonBurstMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ADNHongryeonBurstMissile::add_event()
{
	if (IsValid(_box_collision))
		_box_collision->OnComponentBeginOverlap.AddDynamic(this, &ADNHongryeonBurstMissile::overlap_actor_handler);
}

void ADNHongryeonBurstMissile::remove_event()
{
	if (IsValid(_box_collision))
		_box_collision->OnComponentBeginOverlap.RemoveDynamic(this, &ADNHongryeonBurstMissile::overlap_actor_handler);
}

void ADNHongryeonBurstMissile::init()
{

}


void ADNHongryeonBurstMissile::fire(FVector location_in)
{

	if (nullptr == _owner)
		return;

	// 여기서는 체력 적음용 나이아가라가 아니라 미사일 모습 파티클 역할
	if (IsValid(_niagara_component))
		_niagara_component->Activate();

	if (IsValid(_missile_fire_soundcue))
		UGameplayStatics::PlaySoundAtLocation(this, _missile_fire_soundcue, GetActorLocation());

	FVector direction_vector = _target->GetActorLocation() - location_in;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Direction Vector :%s"), *direction_vector.ToString()));

	_projectile_movement_component->Velocity = direction_vector * _projectile_movement_component->InitialSpeed;
	//DrawDebugLine(GetWorld(), location_in, target_in->GetActorLocation(), FColor::Cyan, true, -1, 0, 10);

	_is_active = true;


}



void ADNHongryeonBurstMissile::destroy_object()
{
	UGameplayStatics::PlaySoundAtLocation(this, _bomb_soundcue, GetActorLocation());

	non_active_bullet();

}

void ADNHongryeonBurstMissile::overlap_actor_handler(class UPrimitiveComponent* selfComp, class AActor* otherActor, UPrimitiveComponent* otherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADNCommonCharacter* actor = Cast<ADNCommonCharacter>(otherActor);
	ADNBullet* missile = Cast<ADNBullet>(otherActor);

	// 벽에 부딫힐 경우 소멸
	// 최종 타겟에 부딫힐 경우 소멸
	// 그 전 적들에게 부딫힐 경우 소멸 X
	// 적 미사일에는 부딫히지 않습니다.

	if (otherActor != _owner)
	{
		if (nullptr == actor)
		{
			// 나머지
			if (IsValid(_bomb_soundcue) && nullptr != _bomb_2_particle)				// 파티클 및 사운드
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _bomb_2_particle, GetActorLocation());

				DNDamageOperation::radial_damage_to_all(GetWorld(), 300.f, GetActorLocation(), 200.f, _owner);
				destroy_object();
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" Missile Bomb nothing")));

			}
		}
		else
		{
			if (E_CHARACTER_TYPE::CT_ENEMY == actor->_character_type && nullptr == missile)					// 적이면서 미사일이 아닌 경우 충돌
			{
				if (IsValid(_bomb_soundcue) && nullptr != _bomb_2_particle && nullptr != _bomb_particle)	// 파티클 및 사운드
				{
					if (_target == actor)
					{
						UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _bomb_2_particle, GetActorLocation(), GetActorRotation(), FVector(1.5f));
						UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _bomb_particle, GetActorLocation());

						DNDamageOperation::radial_damage_to_all(GetWorld(), 1200.f, GetActorLocation(), 800.f, _owner);
						destroy_object();
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" Missile Bomb target")));

					}
					else
					{
						UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _bomb_2_particle, GetActorLocation());

						DNDamageOperation::radial_damage_to_all(GetWorld(), 600.f, GetActorLocation(), 400.f, _owner);
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" Missile Bomb other")));

					}
				}
			}
		}
	}

}