


#include "UE5_Training_Project/Controller/DNLobbyController.h"




ADNLobbyController::ADNLobbyController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}





void ADNLobbyController::BeginPlay()
{
	Super::BeginPlay();

}

void ADNLobbyController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ADNLobbyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADNLobbyController::SetupInputComponent()
{
	Super::SetupInputComponent();

}