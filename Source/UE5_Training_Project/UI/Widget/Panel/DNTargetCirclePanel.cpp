


#include "UE5_Training_Project/UI/Widget/Panel/DNTargetCirclePanel.h"

// Engine
#include "Materials/MaterialInstanceDynamic.h"

// Actor
#include "UE5_Training_Project/Actor/DNPatternTargetActor.h"


void UDNTargetCirclePanel::NativeConstruct()
{
	set_panel_type(E_UI_PANEL_TYPE::UPT_TARGET_CIRCLE);
	Super::NativeConstruct();
	init();
}

void UDNTargetCirclePanel::NativeDestruct()
{
	Super::NativeDestruct();

}

void UDNTargetCirclePanel::add_event()
{
	Super::add_event();

}

void UDNTargetCirclePanel::remove_event()
{
	Super::remove_event();

}

void UDNTargetCirclePanel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// 시간 동기화
	set_time_percent(_current_time);

	_current_time -= InDeltaTime;

	if (_current_time == 0)
	{
		init();
		SetVisibility(ESlateVisibility::Collapsed);	//시간이 다 되었으니 틱은 더이상 작동되면 안되므로
	}
}

void UDNTargetCirclePanel::set_widget(ADNPatternTargetActor* owner_in)
{
	if (nullptr == owner_in)
		return;

	if (false == IsValid(umg_main_overlay))
		return;

	if (false == IsValid(umg_target_time_circle_icon))
		return;

	if (false == IsValid(umg_target_circle_icon))
		return;


	_owner = owner_in;

	// 시간
	_max_time = owner_in->get_limit_max_time();
	_current_time = _owner->get_limit_current_time();

	// HP
	_max_hp = owner_in->get_max_hp();
	_current_hp = _owner->get_current_hp();

	// HP 동기화
	set_hp_percent(_current_hp);

	if(_current_hp > 0)  // 살아 있을 경우
		SetVisibility(ESlateVisibility::HitTestInvisible);
	else
	{
		init();
		SetVisibility(ESlateVisibility::Collapsed);
	}

}

void UDNTargetCirclePanel::close_widget()
{
	SetVisibility(ESlateVisibility::Hidden);	//틱은 정상작동 되야하므로
}

void UDNTargetCirclePanel::set_time_percent(float time_in)
{
	float percent = time_in / _max_time;


	UMaterialInstanceDynamic* material = umg_target_time_circle_icon->GetDynamicMaterial();
	if (IsValid(material))
	{
		material->SetScalarParameterValue("percent", percent);
	}

	
}

void UDNTargetCirclePanel::set_hp_percent(float hp_in)
{
	float percent = hp_in / _max_hp;

	UMaterialInstanceDynamic* material = umg_target_circle_icon->GetDynamicMaterial();
	if (IsValid(material))
	{
		material->SetScalarParameterValue("percent", percent);
	}

}

void UDNTargetCirclePanel::init()
{
	_max_time = 0.f;
	_current_time = 0.f;
	_current_hp = 0.f;
	_max_hp = 0.f;
	_owner = nullptr;
}