

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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShotDelegate, ADNPlayerCharacter*, player);


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
	void set_burst_gauge(float value_in);

	void init_ui_event() override;
	void remove_ui_event() override;

	void order_move(FVector destination_in, ADNUnEnemyCharacter* doll_in);
	void order_attack(ADNEnemyCharacter* enemy_in, ADNUnEnemyCharacter* doll_in);			// 적 액터
	
	void play_hit_sound();

public:
	FOnShotDelegate on_attack;
	FOnArmDelegate on_armed;
	FOnCrouchDelegate on_crouch;
	FOnSprintDelegate on_sprint;


	FOnOrderMoveDelegate				OnOrderMove;
	FOnOrderAttackDelegate				OnOrderAttack;

public: 
	bool _is_selected = false;
	bool _lobby_finished = false;

	// 버스트 게이지는 세이브 요소가 아니므로 status에 두지 않았음.
	float _burst_current_gauge = 0.f;
	float _burst_max_gauge = 1000.f;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	E_CHARACTER_SPAWN_LEVEL_TYPE _spawn_level_type = E_CHARACTER_SPAWN_LEVEL_TYPE::CSLT_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)								//히트 사운드 (나중에 크리 히트 사운드랑 구별할 예정
	TObjectPtr<USoundBase> _bullet_hit_sound_cue;


public:
	UFUNCTION()
	void player_arm_event(bool armed_in);

	UFUNCTION()
	void player_crouch_event(bool crouch_in);

	UFUNCTION()
	void player_sprint_event(bool sprint_in);
};

