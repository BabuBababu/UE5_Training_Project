


#include "UE5_Training_Project/UI/Widget/Panel/DNPlayerCombatPanel.h"

// Panel
#include "UE5_Training_Project/UI/Widget/Panel/DNPlayerGaugeBar.h"

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Component
#include <UE5_Training_Project/Component/DNStatusComponent.h>


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
	ADNCommonCharacter* character = dynamic_cast<ADNCommonCharacter*>(GetWorld()->GetFirstPlayerController()->GetPawn());
	_current_ammo = character->_status->_current_ammo;
	_has_ammo = character->_status->_has_ammo;
	_current_hp = character->_status->_current_hp;
	_max_hp = character->_status->get_max_hp();


	FString has_ammo = FString::FromInt(_has_ammo);
	FString current_ammo = FString::FromInt(_current_ammo);
	
	set_hp(_current_hp, _max_hp);
	umg_current_ammo_text.Get()->SetText(FText::FromString(current_ammo));
	umg_save_ammo_text.Get()->SetText(FText::FromString(has_ammo));

	//set_sp(_current_sp, _max_sp);	//이건 보류
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