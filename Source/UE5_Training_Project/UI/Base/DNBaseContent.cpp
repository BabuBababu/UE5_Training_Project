


#include "UE5_Training_Project/UI/Base/DNBaseContent.h"


void UDNBaseContent::NativeConstruct()
{
	Super::NativeConstruct();
	UI_MANAGER->get_widget_manager()->add_content(this);


	UE_LOG(LogTemp, Warning, TEXT("BaseContent Initialize Succeed"));
}


void UDNBaseContent::NativeDestruct()
{
	Super::NativeDestruct();

}

void UDNBaseContent::update_content()
{

}