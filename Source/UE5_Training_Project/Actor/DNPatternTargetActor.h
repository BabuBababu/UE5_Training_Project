﻿

#pragma once

// Engine
#include <CoreMinimal.h>
#include <NiagaraSystem.h>
#include <NiagaraFunctionLibrary.h>

// Character
#include "UE5_Training_Project/Character/DNEnemyCharacter.h"

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNPatternTargetActor.generated.h"

/**
 *  처음엔 CommonActor로 받았다가 구조상 EnemyCharacter로 변경함
 */

class ADNEnemyCharacter;

UCLASS()
class UE5_TRAINING_PROJECT_API ADNPatternTargetActor : public ADNEnemyCharacter
{
	GENERATED_BODY()
public:
	ADNPatternTargetActor();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void init();	//한번만 호출
	void play_particle();
	
public:
	float get_max_hp() const { return _max_hp; };
	void set_current_hp(float hp_in) { _current_hp = hp_in; };
	float get_current_hp() const { return _current_hp; };
	float get_limit_max_time() const { return _limit_max_time; };
	float get_limit_current_time() const { return _limit_current_time; };

	void set_owner(ADNEnemyCharacter* owner_in) { _owner = owner_in; };
	ADNEnemyCharacter* get_owner() const { return _owner; };
public:
	UPROPERTY(EditAnywhere, Category = "Particle Effects")					//타겟 반짝임 파티클 나이아가라 컴포넌트
	TObjectPtr<UNiagaraComponent> _target_deco_particle_component;


private:
	ADNEnemyCharacter* _owner;
	bool _is_active;
	float _limit_max_time;
	float _limit_current_time;
	float _max_hp;
	float _current_hp;
};
