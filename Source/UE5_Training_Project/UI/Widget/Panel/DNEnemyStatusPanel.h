

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
	void sync_gauge();
	void set_hp(float current_hp_in, float max_hp_in);

	void play_damaged_animation();

private:
	UPROPERTY()
	TObjectPtr<UOverlay> umg_main_overlay;

	UPROPERTY()
	TObjectPtr<UImage> umg_main_image;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_name_text;

	UPROPERTY()
	TObjectPtr<UDNPlayerGaugeBar> umg_main_hp_bar;


	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* umg_damaged_animation;

};
