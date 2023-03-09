


#include "UE5_Training_Project/UI/Widget/Panel/DNCrosshairPanel.h"




void UDNCrosshairPanel::NativeConstruct()
{
	set_panel_type(E_UI_PANEL_TYPE::UPT_CROSSHAIR);
	Super::NativeConstruct();

}


void UDNCrosshairPanel::NativeDestruct()
{
	Super::NativeDestruct();

}


void UDNCrosshairPanel::add_event()
{

}


void UDNCrosshairPanel::remove_event()
{

}


void UDNCrosshairPanel::play_hit_animation()
{
	if (IsValid(umg_hit_animation))
	{
		PlayAnimation(umg_hit_animation);
	}
}


void UDNCrosshairPanel::play_critical_hit_animation()
{
	if (IsValid(umg_hit_animation))
	{
		PlayAnimation(umg_hit_animation);
	}

	if (IsValid(umg_critical_hit_animation))
	{
		PlayAnimation(umg_critical_hit_animation);
	}
}


void UDNCrosshairPanel::play_damaged_animation()
{

	if (IsValid(umg_damaged_animation))
	{
		PlayAnimation(umg_damaged_animation);
	}
}