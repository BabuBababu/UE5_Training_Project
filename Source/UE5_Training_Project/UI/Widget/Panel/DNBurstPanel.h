

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
#include "DNBurstPanel.generated.h"

/**
 * 
 */

class UDNBurstGaugeBar;
class ADNPlayerCharacter;


UCLASS()
class UE5_TRAINING_PROJECT_API UDNBurstPanel : public UDNBasePanel
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;
	void NativeDestruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	void add_event() override;
	void remove_event() override;

public:
	void sync_status();
	void set_burst(float current_burst_in, float max_burst_in);

	void add_function_handler(ADNPlayerCharacter* player_in);
	void remove_function_handler(ADNPlayerCharacter* player_in);

	void play_full_animation();

private:
	UPROPERTY()
		TObjectPtr<UOverlay> umg_main_overlay;

	UPROPERTY()
		TObjectPtr<UImage> umg_main_image;

	UPROPERTY()
		TObjectPtr<UTextBlock> umg_name_text;

	UPROPERTY()
		TObjectPtr<UDNBurstGaugeBar> umg_main_burst_bar;


	UPROPERTY(Meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* umg_full_animation;

private:
	TObjectPtr<ADNEnemyCharacter>  _enemy = nullptr;

	float _current_burst = 0.f;
	float _max_burst = 0.f;

};
