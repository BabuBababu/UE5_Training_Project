


#include "UE5_Training_Project/Manager/DNLobbyNPCManager.h"


// Characeter
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"




void UDNLobbyNPCManager::initialize()
{
	_manager_type = E_MANAGER_TYPE::MT_LOBBY_NPC_MANAGER;
	_guard_doll_array.Empty();
	_patrol_doll_array.Empty();
	_post_doll_array.Empty();
	_rest_doll_array.Empty();

	_working_time = 10.f; //테스트용 10초
	_resting_time = 10.f; //테스트용 10초

	Super::initialize();
}


void UDNLobbyNPCManager::destroy()
{

	Super::destroy();

}



TObjectPtr<UDNLobbyNPCManager> UDNLobbyNPCManager::get_lobby_manager()
{
	TArray<UObject*> object_array;
	GetObjectsOfClass(UDNLobbyNPCManager::StaticClass(), object_array);

	if (object_array.Num() > 0)
	{
		return Cast<UDNLobbyNPCManager>(object_array[0]);
	}

	return nullptr;
}


// 반드시 처음 초기화할 때만 사용합니다.
void UDNLobbyNPCManager::set_on_rest(ADNUnEnemyCharacter* doll_in)
{

	_rest_doll_array.Emplace(doll_in->_character_id, doll_in);
}


void UDNLobbyNPCManager::set_on_guard(ADNUnEnemyCharacter* doll_in)
{
	// 행여나 있을 버그 체크
	if (false == _rest_doll_array.IsEmpty())
		return;

	// 입초 근무에 추가
	_guard_doll_array.Emplace(doll_in->_character_id, doll_in);

	// 미배정에서 제거
	for (auto& doll : _rest_doll_array)
	{
		if (doll.Value == doll_in)
			_rest_doll_array.Remove(doll.Key);
	}
}

void UDNLobbyNPCManager::set_on_patrol(ADNUnEnemyCharacter* doll_in)
{
	if (false == _rest_doll_array.IsEmpty())
		return;

	// 순찰 근무에 추가
	_patrol_doll_array.Emplace(doll_in->_character_id, doll_in);

	// 미배정에서 제거
	for (auto& doll : _rest_doll_array)
	{
		if (doll.Value == doll_in)
			_rest_doll_array.Remove(doll.Key);
	}
}

void UDNLobbyNPCManager::set_on_post(ADNUnEnemyCharacter* doll_in)
{
	if (false == _rest_doll_array.IsEmpty())
		return;

	// 당직 근무에 추가
	_post_doll_array.Emplace(doll_in->_character_id, doll_in);

	// 미배정에서 제거
	for (auto& doll : _rest_doll_array)
	{
		if (doll.Value == doll_in)
			_rest_doll_array.Remove(doll.Key);
	}
}

void UDNLobbyNPCManager::set_off_guard(ADNUnEnemyCharacter* doll_in)
{
	if (false == _guard_doll_array.IsEmpty())
		return;

	_rest_doll_array.Emplace(doll_in->_character_id,doll_in);

	// 입초근무에서 제거
	for (auto& doll : _guard_doll_array)
	{
		if (doll.Value == doll_in)
			_guard_doll_array.Remove(doll.Key);
	}
}

void UDNLobbyNPCManager::set_off_patrol(ADNUnEnemyCharacter* doll_in)
{
	if (false == _patrol_doll_array.IsEmpty())
		return;

	_rest_doll_array.Emplace(doll_in->_character_id, doll_in);

	// 순찰근무에서 제거
	for (auto& doll : _patrol_doll_array)
	{
		if (doll.Value == doll_in)
			_patrol_doll_array.Remove(doll.Key);
	}
}

void UDNLobbyNPCManager::set_off_post(ADNUnEnemyCharacter* doll_in)
{
	if (false == _post_doll_array.IsEmpty())
		return;

	_rest_doll_array.Emplace(doll_in->_character_id, doll_in);

	// 당직근무에서 제거
	for (auto& doll : _post_doll_array)
	{
		if (doll.Value == doll_in)
			_post_doll_array.Remove(doll.Key);
	}
}

void UDNLobbyNPCManager::hide_weapon(ADNUnEnemyCharacter* doll_in)
{
	doll_in->change_armed_state_handler(false);
}

void UDNLobbyNPCManager::show_weapon(ADNUnEnemyCharacter* doll_in)
{
	doll_in->change_armed_state_handler(true);
}
