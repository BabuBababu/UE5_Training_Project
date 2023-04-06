


#include "UE5_Training_Project/Manager/DNQuestManager.h"

// Item
#include "UE5_Training_Project/Actor/Item/DNQuestItem.h"


UDNQuestManager::UDNQuestManager()
{
	static ConstructorHelpers::FClassFinder<ADNQuestItem> ActorClassFinder(TEXT("/Game/Blueprint/Item/DNQuestItem_1.DNQuestItem_1_C"));
	rally_point_level_quest_item_class = ActorClassFinder.Class;
}



void UDNQuestManager::initialize()
{
	_manager_type = E_MANAGER_TYPE::MT_QUEST_MANAGER;

	_quest_item_array.Empty();


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
