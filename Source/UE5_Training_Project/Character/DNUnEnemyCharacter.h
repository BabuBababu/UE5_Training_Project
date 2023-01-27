// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine
#include "CoreMinimal.h"

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


private:
	void init_ai();
	void init_base();
};
