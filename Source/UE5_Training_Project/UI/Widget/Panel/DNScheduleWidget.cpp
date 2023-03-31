


#include "UE5_Training_Project/UI/Widget/Panel/DNScheduleWidget.h"

// Character
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Component
#include "UE5_Training_Project/Component/DNStatusComponent.h"

// Panel
#include "UE5_Training_Project/UI/Widget/Panel/DNScheduleList.h"
#include "UE5_Training_Project/UI/Widget/Panel/DNScheduleCharacterEntryWidget.h"

// Button
#include "UE5_Training_Project/UI/Component/Button/DNScheduleCharacterButton.h"
#include "UE5_Training_Project/UI/Component/Button/DNCharacterButton.h"


// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"


/////////////   리스트 뷰 작동 원리   /////////////////
// umg에디터에서 리스트 뷰 위젯의 entry class를 설정해두면
// 따로 createwidget을 하지않아도 entry class로 설정해둔 그 클래스의 NativeOnListItemObjectSet메서드로
// 하단의 umg_character_list_view->AddItem를 호출해서 집어넣을 때 데이터를 초기화할 수 있고
// 위젯도 생성할 수 있습니다.
//////////////////////////////////////////////////////

void UDNScheduleWidget::NativeConstruct()
{

	set_content_type(E_UI_CONTENT_TYPE::UCT_WORK);

	if (IsValid(umg_character_list_view))
	{

		for (auto& actor : OBJECT_MANAGER->_griffin_player_array)
		{
			ADNCommonCharacter* character = Cast<ADNCommonCharacter>(actor);
			if (nullptr != character)
			{
				if (character->get_character_type() == E_CHARACTER_TYPE::CT_GRIFFIN)			//인형들만 다 집어넣습니다.
				{
					umg_character_list_view->AddItem(character->_status);
				}
			}
			
		}
	}


	Super::NativeConstruct();

	

}

void UDNScheduleWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UDNScheduleWidget::add_event()
{
	Super::add_event();

}

void UDNScheduleWidget::remove_event()
{
	Super::remove_event();
}