﻿


#include "UE5_Training_Project/UI/Widget/Panel/DNPlayerGaugeBar.h"

// Engine
#include <Components/ProgressBar.h>

// Manager
#include "UE5_Training_Project/Manager/DNSoundManager.h"
#include "UE5_Training_Project/Manager/DNUIManager.h"

// UI
#include "UE5_Training_Project/UI/Widget/Panel/DNCommentPanel.h"


void UDNPlayerGaugeBar::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDNPlayerGaugeBar::NativeDestruct()
{
	Super::NativeDestruct();
}

void UDNPlayerGaugeBar::check_gauge()
{
	E_UI_GAUGE_STATE type_state = E_UI_GAUGE_STATE::UGS_NONE; // 안보임 0, 보이지만 비활성 1, 보이고 활성 2,

	switch (_gauge_type)
	{
	case E_UI_GAUGE_TYPE::UGT_NONE:
		break;

	case E_UI_GAUGE_TYPE::UGT_HP:
		/*if (_my_character->get_combat_posture())
			type_state = E_NUI_GAUGE_STATE::NGS_OPEN_SHOW;
		else
		{
		}*/

		if (_percent_value < 1.0f)
			type_state = E_UI_GAUGE_STATE::UGS_CLOSE_SHOW;
		else
		{
			if (_has_buff)
				type_state = E_UI_GAUGE_STATE::UGS_CLOSE_SHOW;
			else
				type_state = E_UI_GAUGE_STATE::UGS_HIDE;
		}
		break;
	case E_UI_GAUGE_TYPE::UGT_BURST:
		if (_percent_value >= 1.0f)
			type_state = E_UI_GAUGE_STATE::UGS_OPEN_SHOW;
		else
			type_state = E_UI_GAUGE_STATE::UGS_HIDE;
		break;
	default:
		break;
	}

	switch (type_state)
	{
	case E_UI_GAUGE_STATE::UGS_HIDE:
		set_gauge_visibility(false);
		set_gauge_enable(false);
		break;
	case E_UI_GAUGE_STATE::UGS_CLOSE_SHOW:
		set_gauge_visibility(true);
		set_gauge_enable(false);
		break;
	case E_UI_GAUGE_STATE::UGS_OPEN_SHOW:
		set_gauge_visibility(true);
		set_gauge_enable(true);
		break;
	default:
		set_gauge_visibility(false);
		set_gauge_enable(false);
		break;
	}
}

void UDNPlayerGaugeBar::set_gauge(float current_value_in, float max_value_in)
{
	_current_value = current_value_in;
	_max_value = max_value_in;
	_percent_value = _current_value / _max_value;



	if (umg_main_progress != nullptr)
	{
		umg_main_progress->SetPercent(_percent_value);
	}


	// 체력이 일정수치 이하로 떨어지면 경고음 플래그 온
	if (_percent_value <= 0.4f && false == SOUND_MANAGER->_is_ui_danger_now)
	{
		SOUND_MANAGER->stop_meta_sound(E_SOUND_TYPE::ST_UI, -1);
		SOUND_MANAGER->stop_meta_sound(E_SOUND_TYPE::ST_BGM, -1);

		SOUND_MANAGER->play_meta_sound(E_SOUND_TYPE::ST_UI, 4);
		SOUND_MANAGER->play_meta_sound(E_SOUND_TYPE::ST_BGM, 3);
		SOUND_MANAGER->_is_ui_danger_now = true;

		UDNBasePanel* panel = WIDGET_MANAGER->get_panel(E_UI_PANEL_TYPE::UPT_COMMENT);
		if (IsValid(panel))
		{
			UDNCommentPanel* widget = Cast<UDNCommentPanel>(panel);

			if (IsValid(widget))
			{
				widget->play_comment_isac(4);
			}
		}
	}

	// 체력을 일정수치 이상으로 회복했다면 경고문 플래그 오프					//인형용 체력바 클래스 만들어서 쭉 긁어오고 이부분만 고치기
	if (_percent_value > 0.4f)
	{
		SOUND_MANAGER->_is_ui_danger_now = false;
	}
	

}

void UDNPlayerGaugeBar::set_gauge_enable(bool is_enable_in)
{
	_is_enable = is_enable_in;
	if (_is_enable)
		this->SetRenderOpacity(1.0f);
	else
		this->SetRenderOpacity(0.4f);

}

void UDNPlayerGaugeBar::set_gauge_visibility(bool is_visibility_in)
{
	_is_visible = is_visibility_in;

	if (_is_visible)
	{
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}