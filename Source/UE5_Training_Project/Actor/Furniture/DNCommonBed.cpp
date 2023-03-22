


#include "UE5_Training_Project/Actor/Furniture/DNCommonBed.h"


// Engine
#include <Components/BoxComponent.h>
#include <BehaviorTree/BlackboardComponent.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"



ADNCommonBed::ADNCommonBed()
{
	_actor_type = E_ACTOR_TYPE::AT_FURNITURE;
	_furniture_type = E_FURNITURE_TYPE::FT_BED;
}

void ADNCommonBed::BeginPlay()
{
	Super::BeginPlay();

	add_event();

	OBJECT_MANAGER->_lobby_bed_array.Add(this);
}


void ADNCommonBed::add_event()
{
	
}


void ADNCommonBed::remove_event()
{

}

void ADNCommonBed::Tick(float DeltaTime)
{

}
