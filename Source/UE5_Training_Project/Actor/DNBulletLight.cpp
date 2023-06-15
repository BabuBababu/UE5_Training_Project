


#include "UE5_Training_Project/Actor/DNBulletLight.h"

// Engine
#include <Components/BoxComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Engine/Classes/Kismet/GameplayStatics.h>
#include <particles/ParticleSystem.h>
#include <NiagaraComponent.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"


ADNBulletLight::ADNBulletLight()
{
	_life_time = 0.6f;
	_life_current_time = 0.f;
}

void ADNBulletLight::BeginPlay()
{
	Super::BeginPlay();
	active_bullet();
}


void ADNBulletLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	_life_current_time = _life_current_time + DeltaTime;

	if (_life_current_time > _life_time)
	{
		non_active_bullet();
		//Destroy();
	}

}


void ADNBulletLight::fire(FVector location_in)
{

	FVector direction_vector = _hit_location - location_in;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Direction Vector :%s"), *direction_vector.ToString()));

	_projectile_movement_component->Velocity = direction_vector * _projectile_movement_component->InitialSpeed;
	//DrawDebugLine(GetWorld(), location_in, target_in->GetActorLocation(), FColor::Cyan, true, -1, 0, 10);

}


void ADNBulletLight::active_bullet()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	_projectile_movement_component->Activate();
	_is_active = true;
}


void ADNBulletLight::non_active_bullet()
{

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	_projectile_movement_component->Deactivate();
	_is_active = false;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Is Active? : %s"), _is_active ? TEXT("true") : TEXT("false")));
}