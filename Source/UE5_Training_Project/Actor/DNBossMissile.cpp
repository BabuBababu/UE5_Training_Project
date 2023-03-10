


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

	add_event();
}

void ADNBossMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}


void ADNBossMissile::add_event()
{
	
}

void ADNBossMissile::remove_event()
{
	
}


void ADNBossMissile::init()
{

}