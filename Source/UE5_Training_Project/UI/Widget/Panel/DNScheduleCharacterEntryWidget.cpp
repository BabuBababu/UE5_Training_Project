


#include "UE5_Training_Project/UI/Widget/Panel/DNScheduleCharacterEntryWidget.h"

// Button
#include "UE5_Training_Project/UI/Component/Button/DNCharacterButton.h"

// Content
#include "UE5_Training_Project/UI/Widget/Panel/DNScheduleWidget.h"
#include "UE5_Training_Project/UI/Widget/Panel/DNScheduleList.h"

// Manager
#include "UE5_Training_Project/UI/Manager/DNWidgetManager.h"

// Character
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"

// Component
#include "UE5_Training_Project/Component/DNStatusComponent.h"


void UDNScheduleCharacterEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UDNStatusComponent* status = Cast<UDNStatusComponent>(ListItemObject);
	if (nullptr != status)
	{

		if (IsValid(umg_character_button))
		{
			umg_character_button->set_data(status->_chartacter_data);
			umg_character_button->init();
		}

		if (IsValid(umg_friendship_text))
		{
			FString rate = FString::FromInt(status->_chartacter_data->character_mental_data.friendship);
			umg_friendship_text->SetText(FText::FromString(rate));
		}

		if (IsValid(umg_morality_text))
		{
			FString rate = FString::FromInt(status->_chartacter_data->character_mental_data.morality);
			umg_morality_text->SetText(FText::FromString(rate));
		}

		if (IsValid(umg_composure_text))
		{
			FString rate = FString::FromInt(status->_chartacter_data->character_mental_data.composure);
			umg_composure_text->SetText(FText::FromString(rate));
		}

		if (IsValid(umg_positiveness_text))
		{
			FString rate = FString::FromInt(status->_chartacter_data->character_mental_data.positiveness);
			umg_positiveness_text->SetText(FText::FromString(rate));
		}




		// 버튼 델리게이트 추가해줍니다.
		UDNBaseContent * content  = WIDGET_MANAGER->get_content(E_UI_CONTENT_TYPE::UCT_WORK);
		if (IsValid(content))
		{
			UDNScheduleWidget* widget = Cast<UDNScheduleWidget>(content);

			if (nullptr != widget)
			{
				if(widget->get_schedule_list())
					umg_character_button->OnClickCharacterDataButton.AddDynamic(widget->get_schedule_list(), &UDNScheduleList::store_data_handler);
			}
		}

	}

}
