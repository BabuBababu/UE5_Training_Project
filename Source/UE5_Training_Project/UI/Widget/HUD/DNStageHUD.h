

#pragma once

#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBaseHUD.h"

// Generated
#include "DNStageHUD.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNStageHUD : public ADNBaseHUD
{
	GENERATED_BODY()

protected:
	void NativeConstruct();
	void NativeDestruct();
	void BeginPlay() override;
};
