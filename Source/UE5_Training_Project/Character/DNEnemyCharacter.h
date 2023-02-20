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

	void BeginPlay() override;



protected:
	void init_ai();
	virtual void init_base();


};
