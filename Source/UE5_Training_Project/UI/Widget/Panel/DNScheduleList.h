

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBaseWidget.h"

// Data
#include "UE5_Training_Project/Data/DNCharacterData.h"

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNScheduleList.generated.h"

/**
 * 
 */


class UDNScheduleCharacterButton;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNScheduleList : public UDNBaseWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;
	void NativeDestruct() override;
	void add_event() override;
	void remove_event() override;

public:
	void play_clicked_animation();
	void stop_animation();

private:
	UPROPERTY()
	TObjectPtr<UDNScheduleCharacterButton>	umg_guard_character_button_1;

	UPROPERTY()
	TObjectPtr<UDNScheduleCharacterButton>	umg_guard_character_button_2;

	UPROPERTY()
	TObjectPtr<UDNScheduleCharacterButton>	umg_patrol_character_button_1;

	UPROPERTY()
	TObjectPtr<UDNScheduleCharacterButton>	umg_patrol_character_button_2;

	UPROPERTY()
	TObjectPtr<UDNScheduleCharacterButton>	umg_post_character_button_1;


	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* umg_click_animation;

public:
	FDNCharacterData _send_character_data;

	TArray<TObjectPtr<UDNScheduleCharacterButton>> _character_button_array;
public:
	UFUNCTION()
	void play_click_animation_handler();

	UFUNCTION()
	void stop_click_animation_handler(UDNScheduleCharacterButton* button_in);

	UFUNCTION()
	void store_data_handler(FDNCharacterData data_in);

};
