

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBaseLayer.h"

// Generated
#include "DNLobbyLayer.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API UDNLobbyLayer : public UDNBaseLayer
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};
