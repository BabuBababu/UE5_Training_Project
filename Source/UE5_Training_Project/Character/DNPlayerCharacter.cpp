


#include "UE5_Training_Project/Character/DNPlayerCharacter.h"

// Controller
#include "UE5_Training_Project/Controller/DNPlayerController.h"




void ADNPlayerCharacter::fire()
{
	if (_is_armed_weapon == false)
		return;

	Super::fire();

	ADNPlayerController* controller = dynamic_cast<ADNPlayerController*>(GetController());

	_is_fire = true;

	if (controller->get_camera_shake() != nullptr)
		controller->ClientStartCameraShake(controller->get_camera_shake());

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