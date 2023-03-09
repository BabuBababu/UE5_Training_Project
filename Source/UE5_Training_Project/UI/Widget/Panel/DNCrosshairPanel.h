

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBasePanel.h"

// Generated
#include "DNCrosshairPanel.generated.h"

/**
 * 
 */

UCLASS()
class UE5_TRAINING_PROJECT_API UDNCrosshairPanel : public UDNBasePanel
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void add_event() override;
	void remove_event() override;

private:
	UPROPERTY()
	TObjectPtr<UOverlay> umg_main_overlay;

	UPROPERTY()
	TObjectPtr<UImage> umg_crosshair_image;

	UPROPERTY()
	TObjectPtr<UOverlay> umg_sub_crosshair_image;

	UPROPERTY()
	TObjectPtr<UOverlay> umg_blood_screen_image;



	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* umg_hit_animation;

	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* umg_critical_hit_animation;

	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* umg_damaged_animation;

public:
	void play_hit_animation();
	void play_critical_hit_animation();
	void play_damaged_animation();
};
