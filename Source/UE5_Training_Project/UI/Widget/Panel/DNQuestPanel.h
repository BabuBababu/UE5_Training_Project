

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

public:
	E_UI_QUEST_TYPE quest_type = E_UI_QUEST_TYPE::UQT_NONE;

};
