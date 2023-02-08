


#include "UE5_Training_Project/UI/Base/DNBasePanel.h"


void UDNBasePanel::NativeConstruct()
{
	Super::NativeConstruct();
	UI_MANAGER->get_widget_manager()->add_panel(this);


	UE_LOG(LogTemp, Warning, TEXT("BasePanel Initialize Succeed"));
}


void UDNBasePanel::NativeDestruct()
{
	Super::NativeDestruct();

}

void UDNBasePanel::update_panel()
{

}