


#include "UE5_Training_Project/Actor/Item/DNCommonGrenade.h"

// Engine
#include <particles/ParticleSystem.h>
#include <NiagaraComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>

// Util
#include "UE5_Training_Project/Util/DNDamageOperation.h"



ADNCommonGrenade::ADNCommonGrenade()
{

	init();
	
}


void ADNCommonGrenade::BeginPlay()
{
	Super::BeginPlay();

}



void ADNCommonGrenade::add_event()
{
	Super::add_event();

}



void ADNCommonGrenade::remove_event()
{
	Super::remove_event();

}



void ADNCommonGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (true == _is_fire && false == _ready_destroy)			//수류탄이 발사 되었는지 체크, 한번 폭발이 된건지 체크
	{
		_current_time += DeltaTime;

		if (_life_time <= _current_time)
			bomb_grenade();
	}

	if (_ready_destroy)
	{
		_limit_time += DeltaTime;
		if (_limit_time > 2.f)
			Destroy();
	}
}

void ADNCommonGrenade::init()
{
	

	_projectile_movement_component = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	

	// 기존에 붙어있던것을 다시 뗍니다.
	_actor_static_mesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	_box_collision->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	RootComponent = _actor_static_mesh;
	_box_collision->SetupAttachment(_actor_static_mesh);

	

	if (IsValid(_projectile_movement_component))
	{
		_projectile_movement_component->InitialSpeed = 10.f;
		_projectile_movement_component->MaxSpeed = 2000.0f;					//수류탄 속도
		_projectile_movement_component->bShouldBounce = true;
		_projectile_movement_component->Bounciness = 0.5f;
		_projectile_movement_component->Friction = 0.2f;
		_projectile_movement_component->ProjectileGravityScale = 1.0f;
		_projectile_movement_component->bRotationFollowsVelocity = true;

		_projectile_movement_component->SetUpdatedComponent(RootComponent);
	}


	_owner = nullptr;
	_is_fire = false;
	_ready_destroy = false;
	_current_time = 0.f;
	_limit_time = 0.f;
	_actor_type = E_ACTOR_TYPE::AT_ITEM;
}


void ADNCommonGrenade::throw_grenade(FVector direction_in)
{
	_is_fire = true;
	if (IsValid(_projectile_movement_component))
	{
		_projectile_movement_component->Velocity = direction_in;
	}
		
}

void ADNCommonGrenade::bomb_grenade()
{
	// 소리
	if(IsValid(_bomb_soundcue))
		UGameplayStatics::PlaySoundAtLocation(this, _bomb_soundcue, GetActorLocation());

	// 파티클
	if(IsValid(_bomb_particle))
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _bomb_particle, GetActorLocation() - FVector(0.f, 0.f, 0.f));

	// 대미지
	DNDamageOperation::radial_damage_to_enemy(GetWorld(), 200.f, GetActorLocation(), 500.f, _owner);

	_ready_destroy = true;
}


