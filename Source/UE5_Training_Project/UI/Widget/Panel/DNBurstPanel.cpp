


#include "UE5_Training_Project/UI/Widget/Panel/DNBurstPanel.h"

// Panel
#include "UE5_Training_Project/UI/Widget/Panel/DNBurstGaugeBar.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"
#include "UE5_Training_Project/Character/DNEnemyCharacter.h"
#include "UE5_Training_Project/Character/DNPlayerCharacter.h"

// Component
#include "UE5_Training_Project/Component/DNStatusComponent.h"
#include "UE5_Training_Project/Character/Component/DNPlayerLineTrace.h"




void UDNBurstPanel::NativeConstruct()
{
	set_panel_type(E_UI_PANEL_TYPE::UPT_BURST_INFORMATION);

	Super::NativeConstruct();
}


void UDNBurstPanel::NativeDestruct()
{
	Super::NativeDestruct();
}



void UDNBurstPanel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	sync_status();
}



void UDNBurstPanel::add_event()
{
	Super::add_event();

}


void UDNBurstPanel::remove_event()
{
	Super::remove_event();
}

void UDNBurstPanel::add_function_handler(ADNPlayerCharacter* player_in)
{

}

void UDNBurstPanel::remove_function_handler(ADNPlayerCharacter* player_in)
{
	
}


void UDNBurstPanel::sync_status()
{
	if (nullptr == OBJECT_MANAGER->_player)
		return;


	_current_burst = OBJECT_MANAGER->_player->_burst_current_gauge;
	_max_burst = OBJECT_MANAGER->_player->_burst_max_gauge;
	set_burst(_current_burst, _max_burst);
}


void UDNBurstPanel::set_burst(float current_burst_in, float max_burst_in)
{
	if (umg_main_burst_bar != nullptr)
	{
		umg_main_burst_bar->set_gauge(current_burst_in, max_burst_in);
	}
}


void UDNBurstPanel::play_full_animation()
{
	if (nullptr != umg_full_animation)
	{
		PlayAnimation(umg_full_animation,0.f,0, EUMGSequencePlayMode::Forward, 1.f, true);
	}
}
