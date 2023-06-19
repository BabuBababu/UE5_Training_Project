

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBasePanel.h"

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Data
#include "UE5_Training_Project/Data/DNCharacterData.h"

// Generated
#include "DNEnemyStatusPanel.generated.h"

/**
 * 
 */

class UDNPlayerGaugeBar;
class ADNPlayerCharacter;



UCLASS()
class UE5_TRAINING_PROJECT_API UDNEnemyStatusPanel : public UDNBasePanel
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;
	void NativeDestruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	void add_event() override;
	void remove_event() override;

public:
	void init_data(FDNCharacterData* data_in);
	void sync_status();
	void set_hp(float current_hp_in, float max_hp_in);

	void add_function_handler(ADNPlayerCharacter* player_in);
	void remove_function_handler(ADNPlayerCharacter* player_in);

	void play_damaged_animation(ADNCommonCharacter* damaged_character_in);

private:
	UPROPERTY()
	TObjectPtr<UOverlay> umg_main_overlay;

	UPROPERTY()
	TObjectPtr<UImage> umg_main_image;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_name_text;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_current_hp_text;
	
	UPROPERTY()
	TObjectPtr<UTextBlock> umg_max_hp_text;

	UPROPERTY()
	TObjectPtr<UDNPlayerGaugeBar> umg_main_hp_bar;


	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* umg_damaged_animation;

private:
	TObjectPtr<ADNEnemyCharacter>  _enemy = nullptr;

	float _current_hp = 0.f;
	float _max_hp = 0.f;

public:
	UFUNCTION()
	void init_status_data_handler(ADNEnemyCharacter* enemy_in);

};
