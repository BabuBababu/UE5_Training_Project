


#include "UE5_Training_Project/UI/Manager/DNWidgetManager.h"

// Panel
#include "UE5_Training_Project/UI/Base/DNBasePanel.h"



void UDNWidgetManager::init_manager()
{
	_manager_type = E_UI_MANAGER_TYPE::UMT_WIDGET_MANAGER;

}

void UDNWidgetManager::destroy_manager()
{
}



///////////////////////////////////////////////////////
// 패널
///////////////////////////////////////////////////////
void UDNWidgetManager::clear_panel_data()
{
	_panel_array.Empty();
}

void UDNWidgetManager::add_panel(UDNBasePanel* panel_in)
{
	UDNBasePanel* panel = get_panel(panel_in->get_panel_type());
	if (nullptr == panel)
	{
		if (panel_in->get_panel_type() != E_UI_PANEL_TYPE::UPT_NONE)
		{
			_panel_array.Emplace(panel_in->get_panel_type(), panel_in);
		}
	}
}

void UDNWidgetManager::remove_panel(UDNBasePanel* panel_in)
{
	UDNBasePanel* panel = get_panel(panel_in->get_panel_type());
	if (nullptr != panel)
	{
		_panel_array.Remove(panel_in->get_panel_type());
	}
}

void UDNWidgetManager::remove_panel(E_UI_PANEL_TYPE panel_type_in)
{
	UDNBasePanel* panel = get_panel(panel_type_in);
	if (nullptr != panel)
	{
		_panel_array.Remove(panel_type_in);
	}
}

UDNBasePanel* UDNWidgetManager::get_panel(E_UI_PANEL_TYPE panel_type_in) const
{
	UDNBasePanel* return_panel = _panel_array.FindRef(panel_type_in);
	return return_panel;
}

void UDNWidgetManager::open_panel(E_UI_PANEL_TYPE panel_type_in)
{
	UDNBasePanel* panel = get_panel(panel_type_in);
	if (nullptr != panel)
	{
		panel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UDNWidgetManager::close_panel(E_UI_PANEL_TYPE panel_type_in)
{
	UDNBasePanel* panel = get_panel(panel_type_in);
	if (nullptr != panel)
	{
		panel->SetVisibility(ESlateVisibility::Collapsed);
	}
}
