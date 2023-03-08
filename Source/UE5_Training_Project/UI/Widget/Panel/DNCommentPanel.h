

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
#include "DNCommentPanel.generated.h"

/**
 * 
 */

class UOverlay;
class UImage;
class UTextBlock;
class UDataTable;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNCommentPanel : public UDNBasePanel
{
	GENERATED_BODY()
public:
	UDNCommentPanel(const FObjectInitializer& ObjectInitializer);


	void clear_panel();
	void play_comment_isac(int64 comment_id_in);	// 부관 코멘트
	void play_comment_character(int64 id_in, int64 comment_id_in);
	void init_data(int64 id_in, int64 comment_id_in);
	void set_image_comment_character(int64 comment_id_in);
	void set_image_comment_isac(int64 comment_id_in);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void add_event() override;
	void remove_event() override;

private:
	UPROPERTY()
	TObjectPtr<UOverlay> umg_main_overlay;

	UPROPERTY()
	TObjectPtr<UImage> umg_face_image;

	UPROPERTY()
	TObjectPtr<UImage> umg_logo_image;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_comment_text;

	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* umg_show_comment_animation;


public:
	UDataTable* _character_datatable;
	FDNCharacterData* _chartacter_data;

	UDataTable* _dialog_datatable;
	FDNCharacterDialogData* _dialog_data;
};
