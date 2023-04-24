

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBasePanel.h"

// Generated
#include "DNQuestPanel.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API UDNQuestPanel : public UDNBasePanel
{
	GENERATED_BODY()
	

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void add_event() override;
	void remove_event() override;

public:
	void set_quest_main_title(FText text_in);
	void set_quest_sub_title(FText text_in);
	void set_quest_icon(FString path_in);
	void set_quest_complete_icon(bool flag_in);
	void set_quest_current_count(int64 count_in);
	void set_quest_need_count(int64 count_in);

	void set_visible_item_count(bool flag_in);

private:
	UPROPERTY()
	TObjectPtr<UCanvasPanel> umg_main_panel;

	UPROPERTY()
	TObjectPtr<UImage> umg_quest_bg;

	UPROPERTY()
	TObjectPtr<UImage> umg_quest_icon;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_main_quest_title_text;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_sub_quest_title_text;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_current_item_count_text;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_max_item_count_text;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_slash;

	UPROPERTY()
	TObjectPtr<UImage> umg_quest_complete_icon;

public:
	E_UI_QUEST_TYPE quest_type = E_UI_QUEST_TYPE::UQT_NONE;



};
