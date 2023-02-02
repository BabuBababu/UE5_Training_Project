


#include "UE5_Training_Project/UI/Widget/Panel/DNPlayerCombatPanel.h"

// Panel
#include "UE5_Training_Project/UI/Widget/Panel/DNPlayerGaugeBar.h"


void UDNPlayerCombatPanel::NativeConstruct()
{
	set_panel_type(E_UI_PANEL_TYPE::UPT_GAUGE);

	Super::NativeConstruct();

	init_gauge();
}

void UDNPlayerCombatPanel::NativeDestruct()
{
	Super::NativeDestruct();
}

void UDNPlayerCombatPanel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	sync_gauge();
}

void UDNPlayerCombatPanel::add_event()
{
	//핸들러 추가예정
	Super::add_event();
}

void UDNPlayerCombatPanel::remove_event()
{
	Super::remove_event();
}


void UDNPlayerCombatPanel::init_gauge()
{

	if (umg_bar_hp != nullptr)
	{
		umg_bar_hp->set_gauge_type(E_UI_GAUGE_TYPE::UGT_HP);
	}
	/*if (UNUIUtil::IsValid(umg_buff_panel))
	{
		umg_buff_panel->set_is_my_character(true);
	}*/
}


// 플레이어 캐릭터 및 인형들 게이지 싱크맞추기
void UDNPlayerCombatPanel::sync_gauge()
{
	//_current_hp = NUI_MANAGER->player_current_life;
	//_max_hp = NUI_MANAGER->player_max_life;


	//_current_sp = NUI_MANAGER->player_current_stamina;
	//_max_sp = NUI_MANAGER->player_max_stamina;

	//set_hp(_current_hp, _max_hp);
	//set_sp(_current_sp, _max_sp);
}

void UDNPlayerCombatPanel::set_hp(float current_hp_in, float max_hp_in)
{
	if (umg_bar_hp != nullptr)
	{
		umg_bar_hp->set_gauge(current_hp_in, max_hp_in);
	}
}



void UDNPlayerCombatPanel::set_player_character()
{

}