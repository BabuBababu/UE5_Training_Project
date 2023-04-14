


#include "UE5_Training_Project/Manager/DNLobbyNPCManager.h"

// Engine
#include <BehaviorTree/BlackboardComponent.h>

// Actor
#include "UE5_Training_Project/Actor/DNGuardPointActor.h"

// Characeter
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"

// Controller
#include "UE5_Training_Project/Controller/DNLobbyAIController.h"

// BlackBoard
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"



void UDNLobbyNPCManager::initialize()
{
	_manager_type = E_MANAGER_TYPE::MT_LOBBY_NPC_MANAGER;
	_guard_doll_array.Empty();
	_patrol_doll_array.Empty();
	_post_doll_array.Empty();
	_rest_doll_array.Empty();

	_working_time = 60.f; //테스트용 60초
	_resting_time = 30.f; //테스트용 30초



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

void UDNLobbyNPCManager::initialize_ai_controller()
{
	_guard_ai_controller_array.Empty();
	_patrol_ai_controller_array.Empty();
	_post_ai_controller_array.Empty();

	for (int64 key = 0; key < 2; ++key)
	{
		ADNLobbyAIController* _guard_ai_controller = GetWorld()->SpawnActor<ADNLobbyAIController>(ADNLobbyAIController::StaticClass());

		if (nullptr != _guard_ai_controller)
			_guard_ai_controller->_ai_type = E_LOBBY_AI_TYPE::LAT_GUARD;

		_guard_ai_controller_array.Add(key, _guard_ai_controller);
	}

	for (int64 key = 0; key < 2; ++key)
	{
		ADNLobbyAIController* _patrol_ai_controller = GetWorld()->SpawnActor<ADNLobbyAIController>(ADNLobbyAIController::StaticClass());

		if (nullptr != _patrol_ai_controller)
			_patrol_ai_controller->_ai_type = E_LOBBY_AI_TYPE::LAT_PATROL;

		_patrol_ai_controller_array.Add(key, _patrol_ai_controller);
	}

	ADNLobbyAIController* _post_ai_controller = GetWorld()->SpawnActor<ADNLobbyAIController>(ADNLobbyAIController::StaticClass());

	if (nullptr != _post_ai_controller)
		_post_ai_controller->_ai_type = E_LOBBY_AI_TYPE::LAT_POST;
	_post_ai_controller_array.Add(0, _post_ai_controller);
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
	doll_in->_lobby_ai_type = E_LOBBY_AI_TYPE::LAT_GUARD;

	// 미배정에서 제거
	for (auto& doll : _rest_doll_array)
	{
		if (doll.Value == doll_in)
			_rest_doll_array.Remove(doll.Key);
	}
	// 당직 근무에서 제거
	for (auto& doll : _post_doll_array)
	{
		if (doll.Value == doll_in)
			_post_doll_array.Remove(doll.Key);
	}
	// 순찰 근무에서 제거
	for (auto& doll : _patrol_doll_array)
	{
		if (doll.Value == doll_in)
			_patrol_doll_array.Remove(doll.Key);
	}
}

void UDNLobbyNPCManager::set_on_patrol(ADNUnEnemyCharacter* doll_in)
{
	if (false == _rest_doll_array.IsEmpty())
		return;

	// 순찰 근무에 추가
	_patrol_doll_array.Emplace(doll_in->_character_id, doll_in);
	doll_in->_lobby_ai_type = E_LOBBY_AI_TYPE::LAT_PATROL;

	// 미배정에서 제거
	for (auto& doll : _rest_doll_array)
	{
		if (doll.Value == doll_in)
			_rest_doll_array.Remove(doll.Key);
	}

	// 당직 근무에서 제거
	for (auto& doll : _post_doll_array)
	{
		if (doll.Value == doll_in)
			_post_doll_array.Remove(doll.Key);
	}
	// 입초 근무에서 제거
	for (auto& doll : _guard_doll_array)
	{
		if (doll.Value == doll_in)
			_guard_doll_array.Remove(doll.Key);
	}
}

void UDNLobbyNPCManager::set_on_post(ADNUnEnemyCharacter* doll_in)
{
	if (false == _rest_doll_array.IsEmpty())
		return;

	// 당직 근무에 추가
	_post_doll_array.Emplace(doll_in->_character_id, doll_in);
	doll_in->_lobby_ai_type = E_LOBBY_AI_TYPE::LAT_POST;

	// 미배정에서 제거
	for (auto& doll : _rest_doll_array)
	{
		if (doll.Value == doll_in)
			_rest_doll_array.Remove(doll.Key);
	}
	// 순찰 근무에서 제거
	for (auto& doll : _patrol_doll_array)
	{
		if (doll.Value == doll_in)
			_patrol_doll_array.Remove(doll.Key);
	}
	// 입초 근무에서 제거
	for (auto& doll : _guard_doll_array)
	{
		if (doll.Value == doll_in)
			_guard_doll_array.Remove(doll.Key);
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

	doll_in->bUseControllerRotationYaw = false;
	doll_in->_weapon_armed->SetVisibility(false);
	doll_in->_weapon_un_armed->SetVisibility(true);
	doll_in->_is_armed_weapon = false;
	doll_in->_pre_upper_character_state = doll_in->_character_state;
	doll_in->_character_state = doll_in->_character_origin_state;
}

void UDNLobbyNPCManager::show_weapon(ADNUnEnemyCharacter* doll_in)
{
	doll_in->bUseControllerRotationYaw = true;
	doll_in->_weapon_armed->SetVisibility(true);
	doll_in->_weapon_un_armed->SetVisibility(false);
	doll_in->_is_armed_weapon = true;
	doll_in->_pre_upper_character_state = doll_in->_character_state;
	doll_in->_character_state = doll_in->_character_origin_state;
}


void UDNLobbyNPCManager::apply_work()
{
	// 적용을 위해 모든 배열에서 컨트롤러를 해제합니다.
	for (auto& doll : _guard_doll_array)
	{
		doll.Value->GetController()->UnPossess();
	}

	for (auto& doll : _patrol_doll_array)
	{
		doll.Value->GetController()->UnPossess();
	}

	for (auto& doll : _post_doll_array)
	{
		doll.Value->GetController()->UnPossess();
	}

	for (auto& doll : _rest_doll_array)
	{
		doll.Value->GetController()->UnPossess();
	}


	// 새롭게 장착할 컨트롤러를 생성합니다.
	initialize_ai_controller();

	// 입초
	for (auto& doll : _guard_doll_array)
	{
		for (auto& controller : _guard_ai_controller_array)
		{
			if (nullptr == controller.Value->GetPawn() && nullptr == doll.Value->GetController())
			{
				controller.Value->Possess(doll.Value);

				for (auto& actor : OBJECT_MANAGER->_guard_location_actor_array)
				{
					if (actor.Key == controller.Key)	//가드 로케이션의 키 : 0~1 (_index로 에디터에서 설정), 컨트롤러의 키 : 0~1
					{
						controller.Value->get_blackboard()->SetValueAsVector(all_ai_bb_keys::guard_location, actor.Value->GetActorLocation());	
					}
						
				}

				
			}
		}
		// 무장 및 역할에 맞는 애니메이션 상태로 전환합니다.

		doll.Value->_is_armed_weapon = false;
		doll.Value->armed();
		doll.Value->_character_state = E_CHARACTER_STATE::CS_GUARD;
	}

	// 순찰
	for (auto& doll : _patrol_doll_array)
	{
		for (auto& controller : _patrol_ai_controller_array)
		{
			if (nullptr == controller.Value->GetPawn() && nullptr == doll.Value->GetController())
			{
				controller.Value->Possess(doll.Value);
			}
		}

		doll.Value->_is_armed_weapon = false;
		doll.Value->armed();
		doll.Value->_character_state = E_CHARACTER_STATE::CS_PATROL;
	}

	// 당직
	for (auto& doll : _post_doll_array)
	{
		for (auto& controller : _post_ai_controller_array)
		{
			if (nullptr == controller.Value->GetPawn() && nullptr == doll.Value->GetController())
			{
				controller.Value->Possess(doll.Value);
			}
		}

		doll.Value->_is_armed_weapon = false;
		doll.Value->armed();
		doll.Value->_character_state = E_CHARACTER_STATE::CS_POST;
	}


	

}