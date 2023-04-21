


#include "UE5_Training_Project/Actor/Furniture/DNCommonFurniture.h"



// Engine
#include <Components/BoxComponent.h>
#include <Components/ArrowComponent.h>
#include <BehaviorTree/BlackboardComponent.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"



ADNCommonFurniture::ADNCommonFurniture()
{
	_interaction_point = CreateDefaultSubobject<UArrowComponent>(TEXT("InteractionArrow"));
	_interaction_point->SetupAttachment(_actor_static_mesh);

	_actor_type = E_ACTOR_TYPE::AT_FURNITURE;
	_is_used = false;
}

void ADNCommonFurniture::BeginPlay()
{
	Super::BeginPlay();

	add_event();


	if (_actor_id == -1)		//설정이 안되어있다면 리턴합니다.
		return;

	OBJECT_MANAGER->_lobby_furniture_array.Add(_actor_id, this);
}


void ADNCommonFurniture::add_event()
{

}


void ADNCommonFurniture::remove_event()
{

}

void ADNCommonFurniture::Tick(float DeltaTime)
{

}
