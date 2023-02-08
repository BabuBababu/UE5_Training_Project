

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBaseLayer.h"

// Panel
#include "UE5_Training_Project/UI/Widget/Panel/DNPlayerCombatPanel.h"
#include "UE5_Training_Project/UI/Widget/Panel/DNInteractionPanel.h"



// Generated
#include "DNPanelLayer.generated.h"

/**
 * 
 */

class UImage;
class UDNPlayerCombatPanel;
class UDNInteractionPanel;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNPanelLayer : public UDNBaseLayer
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY()
	TObjectPtr<UImage> umg_crosshair_image;


	UPROPERTY()
	TObjectPtr<UDNPlayerCombatPanel> umg_comabat_panel;

	UPROPERTY()
	TObjectPtr<UDNInteractionPanel> umg_interaction_panel;
};
