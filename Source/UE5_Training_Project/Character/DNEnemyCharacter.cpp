// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5_Training_Project/Character/DNEnemyCharacter.h"

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"


ADNEnemyCharacter::ADNEnemyCharacter()
{
	init_base();
	init_ai();
}

void ADNEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	_is_attacking = false;
	_is_armed_weapon = true;
	_character_state = E_CHARACTER_STATE::CS_ARM;			//우선은 테스트를 위해 무기를 들었다고 설정
}


void ADNEnemyCharacter::init_ai()
{
	AIControllerClass = ADNAIController::StaticClass();		//엔진 초기화 단계에서 생성해줘야하므로 StaticClass
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

void ADNEnemyCharacter::init_base()
{
	_character_type = E_CHARACTER_TYPE::CT_ENEMY;
}