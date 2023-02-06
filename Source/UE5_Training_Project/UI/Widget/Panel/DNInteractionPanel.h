

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBaseWidget.h"

// Generated
#include "DNInteractionPanel.generated.h"

/**
 * 
 */

UCLASS()
class UE5_TRAINING_PROJECT_API UDNInteractionPanel : public UDNBaseWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;


private:
	UPROPERTY()
	TObjectPtr<UCanvasPanel> umg_main_panel;

	UPROPERTY()
	TObjectPtr<UTextBlock> _umg_text;

	UPROPERTY()
	TObjectPtr<UImage> _umg_image;

};
