

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBaseComponent.h"

// Generated
#include "DNCommonButton.generated.h"

/**
 * 
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDNButtonEvent, UDNCommonButton*, evented_button);


class UImage;
class UButton;
class UTextBlock;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNCommonButton : public UDNBaseComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<UButton> umg_button;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_text_box;

	UPROPERTY()
	TObjectPtr<UImage> umg_image_icon;



public:
	UPROPERTY()
	E_UI_BUTTON_STATE			_button_state = E_UI_BUTTON_STATE::UBS_NORMAL;

	// text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
	FString						_text = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
	FDNUICommonButtonTextColor	_text_color;

	// icon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
	ESlateVisibility			_icon_visibility = ESlateVisibility::Hidden;


public:
	UPROPERTY()
	FDNButtonEvent	OnClicked;

	UPROPERTY()
	FDNButtonEvent	OnHovered;

	UPROPERTY()
	FDNButtonEvent	OnUnHovered;

	UPROPERTY()
	FDNButtonEvent	OnPressed;

	UPROPERTY()
	FDNButtonEvent	OnReleased;

protected:
	virtual void update_component() override;

	virtual void add_component_event() override;
	virtual void remove_component_event() override;

	virtual void native_component_enabled(bool is_enabled_in) override;

public:
	void set_text(FString text_in);
	void set_text_color(E_UI_BUTTON_STATE state_in);
	void set_icon_visiblilty(ESlateVisibility visiblilty_in);

public:
	// umg
	TObjectPtr<UButton>				get_button() { return umg_button; };
	TObjectPtr<UTextBlock>			get_text_box() { return umg_text_box; };

	const FString					get_text() const { return _text; };
	const TObjectPtr<UImage>		get_icon() const { return umg_image_icon; };



protected:
	UFUNCTION()
	virtual	void on_clicked_handler();

	UFUNCTION()
	virtual void on_pressed_handler();

	UFUNCTION()
	virtual void on_released_handler();

	UFUNCTION()
	virtual void on_hovered_handler();

	UFUNCTION()
	virtual void on_unhovered_handler();
};


