


#include "UE5_Training_Project/Actor/DNCommonShield.h"

// Engine
#include <Engine/Classes/Kismet/GameplayStatics.h>


ADNCommonShield::ADNCommonShield()
{
	_actor_type = E_ACTOR_TYPE::AT_SHIELD;
}

void ADNCommonShield::BeginPlay()
{
	Super::BeginPlay();
	_current_hp = _max_hp;

}

void ADNCommonShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADNCommonShield::add_event()
{

}

void ADNCommonShield::remove_event()
{

}

void ADNCommonShield::destroy_object()
{
	// 사운드
	if (IsValid(_destroy_soundcue))
		UGameplayStatics::PlaySoundAtLocation(this, _destroy_soundcue, GetActorLocation());


	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void ADNCommonShield::reset()
{
	set_current_hp(_max_hp);

	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

void ADNCommonShield::play_damaged_sound()
{

	// 사운드
	if (IsValid(_damaged_soundcue))
		UGameplayStatics::PlaySoundAtLocation(this, _damaged_soundcue, GetActorLocation());
}