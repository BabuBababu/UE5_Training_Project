

#pragma once

// Engine
#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>

// Generated
#include "DNBaseLayer.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API UDNBaseLayer : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct();
	virtual void NativeDestruct();

};
