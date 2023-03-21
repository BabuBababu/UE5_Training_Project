


#include "UE5_Training_Project/Character/Animation/DNLobbyCharacterAnimInstance.h"


// Engine
#include <GameFramework/PawnMovementComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <KismetAnimationLibrary.h>
#include <Engine/Classes/Kismet/GameplayStatics.h>

// Character
#include "UE5_Training_Project/Character/DNPlayerCharacter.h"

// Controller
#include "UE5_Training_Project/Controller/DNPlayerController.h"



UDNLobbyCharacterAnimInstance::UDNLobbyCharacterAnimInstance()
{

}

void UDNLobbyCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	ADNPlayerCharacter* character = Cast<ADNPlayerCharacter>(TryGetPawnOwner());

	if (nullptr != character)
		_owner = character;

}

void UDNLobbyCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (false == IsValid(TryGetPawnOwner()))
		return;

	if (nullptr == _owner)
		return;

	_lobby_finished = _owner->_lobby_finished;
	_select_character_lobby = _owner->_is_selected;

}