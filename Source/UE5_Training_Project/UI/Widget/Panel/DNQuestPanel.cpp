


#include "UE5_Training_Project/UI/Widget/Panel/DNQuestPanel.h"

// Manager
#include "UE5_Training_Project/Manager/DNQuestManager.h"

//
//	퀘스트 타입에 따라 퀘스트 아이콘이 바뀌어야합니다.
//	추후에 데이터 테이블로 퀘스트 타이틀과 서브타이틀을 연결할 예정입니다.
//  우선은 다른 작업때문에 기능 구현이 없으므로 코드로서 작동되는 것은 없습니다.
//

void UDNQuestPanel::NativeConstruct()
{

	set_panel_type(E_UI_PANEL_TYPE::UPT_QUEST);
	Super::NativeConstruct();

	QUEST_MANAGER->set_ui();			//이거 내부 식이 너무 비효율적인듯.. 바꾸던가해야지
}


void UDNQuestPanel::NativeDestruct()
{
	Super::NativeDestruct();

}


void UDNQuestPanel::add_event()
{
	Super::add_event();

}


void UDNQuestPanel::remove_event()
{

	Super::remove_event();
}


void UDNQuestPanel::set_quest_main_title(FText text_in)
{
	if (IsValid(umg_main_quest_title_text))
		umg_main_quest_title_text->SetText(text_in);
}


void UDNQuestPanel::set_quest_sub_title(FText text_in)
{
	if (IsValid(umg_sub_quest_title_text))
		umg_sub_quest_title_text->SetText(text_in);
}


void UDNQuestPanel::set_quest_icon(FString path_in)
{
	if (IsValid(umg_quest_icon))
	{
		UTexture2D* texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *path_in));
		umg_quest_icon->SetBrushFromTexture(texture);
	}
}

void UDNQuestPanel::set_quest_complete_icon(bool flag_in)
{
	if (false == IsValid(umg_quest_complete_icon) || false == IsValid(umg_quest_bg))
		return;

	if (flag_in)
	{
		umg_quest_bg->SetVisibility(ESlateVisibility::HitTestInvisible);
		umg_quest_complete_icon->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		umg_quest_bg->SetVisibility(ESlateVisibility::Collapsed);
		umg_quest_complete_icon->SetVisibility(ESlateVisibility::Collapsed);
	}


	

}

void UDNQuestPanel::set_visible_item_count(bool flag_in)
{
	if (false == IsValid(umg_current_item_count_text) || false == IsValid(umg_max_item_count_text))
		return;

	if (flag_in)
	{
		umg_current_item_count_text->SetVisibility(ESlateVisibility::HitTestInvisible);
		umg_max_item_count_text->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		umg_current_item_count_text->SetVisibility(ESlateVisibility::Collapsed);
		umg_max_item_count_text->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UDNQuestPanel::set_quest_current_item_count(int64 count_in)
{
	if (IsValid(umg_current_item_count_text))
	{
		FString string = FString::FromInt(count_in);
		umg_current_item_count_text->SetText(FText::FromString(string));
	}
}


void UDNQuestPanel::set_quest_need_item_count(int64 count_in)
{
	if (IsValid(umg_max_item_count_text))
	{
		FString string = FString::FromInt(count_in);
			umg_max_item_count_text->SetText(FText::FromString(string));
	}
}

