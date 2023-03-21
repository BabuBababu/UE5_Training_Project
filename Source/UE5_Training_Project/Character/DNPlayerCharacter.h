

#pragma once

// Engine
#include <CoreMinimal.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Generated
#include "DNPlayerCharacter.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnArmDelegate, bool, armed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCrouchDelegate, bool, crouch);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSprintDelegate, bool, sprint);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnOrderMoveDelegate, FVector, destination, ADNUnEnemyCharacter*, doll);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnOrderAttackDelegate, ADNEnemyCharacter*, enemy, ADNUnEnemyCharacter*, doll);


/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNPlayerCharacter : public ADNCommonCharacter
{
	GENERATED_BODY()
	
protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

public:
	void fire() override;
	void armed() override;
	void crouch() override;
	void reload() override;
	void aiming() override;
	void stop_aiming() override;
	void sprint() override;
	void stop_sprint() override;
	void cover() override;
	void wall_jump();

public:
	void start_fire();

	void init_ui_event() override;
	void remove_ui_event() override;

	void order_move(FVector destination_in, ADNUnEnemyCharacter* doll_in);
	void order_attack(ADNEnemyCharacter* enemy_in, ADNUnEnemyCharacter* doll_in);

private:
	FTransform set_camera_transform(bool flag_in);

public:
	FOnArmDelegate on_armed;
	FOnCrouchDelegate on_crouch;
	FOnSprintDelegate on_sprint;


	FOnOrderMoveDelegate	   OnOrderMove;
	FOnOrderAttackDelegate	   OnOrderAttack;

public: 
	bool _is_selected = false;
	bool _lobby_finished = false;
public:
	UFUNCTION()
	void player_arm_event(bool armed_in);

	UFUNCTION()
	void player_crouch_event(bool crouch_in);

	UFUNCTION()
	void player_sprint_event(bool sprint_in);
};

