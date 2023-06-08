

#pragma once

#include "CoreMinimal.h"
#include "UE5_Training_Project/Character/DNCommonBossCharacter.h"
#include "DNRaptureCubeCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNRaptureCubeCharacter : public ADNCommonBossCharacter
{
	GENERATED_BODY()
	
public:
	ADNRaptureCubeCharacter();

protected:
	void BeginPlay() override;

public:
	void init_base() override;
	void rotate_head(float deleta_time_in, ADNCommonCharacter* target_in) override;
};
