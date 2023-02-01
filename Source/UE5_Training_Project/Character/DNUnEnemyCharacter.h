// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine
#include <CoreMinimal.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// generated
#include "DNUnEnemyCharacter.generated.h"

/**
 *	 플레이어 및 그리폰 인형의 캐릭터 클래스입니다.
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNUnEnemyCharacter : public ADNCommonCharacter
{
	GENERATED_BODY()

public:
	ADNUnEnemyCharacter();
	void fire() override;

	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	void add_event() override;
	void remove_event() override;

private:
	void init_ai();
	void init_base();

public:
	void set_attack_finish();

public:
	UFUNCTION()
	void change_armed_state_handler(bool armed_in);
	UFUNCTION()
	void change_crouch_state_handler(bool crouch_in);

};
