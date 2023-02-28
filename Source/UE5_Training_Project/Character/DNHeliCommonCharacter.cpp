


#include "UE5_Training_Project/Character/DNHeliCommonCharacter.h"

// Engine
#include <GameFramework/FloatingPawnMovement.h>

ADNHeliCommonCharacter::ADNHeliCommonCharacter()
{
	// Mesh
	_heli_skeletal_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HeliSkeletalMesh"));
	_heli_skeletal_mesh->SetupAttachment(RootComponent);

	_floting_movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
	_floting_movement->SetUpdatedComponent(RootComponent);


	init_base();
}

void ADNHeliCommonCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ADNHeliCommonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	set_flying_move(DeltaTime);

}

void ADNHeliCommonCharacter::add_event()
{

}

void ADNHeliCommonCharacter::remove_event()
{

}


void ADNHeliCommonCharacter::init_base()
{
	_character_type = E_CHARACTER_TYPE::CT_HELI;

	_rotor_mast = 0.f;
	_rotor_back = 0.f;
	_rotor_minigun = 0.f;
}


void ADNHeliCommonCharacter::set_flying_move(float DeltaTime)
{
	// 공중에 떠있는 것
	FVector NewLocation = GetActorLocation();

	float DeltaHeight = (FMath::Sin(_running_time + DeltaTime) - FMath::Sin(_running_time));

	NewLocation.X += DeltaHeight * XValue;
	NewLocation.Y += DeltaHeight * YValue;
	NewLocation.Z += DeltaHeight * ZValue;

	_running_time += DeltaTime;

	SetActorLocation(NewLocation);

	//날개 움직임

	if (_rotor_mast < -360.f)
	{
		_rotor_mast = 0.f;
	}
	if (_rotor_back < -360.f)
	{
		_rotor_back = 0.f;
	}

	_rotor_mast -= 20.f;
	_rotor_back -= 20.f;

}