

#pragma once

// Engine
#include <UMG.h>
#include <Blueprint/UserWidget.h>

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNBaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API UDNBaseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct();
	virtual void NativeDestuct();

	virtual void add_event();
	virtual void remove_event();

};
