

#pragma once

// Engine
#include <CoreMinimal.h>
#include <NiagaraSystem.h>
#include <NiagaraFunctionLibrary.h>

// Actor
#include "UE5_Training_Project/Actor/DNCommonActor.h"

// Generated
#include "DNCommonGrenade.generated.h"

/**
 * 
 */

class UProjectileMovementComponent;
class ADNCommonCharacter;

UCLASS()
class UE5_TRAINING_PROJECT_API ADNCommonGrenade : public ADNCommonActor
{
	GENERATED_BODY()

public:
	ADNCommonGrenade();

protected:
	virtual void BeginPlay() override;

	virtual void add_event() override;
	virtual void remove_event() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	void init() override;
	virtual void throw_grenade(FVector direction_in);
	virtual void bomb_grenade();

public:

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	TObjectPtr<UProjectileMovementComponent> _projectile_movement_component;

	UPROPERTY(EditAnywhere, Category = "Particle Effects")					//폭발 파티클
	UNiagaraSystem* _bomb_particle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)								//폭발 소리
	TObjectPtr<USoundBase> _bomb_soundcue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)								//바닥에 튕기는 소리
	TObjectPtr<USoundBase> _bound_soundcue;

	UPROPERTY(EditAnywhere, Category = "Base")								//던지는 힘
	float throw_force = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Base")								//대기 시간
	float _life_time = 3.f;
public:
	ADNCommonCharacter* _owner;
	bool	_is_fire;
	bool	_ready_destroy;
	float	_limit_time;
	float   _current_time;

};
