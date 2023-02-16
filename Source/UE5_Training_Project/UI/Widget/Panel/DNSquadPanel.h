

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBasePanel.h"

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNSquadPanel.generated.h"

/**
 * 
 */

class UDNSquadSlot;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNSquadPanel : public UDNBasePanel
{
	GENERATED_BODY()


protected:
	void NativeConstruct() override;
	void NativeDestruct() override;

	void add_event() override;
	void remove_event() override;

private:
	UPROPERTY()
	TObjectPtr<UUniformGridPanel> umg_uniform_grid_panel;

	UPROPERTY()
	TObjectPtr<UDNSquadSlot> umg_slot_1;

	UPROPERTY()
	TObjectPtr<UDNSquadSlot> umg_slot_2;

	UPROPERTY()
	TObjectPtr<UDNSquadSlot> umg_slot_3;

	UPROPERTY()
	TObjectPtr<UDNSquadSlot> umg_slot_4;

	UPROPERTY()
	TObjectPtr<UDNSquadSlot> umg_slot_6;

	UPROPERTY()
	TObjectPtr<UDNSquadSlot> umg_slot_7;

	UPROPERTY()
	TObjectPtr<UDNSquadSlot> umg_slot_8;

	UPROPERTY()
	TObjectPtr<UDNSquadSlot> umg_slot_9;


private:
	TArray<UDNSquadSlot*>	_slot_array;
private:
	void init_panel();


public:
	UFUNCTION()
	void play_damaged_animation_handler(int64 squad_index_in);
};
