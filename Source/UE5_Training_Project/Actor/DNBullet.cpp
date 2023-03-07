


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
//	���⵵ �������� ��� �����Ϳ� ���� �̻����� ����� ��Ÿ� �̵��ӵ� �޽ø� ���Ҽ��ֵ��� �����ؾ��մϴ�.
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
							// ���� ��Ʈ������Ʈ�� �صθ� �Ʒ��� �̻��� ��ġ �ʱ�ȭ�� �ȵǼ� �׳� �̷�����. 
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


void ADNBullet::fire(ADNCommonCharacter* target_in)
{
	//active_bullet();

	if (nullptr == _owner)
		return;

	FVector socket_location = _owner->_heli_skeletal_mesh->GetSocketLocation(FName("Rocket_Muzzle_L"));
	


	//_projectile_movement_component->StopMovementImmediately();
	SetActorLocation(socket_location);
	SetActorRotation(_owner->GetActorRotation());

	// ����
	if(IsValid(_owner->_missile_fire_soundcue))
		UGameplayStatics::PlaySoundAtLocation(this, _owner->_missile_fire_soundcue, GetActorLocation());

	FVector direction_vector = target_in->GetActorLocation() - _owner->GetActorLocation();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Direction Vector :%s"), *direction_vector.ToString()));

	_projectile_movement_component->Velocity = direction_vector * _projectile_movement_component->InitialSpeed;
	_ready_destroy = true;

}



void ADNBullet::overlap_actor_handler(const FHitResult& HitResult)
{
	if (nullptr == HitResult.GetActor())												// �ٴڿ� ������ ��
	{
		if (IsValid(_owner->_missile_fire_soundcue) && nullptr != _owner->_bomb_particle)				// ��ƼŬ �� ����
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _owner->_bomb_particle, GetActorLocation());
			UGameplayStatics::PlaySoundAtLocation(this, _owner->_bomb_soundcue, GetActorLocation());

		}
	}

	if (_owner != HitResult.GetActor())													// ��� �ڽŰ� �浹 üũ
	{
		if (IsValid(_owner->_missile_fire_soundcue) && nullptr != _owner->_bomb_particle)				// ��ƼŬ �� ����
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _owner->_bomb_particle, GetActorLocation() - FVector(0.f,0.f,200.f));
			UGameplayStatics::PlaySoundAtLocation(this, _owner->_bomb_soundcue, GetActorLocation());
			
			DNDamageOperation::radial_damage(GetWorld(), 500.f, GetActorLocation(), 2000.f, _owner);

		}
	}
	
	

}
