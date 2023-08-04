


#include "UE5_Training_Project/Actor/DNPatternTargetActor.h"

// Engine
#include <Components/CapsuleComponent.h>
#include <particles/ParticleSystem.h>
#include <NiagaraComponent.h>

// Character
#include "UE5_Training_Project/Character/DNEnemyCharacter.h"

ADNPatternTargetActor::ADNPatternTargetActor()
{
	_enemy_type = E_ENEMY_TYPE::ET_TARGET_CIRCLE;

	_owner = nullptr;
	_is_active = false;
	_limit_max_time = 0.f;
	_limit_current_time = 0.f;
	_max_hp = 0.f;
	_current_hp = 0.f;

	_target_deco_particle_component = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	_target_deco_particle_component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void ADNPatternTargetActor::BeginPlay()
{
	Super::BeginPlay();

	init();
	play_particle();
}

void ADNPatternTargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_is_active)
	{
		_limit_current_time -= DeltaTime;

		if (_limit_current_time <= 0)
		{
			_is_active = false;
			if (IsValid(_owner))
			{
				_owner->_is_target_circle_success = true;
			}

			_target_deco_particle_component->Deactivate();
			Destroy();
		}
	}
}

void ADNPatternTargetActor::init()
{
	if (nullptr == _owner)
		return;


	// 시간
	_limit_max_time = _owner->_target_circle_time;
	_limit_current_time = _limit_max_time;

	// HP
	_max_hp = _owner->_target_circle_hp;
	_current_hp = _max_hp;

	// 타겟 서클 크기 조정
	GetCapsuleComponent()->SetCapsuleRadius(GetCapsuleComponent()->GetScaledCapsuleRadius() * _owner->_target_circle_scale);

	// 타겟 서클 부착
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
	this->AttachToComponent(_owner->_character_skeletal_mesh, AttachmentRules, "TargetCircle1");

	// 작동 시작
	_is_active = true;
}

void ADNPatternTargetActor::play_particle()
{
	if (false == IsValid(_target_deco_particle_component))
		return;

	if (nullptr == _owner)
		return;

	// 시전자 크기에 맞게 사이즈 수정
	_target_deco_particle_component->SetRelativeScale3D(FVector(1.0 * _owner->_target_circle_scale));
	// 활성화
	_target_deco_particle_component->Activate();
}