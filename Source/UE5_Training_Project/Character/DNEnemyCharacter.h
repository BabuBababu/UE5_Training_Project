// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


// Engine
#include <CoreMinimal.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Generated
#include "DNEnemyCharacter.generated.h"

/**
 *		적군 캐릭터 클래스입니다.
 */


UCLASS()
class UE5_TRAINING_PROJECT_API ADNEnemyCharacter : public ADNCommonCharacter
{
	GENERATED_BODY()
	
public:
	ADNEnemyCharacter();

protected:
	void BeginPlay() override;
	virtual void init_base();


public:
	void init_ai();
	void play_target_circle_destroy_sound();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	E_ENEMY_TYPE _enemy_type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TargetCircle)	//타겟 서클 쿨타임
	float _target_circle_cool_time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TargetCircle)
	float _target_circle_hp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TargetCircle)
	float _target_circle_time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TargetCircle)
	float _target_circle_scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TargetCircle)	//타겟 서클 파괴 소리
	TObjectPtr<USoundBase> _bomb_soundcue;
	
	bool _is_target_circle_success;
	float _target_circle_current_cool_time;
};
