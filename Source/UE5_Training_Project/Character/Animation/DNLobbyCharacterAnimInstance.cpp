


#include "UE5_Training_Project/Character/Animation/DNLobbyCharacterAnimInstance.h"


// Engine
#include <GameFramework/PawnMovementComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <KismetAnimationLibrary.h>
#include <Engine/Classes/Kismet/GameplayStatics.h>

// UI
#include "UE5_Training_Project/UI/Base/DNBasePanel.h"
#include "UE5_Training_Project/UI/Widget/Panel/DNLobbyPanel.h"
#include "UE5_Training_Project/UI/Component/Button/DNLobbySelectButton.h"

// Character
#include "UE5_Training_Project/Character/DNPlayerCharacter.h"

// Controller
#include "UE5_Training_Project/Controller/DNPlayerController.h"

// Manager
#include "UE5_Training_Project/Manager/DNUIManager.h"
#include "UE5_Training_Project/UI/Manager/DNWidgetManager.h"


UDNLobbyCharacterAnimInstance::UDNLobbyCharacterAnimInstance()
{

}



void UDNLobbyCharacterAnimInstance::add_event()
{
	UDNBasePanel* panel = WIDGET_MANAGER->get_panel(E_UI_PANEL_TYPE::UPT_CHARACTER_SELECT);
	if (true == IsValid(panel))
	{
		UDNLobbyPanel* lobby_panel = Cast<UDNLobbyPanel>(panel);
		if (nullptr != lobby_panel)
		{
			if (false == lobby_panel->get_start_button()->OnSelected.IsBound())
				lobby_panel->get_start_button()->OnSelected.AddDynamic(this, &UDNLobbyCharacterAnimInstance::play_walking_montage);

		}
	}
	
}

void UDNLobbyCharacterAnimInstance::remove_event()
{
	UDNBasePanel* panel = WIDGET_MANAGER->get_panel(E_UI_PANEL_TYPE::UPT_CHARACTER_SELECT);
	if (true == IsValid(panel))
	{
		UDNLobbyPanel* lobby_panel = Cast<UDNLobbyPanel>(panel);
		if (nullptr != lobby_panel)
		{
			if (true == lobby_panel->get_start_button()->OnSelected.IsBound())
				lobby_panel->get_start_button()->OnSelected.RemoveDynamic(this, &UDNLobbyCharacterAnimInstance::play_walking_montage);

		}
	}
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

	// 걷기 재생 체크
	if (true == _playing_walking_montage)
	{
		if (false == Montage_IsPlaying(lobby_walking_montage))
			on_walking_montage_ended();
	}

}



void UDNLobbyCharacterAnimInstance::on_walking_montage_ended()
{
	_playing_walking_montage = false;
	OnWalkingEnd.Broadcast();
}



void UDNLobbyCharacterAnimInstance::play_walking_montage()
{
	if (false == _playing_walking_montage)
	{
		Montage_Play(lobby_walking_montage);
		_playing_walking_montage = true;
	}

}