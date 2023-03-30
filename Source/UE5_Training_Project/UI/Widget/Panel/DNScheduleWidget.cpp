


#include "UE5_Training_Project/UI/Widget/Panel/DNScheduleWidget.h"

// Engine
//#include <Components/ListView.h>

// Character
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"

// Component
#include "UE5_Training_Project/Component/DNStatusComponent.h"

// Panel
#include "UE5_Training_Project/UI/Widget/Panel/DNScheduleList.h"
#include "UE5_Training_Project/UI/Widget/Panel/DNScheduleCharacterEntryWidget.h"

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
	Super::NativeConstruct();

	if (IsValid(umg_character_list_view))
	{

		for (auto& doll : OBJECT_MANAGER->_in_squad_doll_array)
		{
			if(nullptr != doll.Value)
				umg_character_list_view->AddItem(doll.Value->_status);
		}
	}
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