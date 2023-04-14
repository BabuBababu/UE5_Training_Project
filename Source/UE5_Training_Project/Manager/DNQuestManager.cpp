


#include "UE5_Training_Project/Manager/DNQuestManager.h"

// Item
#include "UE5_Training_Project/Actor/Item/DNQuestItem.h"

// Manager
#include "UE5_Training_Project/Manager/DNUIManager.h"
#include "UE5_Training_Project/UI/Manager/DNWidgetManager.h"

// UI
#include "UE5_Training_Project/UI/Widget/Panel/DNQuestPanel.h"


//
//	퀘스트 매니저에서 변수에 설정된 타겟 위치, 타겟 액터, 이런 것들은 월드에서 플레이어가 겪는 각각의 위치, 액터끼리
//  형변환을 통해서 같은 클래스인지 판단하고 같으면 점령완료,사살완료 nullptr이면 해당아님 등을 처리하면 될 것 같습니다.
//


UDNQuestManager::UDNQuestManager()
{ 
	// 퀘스트 데이터 테이블 초기화
	static ConstructorHelpers::FObjectFinder<UDataTable> QuestDataObject(TEXT("/Game/Blueprint/Data/DT_DNQuestData"));
	if (QuestDataObject.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable Succeed!"));
		_quest_datatable = QuestDataObject.Object;
	}

	_target_location = nullptr;
	_target_actor = nullptr;
	_current_item_count = 0; 
	_request_item_count = 0;
}



void UDNQuestManager::initialize()
{
	_manager_type = E_MANAGER_TYPE::MT_QUEST_MANAGER;


	_player = nullptr;

	Super::initialize();
}


void UDNQuestManager::destroy()
{

	Super::destroy();

}



TObjectPtr<UDNQuestManager> UDNQuestManager::get_quest_manager()
{
	TArray<UObject*> object_array;
	GetObjectsOfClass(UDNQuestManager::StaticClass(), object_array);

	if (object_array.Num() > 0)
	{
		return Cast<UDNQuestManager>(object_array[0]);
	}

	return nullptr;
}

void UDNQuestManager::start_quest(int64 quest_uid_in)
{
	stop_quest();
	// 먼저 퀘스트 uid를 받아와 해당 퀘스트 데이터를 저장합니다.
	init_data(quest_uid_in);

	// 저장된 퀘스트 데이터를 매니저에 적용 및 UI에 뿌립니다.
	if (_quest_data->quest_type == E_UI_QUEST_TYPE::UQT_COLLECT)				// 아이템 수집
	{
		_quest_item_class = _quest_data->quest_item;
		_request_item_count = _quest_data->quest_need_item_count;
	}
	else if (_quest_data->quest_type == E_UI_QUEST_TYPE::UQT_KILL)				// 목표 사살
	{
		_target_actor = _quest_data->quest_eliminate_character;
	}
	else if (_quest_data->quest_type == E_UI_QUEST_TYPE::UQT_DEFENCE)			// 거점 방어
	{
		_target_location = _quest_data->quest_location;
	}
	else if (_quest_data->quest_type == E_UI_QUEST_TYPE::UQT_OCCUPATION)		// 거점 점령
	{
		_target_location = _quest_data->quest_location;
	}
	else if (_quest_data->quest_type == E_UI_QUEST_TYPE::UQT_GO)				// 지점 이동
	{
		_target_location = _quest_data->quest_location;
	}

}

void UDNQuestManager::stop_quest()
{
	// 일단 ui만 숨깁니다.
	hide_ui();

}


void UDNQuestManager::init_data(int64 quest_uid_in)
{
	TArray<FDNQuestData*> data_array;
	_quest_datatable->GetAllRows<FDNQuestData>("", data_array);

	for (auto& data : data_array)
	{
		if (data->quest_uid == quest_uid_in)
		{
			_quest_data = data;
		}
	}
}

void UDNQuestManager::set_ui()
{
	if (nullptr == _quest_data)
	{
		hide_ui();
		return;
	}

	auto * widget = WIDGET_MANAGER->get_panel(E_UI_PANEL_TYPE::UPT_QUEST);
	UDNQuestPanel* panel = Cast<UDNQuestPanel>(widget);
	if (nullptr != panel)
	{
		// 화면에 보이기
		panel->SetVisibility(ESlateVisibility::HitTestInvisible);
		// 퀘스트 메인 이름
		panel->set_quest_main_title(FText::FromString(_quest_data->quest_main_name));
		// 퀘스트 서브 이름
		panel->set_quest_sub_title(FText::FromString(_quest_data->quest_sub_name));
		// 퀘스트 아이콘
		panel->set_quest_icon(_quest_data->quest_sub_icon_path);
		// 퀘스트 완료 아이콘 초기화
		panel->set_quest_complete_icon(false);

		// 수집형 퀘스트
		if (_quest_data->quest_type == E_UI_QUEST_TYPE::UQT_COLLECT)
		{
			panel->set_visible_item_count(true);
			panel->set_quest_current_item_count(0);
			panel->set_quest_need_item_count(_quest_data->quest_need_item_count);
		}
		else
		{
			panel->set_visible_item_count(false);
			panel->set_quest_current_item_count(-1);
			panel->set_quest_need_item_count(0);
		}
	}

}

void UDNQuestManager::hide_ui()
{
	auto* widget = WIDGET_MANAGER->get_panel(E_UI_PANEL_TYPE::UPT_QUEST);
	UDNQuestPanel* panel = Cast<UDNQuestPanel>(widget);
	if (nullptr != panel)
	{
		// 숨기기
		panel->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UDNQuestManager::add_item_count()
{
	_current_item_count += 1;

	auto* widget = WIDGET_MANAGER->get_panel(E_UI_PANEL_TYPE::UPT_QUEST);
	UDNQuestPanel* panel = Cast<UDNQuestPanel>(widget);
	if (nullptr != panel)
	{
		panel->set_quest_current_item_count(_current_item_count);
	}
}