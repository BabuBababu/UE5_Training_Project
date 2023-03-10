


#include "UE5_Training_Project/Actor/DNBossMissile.h"

// Engine
#include <Components/SplineComponent.h>


ADNBossMissile::ADNBossMissile()
{

	_spline_component = CreateDefaultSubobject<USplineComponent>(TEXT("SplineForMove"));

}

void ADNBossMissile::BeginPlay()
{
	Super::BeginPlay();

}

void ADNBossMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}


void ADNBossMissile::add_event()
{
	Super::add_event();
}

void ADNBossMissile::remove_event()
{

	Super::remove_event();
}


void ADNBossMissile::init()
{

}