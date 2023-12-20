


#include "UE5_Training_Project/UI/Widget/Panel/DNSelectSquadPanel.h"

// Component
#include "UE5_Training_Project/UI/Component/Button/DNCommonButton.h"

void UDNSelectSquadPanel::NativeConstruct()
{
	set_panel_type(E_UI_PANEL_TYPE::UPT_MAKE_SQUAD);
	Super::NativeConstruct();

}

void UDNSelectSquadPanel::NativeDestruct()
{
	Super::NativeDestruct();
}
