


#include "UE5_Training_Project/UI/Widget/Panel/DNSquadPanel.h"

// Panel
#include "UE5_Training_Project/UI/Widget/Panel/DNSquadSlot.h"

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"

// Component
#include "UE5_Training_Project/Component/DNStatusComponent.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"

void UDNSquadPanel::NativeConstruct()
{
	set_panel_type(E_UI_PANEL_TYPE::UPT_SQUAD);
	Super::NativeConstruct();
	_slot_array.Empty();
	init_panel();
}

void UDNSquadPanel::NativeDestruct()
{
	Super::NativeDestruct();
}


void UDNSquadPanel::add_event()
{
	for (auto& doll : OBJECT_MANAGER->_in_squad_doll_array)
	{
		if( nullptr != doll.Value)
			doll.Value->OnDamaged.AddDynamic(this, &UDNSquadPanel::play_damaged_animation_handler);
	}
}


void UDNSquadPanel::remove_event()
{
	for (auto& doll : OBJECT_MANAGER->_in_squad_doll_array)
	{
		if (nullptr != doll.Value)
			doll.Value->OnDamaged.RemoveDynamic(this, &UDNSquadPanel::play_damaged_animation_handler);
	}
}



void UDNSquadPanel::init_panel()
{
	if (IsValid(umg_slot_1))
	{
		for (const auto& doll : OBJECT_MANAGER->_in_squad_doll_array)
		{
			if (nullptr != doll.Value)
			{
				if (doll.Value->_squad_index == 1)
				{
					umg_slot_1->init_data(1, doll.Value->_status->_chartacter_data);
				}
				
			}
			else
			{

				umg_slot_1->init_data(1, nullptr);
			}
		}
		_slot_array.Add(umg_slot_1);
	}
	if (IsValid(umg_slot_2))
	{
		for (const auto& doll : OBJECT_MANAGER->_in_squad_doll_array)
		{
			if (nullptr != doll.Value)
			{
				if (doll.Value->_squad_index == 2)
				{
					umg_slot_2->init_data(2, doll.Value->_status->_chartacter_data);
					
				}
				
			}
			else
			{

				umg_slot_2->init_data(2, nullptr);
				
			}
		}
		_slot_array.Add(umg_slot_2);
	}
	if (IsValid(umg_slot_3))
	{
		for (const auto& doll : OBJECT_MANAGER->_in_squad_doll_array)
		{
			if (nullptr != doll.Value)
			{
				if (doll.Value->_squad_index == 3)
				{
					umg_slot_3->init_data(3, doll.Value->_status->_chartacter_data);
					
				}
				
			}
			else
			{

				umg_slot_3->init_data(3, nullptr);
				
			}
		}
		_slot_array.Add(umg_slot_3);
	}
	if (IsValid(umg_slot_4))
	{
		for (const auto& doll : OBJECT_MANAGER->_in_squad_doll_array)
		{
			if (nullptr != doll.Value)
			{
				if (doll.Value->_squad_index == 4)
				{
					umg_slot_4->init_data(4, doll.Value->_status->_chartacter_data);
					
				}
			}
			else
			{

				umg_slot_4->init_data(4, nullptr);
				
			}
		}
		_slot_array.Add(umg_slot_4);
	}
	if (IsValid(umg_slot_6))
	{
		for (const auto& doll : OBJECT_MANAGER->_in_squad_doll_array)
		{
			if (nullptr != doll.Value)
			{
				if (doll.Value->_squad_index == 6)
				{
					umg_slot_6->init_data(6, doll.Value->_status->_chartacter_data);
					
				}
				
			}
			else
			{

				umg_slot_6->init_data(6, nullptr);
				
			}
		}
		_slot_array.Add(umg_slot_6);
	}
	if (IsValid(umg_slot_7))
	{
		for (const auto& doll : OBJECT_MANAGER->_in_squad_doll_array)
		{
			if (nullptr != doll.Value)
			{
				if (doll.Value->_squad_index == 7)
				{
					umg_slot_7->init_data(7, doll.Value->_status->_chartacter_data);
					
					
				}
				
			}
			else
			{

				umg_slot_7->init_data(7, nullptr);
				
			}
		}
		_slot_array.Add(umg_slot_7);
	}
	if (IsValid(umg_slot_8))
	{
		for (const auto& doll : OBJECT_MANAGER->_in_squad_doll_array)
		{
			if (nullptr != doll.Value)
			{
				if (doll.Value->_squad_index == 8)
				{
					umg_slot_8->init_data(8, doll.Value->_status->_chartacter_data);
					
					
				}
				
			}
			else
			{
				umg_slot_8->init_data(8, nullptr);
				
			}
		}
		_slot_array.Add(umg_slot_8);
	}
	if (IsValid(umg_slot_9))
	{
		for (const auto& doll : OBJECT_MANAGER->_in_squad_doll_array)
		{
			if (nullptr != doll.Value)
			{
				if (doll.Value->_squad_index == 9)
				{
					umg_slot_9->init_data(9, doll.Value->_status->_chartacter_data);
					
					
				}
			}
			else
			{
				umg_slot_9->init_data(9, nullptr);
				
			}
		}
		_slot_array.Add(umg_slot_9);
	}

}


void UDNSquadPanel::update_squad(int64 first_index_in, int64 second_index_in)
{
	UDNSquadSlot* UniformGridSlot_first = nullptr;
	UDNSquadSlot* UniformGridSlot_second = nullptr;




	for (auto slot : _slot_array)
	{
		if (slot->get_widget_index() == first_index_in)
		{
			UniformGridSlot_first = slot;
		}

		if (slot->get_widget_index() == second_index_in)
		{
			UniformGridSlot_second = slot;
		}
	}

	

	UUniformGridSlot* slot_first = Cast<UUniformGridSlot>(UniformGridSlot_first->Slot);
	UUniformGridSlot* slot_second = Cast<UUniformGridSlot>(UniformGridSlot_second->Slot);



	int32 first_row = slot_first->GetRow();
	int32 first_column = slot_first->GetColumn();
	int32 second_row = slot_second->GetRow();
	int32 second_column = slot_second->GetColumn();



	// 위치 및 인덱스도 바꿔줍니다.
	UniformGridSlot_first->set_widget_index(second_index_in);
	UniformGridSlot_second->set_widget_index(first_index_in);

	slot_first->SetRow(second_row);
	slot_first->SetColumn(second_column);
	slot_second->SetRow(first_row);
	slot_second->SetColumn(first_column);




}

void UDNSquadPanel::play_damaged_animation_handler(int64 squad_index_in)
{
	for (const auto& slot : _slot_array)
	{
		if (slot->get_widget_index() == squad_index_in)
			slot->play_damaged_animation();
	}
}