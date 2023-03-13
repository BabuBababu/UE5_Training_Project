


#include "UE5_Training_Project/Actor/DNBossMissile.h"

// Engine
#include <Components/SplineComponent.h>
#include <Engine/Classes/Kismet/GameplayStatics.h>


// Util
#include "UE5_Training_Project/Util/DNDamageOperation.h"


ADNBossMissile::ADNBossMissile()
{

	_spline_component = CreateDefaultSubobject<USplineComponent>(TEXT("SplineForMove"));

	
}

void ADNBossMissile::BeginPlay()
{
	Super::BeginPlay();

}

void ADNBossMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


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

}

void ADNBossMissile::play_damaged_sound()
{

}

void ADNBossMissile::destroy_object()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _bomb_particle, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, _bomb_soundcue, GetActorLocation());

	non_active_bullet();
	_ready_destroy = true;
}


void ADNBossMissile::overlap_actor_handler(const FHitResult& HitResult)
{
	if (nullptr == HitResult.GetActor())												// 바닥에 꽂혔을 때
	{
		if (IsValid(_bomb_soundcue) && nullptr != _bomb_particle)				// 파티클 및 사운드
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _bomb_particle, GetActorLocation());
			UGameplayStatics::PlaySoundAtLocation(this, _bomb_soundcue, GetActorLocation());

		}
	}

	if (_owner != HitResult.GetActor())													// 자신과 충돌 체크
	{
		if (IsValid(_bomb_soundcue) && nullptr != _bomb_particle)				// 파티클 및 사운드
		{
			if (_fire_type == E_FIRE_TYPE::FT_SUB)
			{
				DNDamageOperation::radial_damage_to_all(GetWorld(), 25.f, GetActorLocation(), 200.f, _owner);		// fire 2
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _bomb_particle, GetActorLocation());
				UGameplayStatics::PlaySoundAtLocation(this, _bomb_soundcue, GetActorLocation());
			}
			else if (_fire_type == E_FIRE_TYPE::FT_MAIN)
			{
				DNDamageOperation::radial_damage_to_all(GetWorld(), 100.f, GetActorLocation(), 500.f, _owner);		// fire 1
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _bomb_particle, GetActorLocation() - FVector(0.f, 0.f, -200.f));
				UGameplayStatics::PlaySoundAtLocation(this, _bomb_soundcue, GetActorLocation());
			}
			

		}
	}



	_ready_destroy = true;
}
