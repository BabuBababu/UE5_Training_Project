

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBasePanel.h"

// Data
#include "UE5_Training_Project/Data/DNCharacterData.h"

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNPortraitPanel.generated.h"

/**
 * 
 */

class UOverlay;
class UImage;
class UDataTable;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNPortraitPanel : public UDNBasePanel
{
	GENERATED_BODY()
public:
	UDNPortraitPanel(const FObjectInitializer& ObjectInitializer);
	
	void clear_panel();
	void play_portrait_panel(int64 id_in, bool is_dead_in);
	void init_data(int64 id_in);
	void set_image();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void add_event() override;
	void remove_event() override;

private:
	UPROPERTY()
	TObjectPtr<UOverlay>	umg_main_overlay;

	UPROPERTY()
	TObjectPtr<UImage>		umg_normal_image;

	UPROPERTY()
	TObjectPtr<UImage>		umg_die_image;

	UPROPERTY()
	TObjectPtr<UImage>		umg_skill_cut_image;


	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* umg_main_image_animation;

	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* umg_die_image_animation;

	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* umg_skill_image_animation;

public:
	UDataTable* _character_datatable;
	FDNCharacterData* _chartacter_data;
};
