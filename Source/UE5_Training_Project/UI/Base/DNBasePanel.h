

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBaseWidget.h"

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"


// Generated
#include "DNBasePanel.generated.h"

/**
 * 
 */

UCLASS()
class UE5_TRAINING_PROJECT_API UDNBasePanel : public UDNBaseWidget
{
	GENERATED_BODY()
	
//////////////////////////////////////////////////////////////////////////
// override
//////////////////////////////////////////////////////////////////////////
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

//////////////////////////////////////////////////////////////////////////
// base
//////////////////////////////////////////////////////////////////////////
protected:
	E_UI_PANEL_TYPE	panel_type = E_UI_PANEL_TYPE::UPT_NONE;

public:
	virtual void update_panel();



//////////////////////////////////////////////////////////////////////////
// getter setter
//////////////////////////////////////////////////////////////////////////
public:
	const E_UI_PANEL_TYPE get_panel_type() const { return panel_type; };
	void set_panel_type(E_UI_PANEL_TYPE panel_type_in) { panel_type = panel_type_in; };
};
