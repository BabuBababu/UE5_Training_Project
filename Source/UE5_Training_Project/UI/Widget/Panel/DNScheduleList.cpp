


#include "UE5_Training_Project/UI/Widget/Panel/DNScheduleList.h"

// Button
#include "UE5_Training_Project/UI/Component/Button/DNScheduleCharacterButton.h"




void UDNScheduleList::NativeConstruct()
{
	Super::NativeConstruct();
	_character_button_array.Empty();


	if (IsValid(umg_guard_character_button_1))
		_character_button_array.Emplace(umg_guard_character_button_1);
	if (IsValid(umg_guard_character_button_2))
		_character_button_array.Emplace(umg_guard_character_button_2);
	if (IsValid(umg_patrol_character_button_1))
		_character_button_array.Emplace(umg_patrol_character_button_1);
	if (IsValid(umg_patrol_character_button_2))
		_character_button_array.Emplace(umg_patrol_character_button_2);
	if (IsValid(umg_post_character_button_1))
		_character_button_array.Emplace(umg_post_character_button_1);

}

void UDNScheduleList::NativeDestruct()
{
	Super::NativeDestruct();

}

void UDNScheduleList::add_event()
{
	Super::add_event();

	if (IsValid(umg_guard_character_button_1))
		umg_guard_character_button_1->OnStopAnimation.AddDynamic(this, &UDNScheduleList::stop_click_animation_handler);
	
	if (IsValid(umg_guard_character_button_2))
		umg_guard_character_button_2->OnStopAnimation.AddDynamic(this, &UDNScheduleList::stop_click_animation_handler);
	
	if (IsValid(umg_patrol_character_button_1))
		umg_patrol_character_button_1->OnStopAnimation.AddDynamic(this, &UDNScheduleList::stop_click_animation_handler);
	
	if (IsValid(umg_patrol_character_button_2))
		umg_patrol_character_button_2->OnStopAnimation.AddDynamic(this, &UDNScheduleList::stop_click_animation_handler);

	if (IsValid(umg_post_character_button_1))
		umg_post_character_button_1->OnStopAnimation.AddDynamic(this, &UDNScheduleList::stop_click_animation_handler);


}

void UDNScheduleList::remove_event()
{
	Super::remove_event();
	if (IsValid(umg_guard_character_button_1))
		umg_guard_character_button_1->OnStopAnimation.RemoveDynamic(this, &UDNScheduleList::stop_click_animation_handler);

	if (IsValid(umg_guard_character_button_2))
		umg_guard_character_button_2->OnStopAnimation.RemoveDynamic(this, &UDNScheduleList::stop_click_animation_handler);

	if (IsValid(umg_patrol_character_button_1))
		umg_patrol_character_button_1->OnStopAnimation.RemoveDynamic(this, &UDNScheduleList::stop_click_animation_handler);

	if (IsValid(umg_patrol_character_button_2))
		umg_patrol_character_button_2->OnStopAnimation.RemoveDynamic(this, &UDNScheduleList::stop_click_animation_handler);

	if (IsValid(umg_post_character_button_1))
		umg_post_character_button_1->OnStopAnimation.RemoveDynamic(this, &UDNScheduleList::stop_click_animation_handler);

}

void UDNScheduleList::store_data_handler(FDNCharacterData data_in)
{
	// 스케쥴 위젯에서 캐릭터버튼의 델리게이트를 바인딩해서 이 핸들러를 호출합니다.

	_send_character_data = data_in;
	play_click_animation_handler();

}
void UDNScheduleList::play_click_animation_handler()
{
	play_clicked_animation();

	if (IsValid(umg_guard_character_button_1))
		umg_guard_character_button_1->SetIsEnabled(true);

	if (IsValid(umg_guard_character_button_2))
		umg_guard_character_button_2->SetIsEnabled(true);

	if (IsValid(umg_patrol_character_button_1))
		umg_patrol_character_button_1->SetIsEnabled(true);

	if (IsValid(umg_patrol_character_button_2))
		umg_patrol_character_button_2->SetIsEnabled(true);

	if (IsValid(umg_post_character_button_1))
		umg_post_character_button_1->SetIsEnabled(true);
}

void UDNScheduleList::stop_click_animation_handler(UDNScheduleCharacterButton* button_in)
{
	//중복이 있는지 체크
	for (auto& obj : _character_button_array)
	{
		if (obj->get_data().character_id == _send_character_data.character_id)
		{
			obj->reset_data();
		}
	}



	for (auto& button : _character_button_array)
	{
		
		if (button == button_in)
		{
			
			button->init_data(_send_character_data);
		}
	}

	_send_character_data.reset();

	stop_animation();

	if (IsValid(umg_guard_character_button_1))
		umg_guard_character_button_1->SetIsEnabled(false);

	if (IsValid(umg_guard_character_button_2))
		umg_guard_character_button_2->SetIsEnabled(false);

	if (IsValid(umg_patrol_character_button_1))
		umg_patrol_character_button_1->SetIsEnabled(false);

	if (IsValid(umg_patrol_character_button_2))
		umg_patrol_character_button_2->SetIsEnabled(false);

	if (IsValid(umg_post_character_button_1))
		umg_post_character_button_1->SetIsEnabled(false);
}



void UDNScheduleList::play_clicked_animation()
{
	if (nullptr != umg_click_animation)
	{
		PlayAnimation(umg_click_animation, 0.f, 0);
	}
}


void UDNScheduleList::stop_animation()
{
	if (nullptr != umg_click_animation)
	{
		if (umg_click_animation)
		{
			StopAnimation(umg_click_animation);
		}
	}
}