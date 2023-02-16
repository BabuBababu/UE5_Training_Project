


#include "UE5_Training_Project/UI/Widget/Panel/DNSquadSlot.h"


// Panel
#include "UE5_Training_Project/UI/Widget/Panel/DNPlayerGaugeBar.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"


// Component
#include "UE5_Training_Project/Component/DNStatusComponent.h"


void UDNSquadSlot::NativeConstruct()
{
	Super::NativeConstruct();
	add_event();
}

void UDNSquadSlot::NativeDestruct()
{
	remove_event();
	Super::NativeDestruct();
}

void UDNSquadSlot::add_event()
{
}

void UDNSquadSlot::remove_event()
{
}



void UDNSquadSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	sync_gauge();
}

void UDNSquadSlot::init_data(int64 squad_index_in , FDNCharacterData * data_in)		// 위젯 인덱스 동기화용, 데이터 받아서 바로 넣어주기
{
	set_widget_index(squad_index_in);


	if (IsValid(umg_image))
	{
		UTexture2D* texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *data_in->character_portrait_image_path));
		if (nullptr != texture)
		{
			umg_image->SetBrushFromTexture(texture);
		}
	}

	if (IsValid(umg_name_text))
	{
		umg_name_text->SetText(FText::FromString(data_in->character_name));
	}

	if (IsValid(umg_hp_bar))
	{
		umg_hp_bar->set_gauge_type(E_UI_GAUGE_TYPE::UGT_HP);
	}
}




void UDNSquadSlot::sync_gauge()
{
	//오브젝트 매니저에서 해당 인형 가져와서 싱크 맞추기
	for (const auto& doll : OBJECT_MANAGER->_in_squad_doll_array)
	{
		if (doll.Value->_squad_index == get_widget_index())		// 해당 인형의 스쿼드 인덱스와 이 슬롯의 인덱스가 같다면
		{
			_current_hp = doll.Value->_status->_current_hp;
			_max_hp = doll.Value->_status->get_max_hp();
		}
	}

	set_hp(_current_hp, _max_hp);

}


void UDNSquadSlot::set_hp(float current_hp_in, float max_hp_in)
{
	if (umg_hp_bar != nullptr)
	{
		umg_hp_bar->set_gauge(current_hp_in, max_hp_in);
	}
}


void UDNSquadSlot::play_damaged_animation()
{
	if (nullptr != umg_damaged_animation)
	{
		PlayAnimation(umg_damaged_animation);
	}
}