﻿


#include "UE5_Training_Project/Actor/Wall/DNCommonWall.h"

// Engine
#include <Components/BoxComponent.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"


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
	_box_collision->OnComponentEndOverlap.AddDynamic(this, &ADNCommonWall::unoverlap_wall_handler);

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
	ADNCommonCharacter* character = dynamic_cast<ADNCommonCharacter*>(otherActor);

	if (nullptr == character)
		return;

	character->_is_near_wall = true;

	UE_LOG(LogTemp, Warning, TEXT("Wall Overlap actor is %s"), *otherActor->GetName());
}


void ADNCommonWall::unoverlap_wall_handler(UPrimitiveComponent* OverlappedComp, AActor* otherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	ADNCommonCharacter* character = dynamic_cast<ADNCommonCharacter*>(otherActor);

	if (nullptr == character)
		return;

	character->_is_near_wall = false;

	UE_LOG(LogTemp, Warning, TEXT("Wall Un Overlap actor is %s"), *otherActor->GetName());
}