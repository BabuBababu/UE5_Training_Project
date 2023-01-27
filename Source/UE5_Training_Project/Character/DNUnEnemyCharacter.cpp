// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"


ADNUnEnemyCharacter::ADNUnEnemyCharacter()
{
	init_base();
	init_ai();
}


void ADNUnEnemyCharacter::init_ai()
{
	AIControllerClass = ADNAIController::StaticClass();		//엔진 초기화 단계에서 생성해줘야하므로 StaticClass
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}


void ADNUnEnemyCharacter::init_base()
{
	_character_type = E_CHARACTER_TYPE::CT_ENEMY;
}