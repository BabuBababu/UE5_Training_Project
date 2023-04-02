


#include "UE5_Training_Project/UI/Component/Button/DNScheduleCharacterButton.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"
#include "UE5_Training_Project/Manager/DNLobbyNPCManager.h"

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"


void UDNScheduleCharacterButton::NativeConstruct()
{
	Super::NativeConstruct();
	SetIsEnabled(false);		// 처음에는 상호작용 불가로 해둡니다.
}

void UDNScheduleCharacterButton::NativeDestruct()
{
	Super::NativeDestruct();
}

void UDNScheduleCharacterButton::add_event()
{
	Super::add_event();

	if (IsValid(umg_button))
	{
		umg_button->OnClicked.AddDynamic(this, &UDNScheduleCharacterButton::change_manager_working_array_handler);
	}

}

void UDNScheduleCharacterButton::remove_event()
{

	if (IsValid(umg_button))
	{
		umg_button->OnClicked.RemoveDynamic(this, &UDNScheduleCharacterButton::change_manager_working_array_handler);
	}



	Super::remove_event();
}

void UDNScheduleCharacterButton::init()
{
	set_character_texture();
	set_character_text();
}


void UDNScheduleCharacterButton::set_character_texture()
{

	if (IsValid(umg_character_image))
	{
		UTexture2D* texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *_character_data.character_portrait_image_path));
		if(nullptr != texture)
			umg_character_image->SetBrushFromTexture(texture);
	}


}

void UDNScheduleCharacterButton::set_character_text()
{
	if (IsValid(umg_character_text))
	{
		umg_character_text->SetText(FText::FromString(_character_data.character_name));
	}
}


void UDNScheduleCharacterButton::init_data(FDNCharacterData data_in)
{
	// 받아온 데이터를 적용합니다.

	_character_data = data_in;

	init();
}

void UDNScheduleCharacterButton::reset_data()
{
	_character_data.reset();
	init();
}




void UDNScheduleCharacterButton::change_manager_working_array_handler()
{

	//로비NPC 매니저의 근무 배열에 추가
	if (_work_type == E_LOBBY_AI_TYPE::LAT_PATROL)
	{
		for ( auto & character : OBJECT_MANAGER->_all_gained_doll_array)
		{
			if (character->_character_id == _character_data.character_id)
			{
				ADNUnEnemyCharacter* doll = Cast<ADNUnEnemyCharacter>(character);
				LOBBY_MANAGER->set_on_patrol(doll);
			}
		}
	}
	else if (_work_type == E_LOBBY_AI_TYPE::LAT_GUARD)
	{
		for (auto& character : OBJECT_MANAGER->_all_gained_doll_array)
		{
			if (character->_character_id == _character_data.character_id)
			{
				ADNUnEnemyCharacter* doll = Cast<ADNUnEnemyCharacter>(character);
				LOBBY_MANAGER->set_on_guard(doll);
			}
		}
	}
	else if (_work_type == E_LOBBY_AI_TYPE::LAT_POST)
	{
		for (auto& character : OBJECT_MANAGER->_all_gained_doll_array)
		{
			if (character->_character_id == _character_data.character_id)
			{
				ADNUnEnemyCharacter* doll = Cast<ADNUnEnemyCharacter>(character);
				LOBBY_MANAGER->set_on_post(doll);
			}
		}
	}


	// 적용이 끝났다면 끝났다는 델리게이트를 다시 스케쥴 리스트에게 보냅니다. 이 버튼에 데이터를 적용하기 위해
	OnStopAnimation.Broadcast(this);

}