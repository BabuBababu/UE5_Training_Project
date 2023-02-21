// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5_Training_Project/Manager/DNObjectManager.h"

// Characeter
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"



void UDNObjectManager::initialize()
{
	_manager_type = E_MANAGER_TYPE::MT_OBJECT_MANAGER;
	_location_actor_array.Empty();


	for (int32 Key = 1; Key <= 9; ++Key)
	{
		_in_squad_doll_array.Emplace(Key, nullptr);
	}


	_player = nullptr;
	
	Super::initialize();
}


void UDNObjectManager::destroy()
{

	Super::destroy();

}



TObjectPtr<UDNObjectManager> UDNObjectManager::get_object_manager()
{
	TArray<UObject*> object_array;
	GetObjectsOfClass(UDNObjectManager::StaticClass(), object_array);

	if (object_array.Num() > 0)
	{
		return Cast<UDNObjectManager>(object_array[0]);
	}

	return nullptr;
}

void UDNObjectManager::update_combat_squad_postion(int32 first_in, int32 second_in)
{
	// 스쿼드 인덱스를 바꿔줍니다.

	if ( nullptr == _in_squad_doll_array[first_in]  &&						// 두번째만 인형일 때
		nullptr != _in_squad_doll_array[second_in]  )
	{
		ADNUnEnemyCharacter* temp_character = _in_squad_doll_array[first_in];

		_in_squad_doll_array[first_in] = _in_squad_doll_array[second_in];
		_in_squad_doll_array[first_in]->_squad_index = first_in;

		_in_squad_doll_array[second_in] = temp_character;
	}
	else if (nullptr != _in_squad_doll_array[first_in]&&					// 첫뻔째만 인형일 때
			nullptr == _in_squad_doll_array[second_in])
	{
		ADNUnEnemyCharacter* temp_character = _in_squad_doll_array[first_in];

		_in_squad_doll_array[first_in] = _in_squad_doll_array[second_in];

		_in_squad_doll_array[second_in] = temp_character;
		_in_squad_doll_array[second_in]->_squad_index = second_in;
	}
	else if (nullptr != _in_squad_doll_array[first_in] &&					// 둘다 인형일 때
			nullptr != _in_squad_doll_array[second_in])
	{
		ADNUnEnemyCharacter* temp_character = _in_squad_doll_array[first_in];
		_in_squad_doll_array[first_in] = _in_squad_doll_array[second_in];
		_in_squad_doll_array[first_in]->_squad_index = first_in;		// 서로 요소를 바꿨기에 내부 스쿼드 인덱스도 바꿔줘야함

		_in_squad_doll_array[second_in] = temp_character;
		_in_squad_doll_array[second_in]->_squad_index = second_in;		// 서로 요소를 바꿨기에 내부 스쿼드 인덱스도 바꿔줘야함

	}
	else if (nullptr == _in_squad_doll_array[first_in] &&					// 둘다 인형이 아닐때
			nullptr == _in_squad_doll_array[second_in])
	{
		return;
	}



	

	

}