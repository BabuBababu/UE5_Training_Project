


#include "UE5_Training_Project/UI/Widget/Panel/DNPlayerGaugeBar.h"

// Engine
#include <Components/ProgressBar.h>


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
	case E_UI_GAUGE_TYPE::UGT_SP:
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

	check_gauge();
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