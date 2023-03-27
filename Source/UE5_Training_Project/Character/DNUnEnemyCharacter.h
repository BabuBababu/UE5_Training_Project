// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine
#include <CoreMinimal.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// generated
#include "DNUnEnemyCharacter.generated.h"

/**
 *	 플레이어 및 그리폰 인형의 캐릭터 클래스입니다.
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNUnEnemyCharacter : public ADNCommonCharacter
{
	GENERATED_BODY()

public:
	ADNUnEnemyCharacter();
	virtual void fire() override;

	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	void add_event() override;
	void remove_event() override;

private:
	void init_ai();
	void init_base();

public:
	void set_attack_finish();

public:
	UFUNCTION()
	void change_armed_state_handler(bool armed_in);
	UFUNCTION()
	void change_crouch_state_handler(bool crouch_in);
	UFUNCTION()
	void change_sprint_state_handler(bool sprint_in);


	UFUNCTION()
	void order_move_handler(FVector destination_in, ADNUnEnemyCharacter* doll_in);
	UFUNCTION()
	void order_attack_handler(ADNEnemyCharacter* enemy_in, ADNUnEnemyCharacter* doll_in);

	void order_stop_handler();					// 이거는 델리게이트 사용하지않음

public:
	bool	_is_in_squad;
	bool	_is_ordered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Squad)			//전투시 스쿼드 위치 구분용
	int64	_squad_index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	E_CHARACTER_SPAWN_LEVEL_TYPE _spawn_level_type = E_CHARACTER_SPAWN_LEVEL_TYPE::CSLT_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lobby)			//원래 UI에서 설정해줘야하나 우선 테스트를 위해 여기서 설정
	E_LOBBY_AI_TYPE _lobby_ai_type = E_LOBBY_AI_TYPE::LAT_NONE;
};
