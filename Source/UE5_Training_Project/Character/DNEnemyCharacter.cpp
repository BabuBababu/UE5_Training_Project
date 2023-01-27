// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5_Training_Project/Character/DNEnemyCharacter.h"

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"


ADNEnemyCharacter::ADNEnemyCharacter()
{
	init_base();
	init_ai();
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