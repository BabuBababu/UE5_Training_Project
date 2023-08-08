


#include "UE5_Training_Project/Actor/DNPatternTargetActor.h"

// Engine
#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
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

	_target_deco_particle_component = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ing_niagara"));
	_target_deco_particle_component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	_target_destroy_particle_component = CreateDefaultSubobject<UNiagaraComponent>(TEXT("destroyed_niagara"));
	_target_destroy_particle_component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	_target_destroy_fail_particle_component = CreateDefaultSubobject<UNiagaraComponent>(TEXT("destroy_failed_niagara"));
	_target_destroy_fail_particle_component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	GetCharacterMovement()->Deactivate();
}

void ADNPatternTargetActor::BeginPlay()
{
	Super::BeginPlay();

}

void ADNPatternTargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_is_active)
	{
		_limit_current_time -= DeltaTime;

		// 시간 초과
		if (_limit_current_time <= 0)
		{
			_is_active = false;
			if (IsValid(_owner))
			{
				// 패턴 공격 실행
				_owner->_is_target_circle_success = true;
			}

			if(nullptr != _target_destroy_fail_particle_component)
				_target_destroy_fail_particle_component->Activate();

			if(nullptr != _target_deco_particle_component)
				_target_deco_particle_component->Deactivate();


			// 콜리전 끄기
			SetActorEnableCollision(false);

			// 실패 파티클 재생이 종료되면
			if(false == _target_destroy_fail_particle_component->IsActive())
				Destroy();
		}
		else
		{
			// 파괴 당함
			if (_current_hp <= 0)
			{
				_is_active = false;
				if (IsValid(_owner))
				{
					_owner->_is_target_circle_success = false;
				}

				if (nullptr != _target_destroy_particle_component)
					_target_destroy_particle_component->Activate();

				if (nullptr != _target_deco_particle_component)
					_target_deco_particle_component->Deactivate();

				// 콜리전 끄기
				SetActorEnableCollision(false);

				// 실패 파티클 재생이 종료되면
				if (false == _target_destroy_particle_component->IsActive())
					Destroy();
			}
		}
	}
}

void ADNPatternTargetActor::add_event()
{
	if (nullptr != _target_destroy_fail_particle_component)
	{
		_target_destroy_fail_particle_component->OnSystemFinished.AddDynamic(this, &ADNPatternTargetActor::start_fail_niagara_handler);
	}
	if (nullptr != _target_destroy_particle_component)
	{
		_target_destroy_particle_component->OnSystemFinished.AddDynamic(this, &ADNPatternTargetActor::start_destroyed_niagara_handler);
	}
}

void ADNPatternTargetActor::remove_event()
{
	if (nullptr != _target_destroy_fail_particle_component)
	{
		_target_destroy_fail_particle_component->OnSystemFinished.RemoveDynamic(this, &ADNPatternTargetActor::start_fail_niagara_handler);
	}
	if (nullptr != _target_destroy_particle_component)
	{
		_target_destroy_particle_component->OnSystemFinished.RemoveDynamic(this, &ADNPatternTargetActor::start_destroyed_niagara_handler);
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

	play_deco_particle();

	// 이벤트 추가
	//add_event();
}

void ADNPatternTargetActor::play_deco_particle()
{
	if (false == IsValid(_target_deco_particle_component))
		return;

	if (nullptr == _owner)
		return;

	// 시전자 크기에 맞게 사이즈 수정
	//_target_deco_particle_component->SetRelativeScale3D(FVector(1.0 * _owner->_target_circle_scale));

	// 활성화
	_target_deco_particle_component->Activate();
}

void ADNPatternTargetActor::play_destroy_particle()
{
	if (false == IsValid(_target_destroy_particle_component))
		return;

	if (nullptr == _owner)
		return;

	// 시전자 크기에 맞게 사이즈 수정
	//_target_deco_particle_component->SetRelativeScale3D(FVector(1.0 * _owner->_target_circle_scale));

	// 활성화
	_target_destroy_particle_component->Activate();
}

void ADNPatternTargetActor::play_fail_particle()
{
	if (false == IsValid(_target_destroy_fail_particle_component))
		return;

	if (nullptr == _owner)
		return;

	// 시전자 크기에 맞게 사이즈 수정
	//_target_deco_particle_component->SetRelativeScale3D(FVector(1.0 * _owner->_target_circle_scale));

	// 활성화
	_target_destroy_fail_particle_component->Activate();
}

void ADNPatternTargetActor::start_fail_niagara_handler(UNiagaraComponent* FinishedComponent)
{
	FinishedComponent->Deactivate();
}

void ADNPatternTargetActor::start_destroyed_niagara_handler(UNiagaraComponent* FinishedComponent)
{
	FinishedComponent->Deactivate();
}