


#include "UE5_Training_Project/UI/Widget/Panel/DNLobbyPanel.h"

// Button
#include "UE5_Training_Project/UI/Component/Button/DNLobbySelectButton.h"
#include "UE5_Training_Project/UI/Component/Button/DNCommonButton.h"


void UDNLobbyPanel::NativeConstruct()
{
	set_panel_type(E_UI_PANEL_TYPE::UPT_CHARACTER_SELECT);
	Super::NativeConstruct();
	init_panel();
}


void UDNLobbyPanel::NativeDestruct()
{
	Super::NativeDestruct();
}


void UDNLobbyPanel::add_event()
{

}


void UDNLobbyPanel::remove_event()
{

}


void UDNLobbyPanel::init_panel()
{

}