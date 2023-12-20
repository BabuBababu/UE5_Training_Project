

#pragma once

// Engine
#include <CoreMinimal.h>

// UI
#include "UE5_Training_Project/UI/Base/DNBasePanel.h"

// Generated
#include "DNSelectSquadPanel.generated.h"

/**
 * 
 */

class UDNCommonButton;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNSelectSquadPanel : public UDNBasePanel
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	
	UPROPERTY()
	TObjectPtr<UTextBlock> umg_nikke_name_text;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_nikke_detail_text;
	
	UPROPERTY()
	TObjectPtr<UImage> umg_nikke_image;
	
	UPROPERTY()
	TObjectPtr<UTextBlock> umg_nikke_recommend_position_text;

	UPROPERTY()
	TObjectPtr<UDNCommonButton> umg_prev_button;
	
	UPROPERTY()
	TObjectPtr<UDNCommonButton> umg_next_button;
	
	UPROPERTY()
	TObjectPtr<UDNCommonButton> umg_get_in_button;
	
	UPROPERTY()
	TObjectPtr<UDNCommonButton> umg_get_out_button;

	UPROPERTY()
	TObjectPtr<UDNCommonButton> umg_confirm_button;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_selected_count_text;

};
