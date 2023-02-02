


#include "UE5_Training_Project/UI/Base/DNBaseWidget.h"


void UDNBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();
	add_event();
}

void UDNBaseWidget::NativeDestuct()
{
	remove_event();
	Super::NativeDestruct();
}


void UDNBaseWidget::add_event()
{

}

void UDNBaseWidget::remove_event()
{

}
