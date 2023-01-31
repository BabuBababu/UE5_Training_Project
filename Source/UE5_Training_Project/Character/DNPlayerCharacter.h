

#pragma once

// Engine
#include <CoreMinimal.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Generated
#include "DNPlayerCharacter.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnArmDelegate, bool, armed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCrouchDelegate, bool, crouch);

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNPlayerCharacter : public ADNCommonCharacter
{
	GENERATED_BODY()
	
protected:
	void BeginPlay() override;

public:
	void fire() override;
	void armed() override;
	void crouch() override;

public:
	void start_fire();

public:
	FOnArmDelegate on_armed;
	FOnCrouchDelegate on_crouch;

public:
	UFUNCTION()
	void player_arm_event(bool armed_in);

	UFUNCTION()
	void player_crouch_event(bool crouch_in);
};
