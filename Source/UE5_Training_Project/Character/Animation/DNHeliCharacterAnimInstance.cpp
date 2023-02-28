


#include "UE5_Training_Project/Character/Animation/DNHeliCharacterAnimInstance.h"


// Character
#include "UE5_Training_Project/Character/DNHeliCommonCharacter.h"


UDNHeliCharacterAnimInstance::UDNHeliCharacterAnimInstance()
{

}

void UDNHeliCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (false == IsValid(TryGetPawnOwner()))
		return;


	ADNHeliCommonCharacter* character = Cast<ADNHeliCommonCharacter>(TryGetPawnOwner());

	if (nullptr == character)
		return;

	_rotor_mast_anim = character->_rotor_mast;
	_rotor_back_anim = character->_rotor_back;
	_rotor_minigun_anim = character->_rotor_minigun;

}