


#include "UE5_Training_Project/Character/DNPlayerCharacter.h"

// Controller
#include "UE5_Training_Project/Controller/DNPlayerController.h"

// Component
#include "UE5_Training_Project/Character/Component/DNPlayerLineTrace.h"

void ADNPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}


void ADNPlayerCharacter::start_fire()
{
	_is_fire = true;
	fire();

	
}


void ADNPlayerCharacter::fire()
{
	if (_is_armed_weapon == false)
		return;
		
	if (_is_fire)
	{
		
		_line_trace->OnFire(this);

		ADNPlayerController* controller = dynamic_cast<ADNPlayerController*>(GetController());

		if (controller->get_camera_shake() != nullptr)
			controller->ClientStartCameraShake(controller->get_camera_shake());


		UE_LOG(LogTemp, Warning, TEXT("Player Timer : %s"), *_fire_timer.ToString());
		GetWorld()->GetTimerManager().SetTimer(_fire_timer, this, &ADNPlayerCharacter::fire, 0.075f, true);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Attack Now"));

	}

}


void ADNPlayerCharacter::armed()
{
	Super::armed();

	player_arm_event(_is_armed_weapon);
}


void ADNPlayerCharacter::crouch()
{
	Super::crouch();
	player_crouch_event(_is_crouch);
}


void ADNPlayerCharacter::player_arm_event(bool armed_in)
{
	on_armed.Broadcast(armed_in);
}

void ADNPlayerCharacter::player_crouch_event(bool crouch_in)
{
	on_crouch.Broadcast(crouch_in);
}