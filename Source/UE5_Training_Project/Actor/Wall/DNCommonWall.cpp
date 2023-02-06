


#include "UE5_Training_Project/Actor/Wall/DNCommonWall.h"

// Engine
#include <Components/BoxComponent.h>


void ADNCommonWall::BeginPlay()
{
	Super::BeginPlay();

	add_event();
}


void ADNCommonWall::add_event()
{
	if (nullptr == _box_collision)
		return;

	_box_collision->OnComponentBeginOverlap.AddDynamic(this, &ADNCommonWall::overlap_wall_handler);

}


void ADNCommonWall::remove_event()
{

}

void ADNCommonWall::Tick(float DeltaTime)
{

}


void ADNCommonWall::overlap_wall_handler(class UPrimitiveComponent* selfComp, class AActor* otherActor, UPrimitiveComponent* otherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnOverlapWall.Broadcast();

	UE_LOG(LogTemp, Warning, TEXT("Wall Overlap actor is %s"), *otherActor->GetName());
}