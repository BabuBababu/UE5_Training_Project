


#include "UE5_Training_Project/Actor/DNPatternTargetActor.h"



ADNPatternTargetActor::ADNPatternTargetActor()
{
	PrimaryActorTick.bCanEverTick = true;
	_owner = nullptr;
	_is_active = false;
	_limit_time = 0.f;
}

void ADNPatternTargetActor::BeginPlay()
{
	Super::BeginPlay();

}

void ADNPatternTargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADNPatternTargetActor::init()
{
	Super::init();
	_current_hp = _max_hp;
}