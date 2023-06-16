


#include "UE5_Training_Project/UI/Widget/Panel/DNEnemyStatusPanel.h"

// Panel
#include "UE5_Training_Project/UI/Widget/Panel/DNPlayerGaugeBar.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"


// Component
#include "UE5_Training_Project/Component/DNStatusComponent.h"

void UDNEnemyStatusPanel::NativeConstruct()
{
	set_panel_type(E_UI_PANEL_TYPE::UPT_ENEMY_STATUS);
	Super::NativeConstruct();
}


void UDNEnemyStatusPanel::NativeDestruct()
{
	Super::NativeDestruct();
}



void UDNEnemyStatusPanel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	sync_gauge();
}



void UDNEnemyStatusPanel::add_event()
{
	Super::add_event();
}


void UDNEnemyStatusPanel::remove_event()
{
	Super::remove_event();
}



void UDNEnemyStatusPanel::init_data(FDNCharacterData* data_in)		// 위젯 인덱스 동기화용, 데이터 받아서 바로 넣어주기
{
	if (nullptr == data_in)
		return;


	if (IsValid(umg_main_image))
	{
		UTexture2D* texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *data_in->character_portrait_image_path));
		if (nullptr != texture)
		{
			umg_main_image->SetBrushFromTexture(texture);
		}
	}

	if (IsValid(umg_name_text))
	{
		umg_name_text->SetText(FText::FromString(data_in->character_name));
	}

	if (IsValid(umg_main_hp_bar))
	{
		umg_main_hp_bar->set_gauge_type(E_UI_GAUGE_TYPE::UGT_HP);
	}
}




void UDNEnemyStatusPanel::sync_gauge()
{
	//오브젝트 매니저에서 해당 적 가져와서 싱크 맞추기
	//for (const auto& doll : OBJECT_MANAGER->_in_squad_doll_array)
	//{
	//	if (nullptr != doll.Value)
	//	{
	//		if (nullptr != doll.Value && doll.Value->_squad_index == get_widget_index())		// 해당 인형의 스쿼드 인덱스와 이 슬롯의 인덱스가 같다면
	//		{
	//			if (false == doll.Value->_status->_dead)										// 죽지 않았다면
	//			{
	//				_current_hp = doll.Value->_status->_current_hp;
	//				_max_hp = doll.Value->_status->get_max_hp();
	//				set_hp(_current_hp, _max_hp);
	//			}
	//		}
	//	}
	//}

}


void UDNEnemyStatusPanel::set_hp(float current_hp_in, float max_hp_in)
{
	if (umg_main_hp_bar != nullptr)
	{
		umg_main_hp_bar->set_gauge(current_hp_in, max_hp_in);
	}
}


void UDNEnemyStatusPanel::play_damaged_animation()
{
	if (nullptr != umg_damaged_animation)
	{
		PlayAnimation(umg_damaged_animation);
	}
}
