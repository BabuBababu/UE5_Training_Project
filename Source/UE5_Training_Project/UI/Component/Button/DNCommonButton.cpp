


#include "UE5_Training_Project/UI/Component/Button/DNCommonButton.h"

// Engine
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Components/OverlaySlot.h>
#include <Components/Image.h>

// Manager
#include "UE5_Training_Project/Manager/DNSoundManager.h"


void UDNCommonButton::update_component()
{
	Super::update_component();

	if (true == IsValid(umg_text_box))
	{
		set_text(_text);
	}

	if (true == IsValid(umg_image_icon))
	{
		set_icon_visiblilty(_icon_visibility);
	}
}

void UDNCommonButton::add_component_event()
{
	Super::add_component_event();

	if (true == IsValid(umg_button))
	{
		umg_button->OnClicked.AddDynamic(this, &UDNCommonButton::on_clicked_handler);
		umg_button->OnPressed.AddDynamic(this, &UDNCommonButton::on_pressed_handler);
		umg_button->OnReleased.AddDynamic(this, &UDNCommonButton::on_released_handler);
		umg_button->OnHovered.AddDynamic(this, &UDNCommonButton::on_hovered_handler);
		umg_button->OnUnhovered.AddDynamic(this, &UDNCommonButton::on_unhovered_handler);
	}
}

void UDNCommonButton::remove_component_event()
{
	if (true == IsValid(umg_button))
	{
		umg_button->OnClicked.RemoveDynamic(this, &UDNCommonButton::on_clicked_handler);
		umg_button->OnPressed.RemoveDynamic(this, &UDNCommonButton::on_pressed_handler);
		umg_button->OnReleased.RemoveDynamic(this, &UDNCommonButton::on_released_handler);
		umg_button->OnHovered.RemoveDynamic(this, &UDNCommonButton::on_hovered_handler);
		umg_button->OnUnhovered.RemoveDynamic(this, &UDNCommonButton::on_unhovered_handler);
	}

	Super::remove_component_event();
}

void UDNCommonButton::native_component_enabled(bool is_enabled_in)
{
	Super::native_component_enabled(is_enabled_in);

	if (get_is_component_enabled()) _button_state = E_UI_BUTTON_STATE::UBS_NORMAL;
	else _button_state = E_UI_BUTTON_STATE::UBS_DISABLED;

	set_text_color(_button_state);
}

//////////////////////////////////////////////////////////////////////////
// setting
//////////////////////////////////////////////////////////////////////////
void UDNCommonButton::set_text(FString text_in)
{
	_text = text_in;

	if (true == IsValid(umg_text_box))
	{
		if (_text.IsEmpty())
		{
			umg_text_box->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			umg_text_box->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}

		umg_text_box->SetText(FText::FromString(_text));
	}
}

void UDNCommonButton::set_icon_visiblilty(ESlateVisibility visiblilty_in)
{
	if (true == IsValid(umg_image_icon))
	{
		umg_image_icon->SetVisibility(_icon_visibility);
	}
}



void UDNCommonButton::set_text_color(E_UI_BUTTON_STATE state_in)
{
	if (true == IsValid(umg_text_box))
	{
		switch (state_in)
		{
		case E_UI_BUTTON_STATE::UBS_NORMAL:
			umg_text_box->SetColorAndOpacity(_text_color.normal_text_color);
			break;
		case E_UI_BUTTON_STATE::UBS_HOVERED:
			umg_text_box->SetColorAndOpacity(_text_color.hovered_text_color);
			break;
		case E_UI_BUTTON_STATE::UBS_PRESSED:
			umg_text_box->SetColorAndOpacity(_text_color.pressed_text_color);
			break;
		case E_UI_BUTTON_STATE::UBS_DISABLED:
			umg_text_box->SetColorAndOpacity(_text_color.disabled_text_color);
			break;
		default:
			umg_text_box->SetColorAndOpacity(_text_color.normal_text_color);
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// handler
//////////////////////////////////////////////////////////////////////////
void UDNCommonButton::on_clicked_handler()
{
	//NUI_SOUND_MANAGER->play_metasound_dev(10002); // 버튼 클릭 사운드

	set_text_color(_button_state);
	OnClicked.Broadcast(this);
}

void UDNCommonButton::on_pressed_handler()
{
	_button_state = E_UI_BUTTON_STATE::UBS_PRESSED;


	set_text_color(_button_state);
	OnPressed.Broadcast(this);
}

void UDNCommonButton::on_released_handler()
{
	_button_state = E_UI_BUTTON_STATE::UBS_HOVERED;


	set_text_color(_button_state);
	OnReleased.Broadcast(this);
}

void UDNCommonButton::on_hovered_handler()
{
	_button_state = E_UI_BUTTON_STATE::UBS_HOVERED;
	//UI_SOUND_MANAGER->play_metasound_dev(10001); // 버튼 호버 사운드


	set_text_color(_button_state);
	OnHovered.Broadcast(this);
}

void UDNCommonButton::on_unhovered_handler()
{
	_button_state = E_UI_BUTTON_STATE::UBS_NORMAL;

	set_text_color(_button_state);
	OnUnHovered.Broadcast(this);
}