


#include "UE5_Training_Project/Actor/DNBullet.h"

// Engine
#include <Components/BoxComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Engine/Classes/Kismet/GameplayStatics.h>
#include <particles/ParticleSystem.h>
#include <NiagaraComponent.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"
#include "UE5_Training_Project/Character/DNHeliCommonCharacter.h"

// Util
#include "UE5_Training_Project/Util/DNDamageOperation.h"

//
//	여기도 언젠가는 헬기 데이터에 따라 미사일의 대미지 사거리 이동속도 메쉬를 정할수있도록 구현해야합니다.
//  이름도 bullet이 아니라 커먼미사일로 해야할듯
//


ADNBullet::ADNBullet()
{
	PrimaryActorTick.bCanEverTick = true;
	_owner = nullptr;
	_target = nullptr;

	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));

	_actor_static_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	_box_collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	_projectile_movement_component = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	RootComponent = _actor_static_mesh;

	_box_collision->SetupAttachment(_actor_static_mesh);

	_niagara_component = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	_niagara_component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


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

	_limit_time = 0.f;
	_is_active = false;

}

void ADNBullet::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(_box_collision))
	{
		_box_collision->IgnoreActorWhenMoving(_owner, true);
	}

	add_event();
}

void ADNBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ADNBullet::add_event()
{
	if (IsValid(_box_collision))
		_box_collision->OnComponentBeginOverlap.AddDynamic(this, &ADNBullet::overlap_actor_handler);


	//if(IsValid(_projectile_movement_component))
	//	_projectile_movement_component->OnProjectileStop.AddDynamic(this, &ADNBullet::overlap_actor_handler);
}

void ADNBullet::remove_event()
{
	//if (IsValid(_projectile_movement_component))
	//	_projectile_movement_component->OnProjectileStop.RemoveDynamic(this, &ADNBullet::overlap_actor_handler);

	if (IsValid(_box_collision))
		_box_collision->OnComponentBeginOverlap.RemoveDynamic(this, &ADNBullet::overlap_actor_handler);
}


void ADNBullet::init()
{

}

void ADNBullet::active_bullet()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	_projectile_movement_component->Activate();
	_is_active = true;
}


void ADNBullet::non_active_bullet()
{

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	_projectile_movement_component->Deactivate();
	_niagara_component->Deactivate();
	_is_active = false;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Is Active? : %s"), _is_active ? TEXT("true") : TEXT("false")));
}


void ADNBullet::fire(FVector location_in)
{

	if (nullptr == _owner)
		return;

	if(IsValid(_niagara_component) && IsValid(_tail_particle))
		_niagara_component->Activate();

	if(IsValid(_missile_fire_soundcue))
		UGameplayStatics::PlaySoundAtLocation(this, _missile_fire_soundcue, GetActorLocation());


	float random_position_x = FMath::FRandRange(-500.f, 500.f);
	float random_position_y = FMath::FRandRange(-500.f, 500.f);

	FVector direction_vector = (_target->GetActorLocation() + FVector(random_position_x, random_position_y, 0.f )) - location_in;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Direction Vector :%s"), *direction_vector.ToString()));

	_projectile_movement_component->Velocity = direction_vector * _projectile_movement_component->InitialSpeed;
	//DrawDebugLine(GetWorld(), location_in, target_in->GetActorLocation(), FColor::Cyan, true, -1, 0, 10);
	

}



void ADNBullet::overlap_actor_handler(class UPrimitiveComponent* selfComp, class AActor* otherActor, UPrimitiveComponent* otherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (nullptr == otherActor)												// 바닥에 꽂혔을 때
	{
		if (IsValid(_bomb_soundcue) && nullptr != _bomb_particle)				// 파티클 및 사운드
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _bomb_particle, GetActorLocation());
			UGameplayStatics::PlaySoundAtLocation(this, _bomb_soundcue, GetActorLocation());

		}
	}

	if (_owner != otherActor)													// 헬기 자신과 충돌 체크
	{
		if (IsValid(_bomb_soundcue) && nullptr != _bomb_particle)				// 파티클 및 사운드
		{
			DNDamageOperation::radial_damage_to_enemy(GetWorld(), 500.f, GetActorLocation(), 1500.f, _owner);
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _bomb_particle, GetActorLocation() - FVector(0.f, 0.f, 200.f));
			UGameplayStatics::PlaySoundAtLocation(this, _bomb_soundcue, GetActorLocation());
			//if (_owner->get_character_type() != E_CHARACTER_TYPE::CT_ENEMY)				// 아군이 쏜 것이라면
			//{
			//	
			//}
		}
	}
	
	
	non_active_bullet();
}

