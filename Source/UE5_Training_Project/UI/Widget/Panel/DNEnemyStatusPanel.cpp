


#include "UE5_Training_Project/UI/Widget/Panel/DNEnemyStatusPanel.h"

// Panel
#include "UE5_Training_Project/UI/Widget/Panel/DNPlayerGaugeBar.h"

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

	sync_status();
}



void UDNEnemyStatusPanel::add_event()
{
	Super::add_event();

}


void UDNEnemyStatusPanel::remove_event()
{
	Super::remove_event();
}

void UDNEnemyStatusPanel::add_function_handler(ADNPlayerCharacter* player_in)
{

	if (nullptr != player_in)
	{
		if (false == player_in->_line_trace->OnTargetAiming.IsBound())
			player_in->_line_trace->OnTargetAiming.AddDynamic(this, &UDNEnemyStatusPanel::init_status_data_handler);
	}
}

void UDNEnemyStatusPanel::remove_function_handler(ADNPlayerCharacter* player_in)
{
	if (nullptr != player_in)
	{
		if (player_in->_line_trace->OnTargetAiming.IsBound())
			player_in->_line_trace->OnTargetAiming.RemoveDynamic(this, &UDNEnemyStatusPanel::init_status_data_handler);
	}
		
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




void UDNEnemyStatusPanel::sync_status()
{

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("sync 444444444444444444444444")));
	if (nullptr == _enemy)
		return;

	//오브젝트 매니저에서 해당 적 가져와서 싱크 맞추기
	for (const auto& enemy : OBJECT_MANAGER->_all_spawned_enemy_array)
	{
		if (enemy == _enemy)
		{
			if (false == enemy->_status->_dead)										// 죽지 않았다면
			{
				_current_hp = enemy->_status->_current_hp;
				_max_hp = enemy->_status->get_max_hp();
				set_hp(_current_hp, _max_hp);

				FString current = FString::FromInt(_current_hp);
				FString max = FString::FromInt(_max_hp);

				umg_current_hp_text->SetText(FText::FromString(current));
				umg_max_hp_text->SetText(FText::FromString(max));
			}
			else                                                                    // 죽었다면
			{
				SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}
}


void UDNEnemyStatusPanel::set_hp(float current_hp_in, float max_hp_in)
{
	if (umg_main_hp_bar != nullptr)
	{
		umg_main_hp_bar->set_gauge(current_hp_in, max_hp_in);
	}
}


void UDNEnemyStatusPanel::play_damaged_animation(ADNCommonCharacter* damaged_character_in)
{
	if (_enemy != damaged_character_in)
		return;

	if (nullptr != umg_damaged_animation)
	{
		PlayAnimation(umg_damaged_animation);
	}
}

void UDNEnemyStatusPanel::init_status_data_handler(ADNEnemyCharacter* enemy_in)
{
	if (nullptr == enemy_in)
		return;

	if (enemy_in->get_status_component()->_dead)
		return;
	
	_enemy = enemy_in;
	init_data(enemy_in->get_status_component()->_chartacter_data);
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}