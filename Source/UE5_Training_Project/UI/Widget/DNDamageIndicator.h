

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBaseWidget.h"

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNDamageIndicator.generated.h"

/**
 * 
 */

class ADNCommonCharacter;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNDamageIndicator : public UDNBaseWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;


private:
	UPROPERTY()
	TObjectPtr<UTextBlock> umg_damage_text;

	UPROPERTY()
	TObjectPtr<UImage> umg_damage_image;

	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* umg_show_damage_normal;

	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* umg_show_damage_weak;

	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* umg_show_damage_critical;

	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* umg_show_damage_resist;

private:
	void play_animation(E_DAMAGE_TYPE type_in);

public:
	UFUNCTION()
	void add_function_handler(ADNCommonCharacter* character_in);

	UFUNCTION()
	void remove_function_handler(ADNCommonCharacter* character_in);

	UFUNCTION()
	void show_indicator_handler(float damage_in, E_DAMAGE_TYPE type_in);

};
