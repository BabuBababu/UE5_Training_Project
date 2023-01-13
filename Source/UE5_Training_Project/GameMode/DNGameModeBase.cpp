// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5_Training_Project/GameMode/DNGameModeBase.h"

// Character
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"

// Controller
#include "UE5_Training_Project/Controller/DNPlayerController.h"




ADNGameModeBase::ADNGameModeBase()
{
	//플레이어 캐릭터
	static ConstructorHelpers::FClassFinder<ADNUnEnemyCharacter> PlayerCharacterBPClass(TEXT("/Game/Blueprint/Character/TEST.TEST_C"));
	if (PlayerCharacterBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerCharacterBPClass.Class;
	}

	//플레이어 컨트롤러
	static ConstructorHelpers::FClassFinder<ADNPlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprint/Controller/MyDNPlayerController.MyDNPlayerController_C"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}



void ADNGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ADNGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}