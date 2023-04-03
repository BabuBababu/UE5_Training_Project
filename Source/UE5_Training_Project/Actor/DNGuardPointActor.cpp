


#include "UE5_Training_Project/Actor/DNGuardPointActor.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"




ADNGuardPointActor::ADNGuardPointActor()
{
	_index = -1;
}


void ADNGuardPointActor::BeginPlay()
{
	Super::BeginPlay();
	add_event();

	OBJECT_MANAGER->_guard_location_actor_array.Emplace(_index, this);		//시작시 오브젝트 매니저에 넣어줍니다.
}



void ADNGuardPointActor::add_event()
{

}


void ADNGuardPointActor::remove_event()
{

}
