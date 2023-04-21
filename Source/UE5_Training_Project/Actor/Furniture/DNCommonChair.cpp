


#include "UE5_Training_Project/Actor/Furniture/DNCommonChair.h"

// Engine
#include <Components/BoxComponent.h>
#include <BehaviorTree/BlackboardComponent.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"



ADNCommonChair::ADNCommonChair()
{
	_furniture_type = E_FURNITURE_TYPE::FT_CHAIR;
}

void ADNCommonChair::BeginPlay()
{
	Super::BeginPlay();

	add_event();

}


void ADNCommonChair::add_event()
{

}


void ADNCommonChair::remove_event()
{

}

void ADNCommonChair::Tick(float DeltaTime)
{

}
