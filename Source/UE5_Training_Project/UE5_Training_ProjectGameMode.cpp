// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5_Training_ProjectGameMode.h"
#include "UE5_Training_ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE5_Training_ProjectGameMode::AUE5_Training_ProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
