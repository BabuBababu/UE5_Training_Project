

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBaseWidget.h"

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Data
#include "UE5_Training_Project/Data/DNCharacterData.h"

// Generated
#include "DNSquadSlot.generated.h"

/**
 * 
 */

class UDNSquadGaugeBar;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNSquadSlot : public UDNBaseWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;
	void NativeDestruct() override;
	void add_event() override;
	void remove_event() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

private:
	UPROPERTY()
	TObjectPtr<UOverlay> umg_main_overlay;

	UPROPERTY()
	TObjectPtr<USizeBox> umg_size_box;

	UPROPERTY()
	TObjectPtr<UImage> umg_image;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_name_text;

	UPROPERTY()
	TObjectPtr<UDNSquadGaugeBar> umg_hp_bar;

	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* umg_damaged_animation;
	
	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* umg_change_animation;

private:
	float _current_hp = 0.0f;
	float _max_hp = 0.0f;

public:

	void init_data(int64 squad_index_in, FDNCharacterData* data_in);

	void sync_gauge();
	void set_hp(float current_hp_in, float max_hp_in);
	void play_damaged_animation();
	void change_position_animation();
	void stop_animation();
};
