


#include "UE5_Training_Project/UI/Manager/DNWidgetManager.h"

// Panel
#include "UE5_Training_Project/UI/Base/DNBasePanel.h"

// Content
#include "UE5_Training_Project/UI/Base/DNBaseContent.h"


void UDNWidgetManager::initialize()
{
	_manager_type = E_MANAGER_TYPE::MT_WIDGET_MANAGER;

	Super::initialize();

}

void UDNWidgetManager::destroy()
{
	clear_panel_data();

	Super::destroy();
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
	if (_panel_array.IsEmpty())
		return nullptr;
		
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


///////////////////////////////////////////////////////
// 컨텐츠
///////////////////////////////////////////////////////

void UDNWidgetManager::clear_content_data()
{
	_content_array.Empty();
}

void UDNWidgetManager::add_content(UDNBaseContent* content_in)
{
	UDNBaseContent* content = get_content(content_in->get_content_type());
	if (nullptr == content)
	{
		if (content_in->get_content_type() != E_UI_CONTENT_TYPE::UCT_NONE)
		{
			_content_array.Emplace(content_in->get_content_type(), content_in);
		}
	}
}

void UDNWidgetManager::remove_content(UDNBaseContent* content_type_in)
{
	UDNBaseContent* content = get_content(content_type_in->get_content_type());
	if (nullptr != content)
	{
		_content_array.Remove(content_type_in->get_content_type());
	}
}

void UDNWidgetManager::remove_content(E_UI_CONTENT_TYPE content_type_in)
{
	UDNBaseContent* panel = get_content(content_type_in);
	if (nullptr != panel)
	{
		_content_array.Remove(content_type_in);
	}
}

UDNBaseContent* UDNWidgetManager::get_content(E_UI_CONTENT_TYPE content_type_in) const
{
	if (_content_array.IsEmpty())
		return nullptr;

	UDNBaseContent* return_content = _content_array.FindRef(content_type_in);
	return return_content;
}

void UDNWidgetManager::open_content(E_UI_CONTENT_TYPE content_type_in)
{
	UDNBaseContent* content = get_content(content_type_in);
	if (nullptr != content)
	{
		content->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UDNWidgetManager::close_content(E_UI_CONTENT_TYPE content_type_in)
{
	UDNBaseContent* content = get_content(content_type_in);
	if (nullptr != content)
	{
		content->SetVisibility(ESlateVisibility::Collapsed);
	}
}
