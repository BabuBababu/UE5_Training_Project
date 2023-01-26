#pragma once


// Engine
#include <CoreMinimal.h>
#include <UObject/NoExportTypes.h>

// Generated
#include "DNCharacterAssetSetting.generated.h"

/**
 * 
 */
UCLASS(config=UE5TrainingProject)
class UE5_TRAINING_PROJECT_SETTING_API UDNCharacterAssetSetting : public UObject
{
	GENERATED_BODY()
	
public:
	UDNCharacterAssetSetting();

	UPROPERTY(config)
	TArray<FSoftObjectPath> _character_assets;


};
