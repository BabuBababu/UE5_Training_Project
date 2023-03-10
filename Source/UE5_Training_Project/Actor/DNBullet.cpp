


#include "UE5_Training_Project/Actor/DNBullet.h"

// Engine
#include <Components/BoxComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Engine/Classes/Kismet/GameplayStatics.h>
#include <particles/ParticleSystem.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"
#include "UE5_Training_Project/Character/DNHeliCommonCharacter.h"

// Util
#include "UE5_Training_Project/Util/DNDamageOperation.h"

//
//	여기도 언젠가는 헬기 데이터에 따라 미사일의 대미지 사거리 이동속도 메시를 정할수있도록 구현해야합니다.
//


ADNBullet::ADNBullet()
{
	PrimaryActorTick.bCanEverTick = true;
	_owner = nullptr;

	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));

	_actor_static_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	_box_collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	_projectile_movement_component = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	RootComponent = _actor_static_mesh;

	_box_collision->SetupAttachment(_actor_static_mesh);

	if (IsValid(_projectile_movement_component))
	{
		_projectile_movement_component->InitialSpeed = 10.f;
		_projectile_movement_component->MaxSpeed = 2000.0f;					//bulletSpeed
		_projectile_movement_component->bShouldBounce = false;
		_projectile_movement_component->bRotationFollowsVelocity = true;
		_projectile_movement_component->bAutoActivate = true;
		_projectile_movement_component->ProjectileGravityScale = 0.0f;
							// 순수 루트컴포넌트로 해두면 아래에 미사일 위치 초기화가 안되서 그냥 이렇게함. 
		_projectile_movement_component->SetUpdatedComponent(RootComponent);	
	}

	_ready_destroy = false;
	_limit_time = 0.f;

}

void ADNBullet::BeginPlay()
{
	Super::BeginPlay();

	add_event();
}

void ADNBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_ready_destroy)
	{
		_limit_time += DeltaTime;
		if (_limit_time > 5.f)
			Destroy();
	}

}


void ADNBullet::add_event()
{
	if(IsValid(_projectile_movement_component))
		_projectile_movement_component->OnProjectileStop.AddDynamic(this, &ADNBullet::overlap_actor_handler);
}

void ADNBullet::remove_event()
{
	if (IsValid(_projectile_movement_component))
		_projectile_movement_component->OnProjectileStop.RemoveDynamic(this, &ADNBullet::overlap_actor_handler);
}


void ADNBullet::init()
{
	
}

void ADNBullet::active_bullet()
{

	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	_projectile_movement_component->Activate();
}


void ADNBullet::non_active_bullet()
{

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	_projectile_movement_component->Deactivate();
}


void ADNBullet::fire(ADNCommonCharacter* target_in,FVector location_in)
{
	//active_bullet();

	if (nullptr == _owner)
		return;

	//FVector socket_location = _owner->_character_skeletal_mesh->GetSocketLocation(FName("Rocket_Muzzle_L"));
	//


	////_projectile_movement_component->StopMovementImmediately();
	//SetActorLocation(socket_location);
	//SetActorRotation(_owner->GetActorRotation());

	// 사운드
	if(IsValid(_missile_fire_soundcue))
		UGameplayStatics::PlaySoundAtLocation(this, _missile_fire_soundcue, GetActorLocation());


	float random_position_x = FMath::FRandRange(-500.f, 500.f);
	float random_position_y = FMath::FRandRange(-500.f, 500.f);

	FVector direction_vector = (target_in->GetActorLocation() + FVector(random_position_x, random_position_y, 0.f )) - location_in;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Direction Vector :%s"), *direction_vector.ToString()));

	_projectile_movement_component->Velocity = direction_vector * _projectile_movement_component->InitialSpeed;
	//DrawDebugLine(GetWorld(), location_in, target_in->GetActorLocation(), FColor::Cyan, true, -1, 0, 10);
	


	//if (IsValid(_tail_particle))			// 꼬리 파티클
	//	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _tail_particle, RootComponent->GetRelativeLocation());

}



void ADNBullet::overlap_actor_handler(const FHitResult& HitResult)
{
	if (nullptr == HitResult.GetActor())												// 바닥에 꽂혔을 때
	{
		if (IsValid(_bomb_soundcue) && nullptr != _bomb_particle)				// 파티클 및 사운드
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _bomb_particle, GetActorLocation());
			UGameplayStatics::PlaySoundAtLocation(this, _bomb_soundcue, GetActorLocation());

		}
	}

	if (_owner != HitResult.GetActor())													// 헬기 자신과 충돌 체크
	{
		if (IsValid(_bomb_soundcue) && nullptr != _bomb_particle)				// 파티클 및 사운드
		{
			
			if (_owner->get_character_type() != E_CHARACTER_TYPE::CT_ENEMY)				// 아군이 쏜 것이라면
			{
				DNDamageOperation::radial_damage_to_enemy(GetWorld(), 500.f, GetActorLocation(), 2000.f, _owner);
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _bomb_particle, GetActorLocation() - FVector(0.f, 0.f, 200.f));
				UGameplayStatics::PlaySoundAtLocation(this, _bomb_soundcue, GetActorLocation());
			}
			else
			{
				DNDamageOperation::radial_damage_to_all(GetWorld(), 25.f, GetActorLocation(), 200.f, _owner);		//적군이 쏜 것이라면
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _bomb_particle, GetActorLocation());
				UGameplayStatics::PlaySoundAtLocation(this, _bomb_soundcue, GetActorLocation());
			}

		}
	}
	
	

	_ready_destroy = true;
}

