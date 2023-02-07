


#include "UE5_Training_Project/UI/Widget/Panel/DNInteractionPanel.h"

// Actor
#include "UE5_Training_Project/Actor/DNCommonActor.h"




void UDNInteractionPanel::NativeConstruct()
{
	set_panel_type(E_UI_PANEL_TYPE::UPT_INTERACTION);
	//_actor_data = nullptr;
	Super::NativeConstruct();

}



void UDNInteractionPanel::NativeDestruct()
{
	Super::NativeDestruct();

}


void UDNInteractionPanel::change_interaction_type(E_UI_INTERACTION_TYPE type_in)
{
	// 이미지는 아직 넣지않음

	if (nullptr == _umg_item_text ||
		nullptr == _umg_vehicle_text ||
		nullptr == _umg_npc_text)
		return;


	if (type_in == E_UI_INTERACTION_TYPE::UIT_ITEM)
	{
		_umg_item_text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		_umg_vehicle_text->SetVisibility(ESlateVisibility::Collapsed);
		_umg_npc_text->SetVisibility(ESlateVisibility::Collapsed);

	}
	else if (type_in == E_UI_INTERACTION_TYPE::UIT_VEHICLE)
	{

		_umg_item_text->SetVisibility(ESlateVisibility::Collapsed);
		_umg_vehicle_text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		_umg_npc_text->SetVisibility(ESlateVisibility::Collapsed);
	}
	else if (type_in == E_UI_INTERACTION_TYPE::UIT_NPC)
	{

		_umg_item_text->SetVisibility(ESlateVisibility::Collapsed);
		_umg_vehicle_text->SetVisibility(ESlateVisibility::Collapsed);
		_umg_npc_text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}