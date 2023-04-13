


#include "UE5_Training_Project/Core/DNGameState.h"




void ADNGameState::BeginPlay()
{
	Super::BeginPlay();

	_is_completed = false;
	_is_failed = false;

}