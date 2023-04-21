


#include "UE5_Training_Project/Actor/Furniture/DNPostChair.h"


// Engine
#include <Components/BoxComponent.h>
#include <BehaviorTree/BlackboardComponent.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"



ADNPostChair::ADNPostChair()
{

}

void ADNPostChair::BeginPlay()
{
	Super::BeginPlay();

	add_event();


	if (_actor_id == -1)		//설정이 안되어있다면 리턴합니다.
		return;

	OBJECT_MANAGER->_post_chair = this;
}


void ADNPostChair::add_event()
{

}


void ADNPostChair::remove_event()
{

}

void ADNPostChair::Tick(float DeltaTime)
{

}
