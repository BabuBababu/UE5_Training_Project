


#include "UE5_Training_Project/Actor/DNTargetPointActor.h"

// Engine
#include <Components/BoxComponent.h>
#include <BehaviorTree/BlackboardComponent.h>

// Character
#include "UE5_Training_Project/Character/DNEnemyCharacter.h"

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"


ADNTargetPointActor::ADNTargetPointActor()
{
	_is_destroyed = false;
	_index = -1;
}


void ADNTargetPointActor::BeginPlay()
{
	Super::BeginPlay();
	add_event();

	OBJECT_MANAGER->_target_location_actor_array.Emplace(_index,this);		//시작시 오브젝트 매니저에 넣어줍니다.
}



void ADNTargetPointActor::add_event()
{
	if (nullptr == _box_collision)
		return;

	_box_collision->OnComponentBeginOverlap.AddDynamic(this, &ADNTargetPointActor::overlap_point_handler);

}


void ADNTargetPointActor::remove_event()
{

}





// 적으로부터 이 액터가 오버랩이 되면 해당 위치는 점령 당한 것으로 간주합니다.
void ADNTargetPointActor::overlap_point_handler(class UPrimitiveComponent* selfComp, class AActor* otherActor, UPrimitiveComponent* otherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADNEnemyCharacter* enemy = dynamic_cast<ADNEnemyCharacter*>(otherActor);

	if (nullptr == enemy)
		return;

	_is_destroyed = true;


}
