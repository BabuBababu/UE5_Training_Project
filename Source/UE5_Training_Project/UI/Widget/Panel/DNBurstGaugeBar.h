﻿

#pragma once


// Engine
#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNBurstGaugeBar.generated.h"

/**
 * 
 */


class UImage;
class UProgressBar;


UCLASS()
class UE5_TRAINING_PROJECT_API UDNBurstGaugeBar : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY()
		TObjectPtr<UImage> umg_image_background;

	UPROPERTY()
		TObjectPtr<UProgressBar> umg_main_progress;

private:
	E_UI_GAUGE_TYPE	_gauge_type = E_UI_GAUGE_TYPE::UGT_NONE;

	float	_current_value = 0;
	float	_max_value = 0;
	float	_percent_value = 0.0f;

	bool	_is_enable = true;
	bool	_is_visible = true;


	ADNCommonCharacter* _my_character = nullptr;
	bool	_has_buff = false;

private:
	void	check_gauge();

public:
	void	set_gauge_type(E_UI_GAUGE_TYPE gauge_type_in) { _gauge_type = gauge_type_in; };
	void	set_gauge(float current_value_in, float max_value_in);

	void	set_has_buff(bool has_buff_in) { _has_buff = has_buff_in; };
	void	set_gauge_enable(bool is_enable_in);
	void	set_gauge_visibility(bool is_visibility_in);
};