


#include "UE5_Training_Project/UI/Component/Button/DNLobbySelectButton.h"


// Engine
#include <Components/Button.h>

// Button
#include "UE5_Training_Project/UI/Component/Button/DNCommonButton.h"

// Contoller
#include "UE5_Training_Project/Controller/DNLobbyController.h"


void UDNLobbySelectButton::add_component_event()
{
	Super::add_component_event();

	APlayerController* MyPlayerController = GetWorld()->GetFirstPlayerController();
	if (nullptr != MyPlayerController)
	{
		ADNLobbyController* controller = Cast<ADNLobbyController>(MyPlayerController);
		
		if (nullptr != controller)
			controller->OnSelected.AddDynamic(this, &UDNLobbySelectButton::change_state_handler);

	}
	
	OnClicked.AddDynamic(this, &UDNLobbySelectButton::selected_handler);

	

}


void UDNLobbySelectButton::remove_component_event()
{
	APlayerController* MyPlayerController = GetWorld()->GetFirstPlayerController();
	if (nullptr != MyPlayerController)
	{
		ADNLobbyController* controller = Cast<ADNLobbyController>(MyPlayerController);

		if (nullptr != controller)
			controller->OnSelected.RemoveDynamic(this, &UDNLobbySelectButton::change_state_handler);

	}
	
	OnClicked.RemoveDynamic(this, &UDNLobbySelectButton::selected_handler);

	Super::remove_component_event();
}

void UDNLobbySelectButton::change_state_handler(bool flag_in)
{
	if (false == IsValid(umg_button))
		return;

	if (flag_in)
	{
		SetIsEnabled(true);
		_button_state = E_UI_BUTTON_STATE::UBS_NORMAL;
		set_text_color(_button_state);
	}
	else
	{
		SetIsEnabled(false);
		_button_state = E_UI_BUTTON_STATE::UBS_DISABLED;
		set_text_color(_button_state);
	}

}

void UDNLobbySelectButton::selected_handler(UDNCommonButton* button_in)
{
	OnSelected.Broadcast();
}