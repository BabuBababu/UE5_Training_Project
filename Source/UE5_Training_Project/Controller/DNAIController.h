// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine
#include <CoreMinimal.h>
#include <AIController.h>
#include <Perception/AIPerceptionTypes.h>

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// generated
#include "DNAIController.generated.h"

/**
 *		그리폰 인형 또는 적군이 사용할 AI 컨트롤러입니다.
 */

class UBehaviorTreeComponent;
class UBehaviorTree;
class UBlackboardComponent;
class UAISenseConfig_Sight;
class ADNCommonCharacter;
class ADNUnEnemyCharacter;
class ADNEnemyCharacter;


UCLASS()
class UE5_TRAINING_PROJECT_API ADNAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ADNAIController(FObjectInitializer const& object_initializer);
	virtual void OnPossess(APawn* pawn_in) override;
	virtual void OnUnPossess() override;
	virtual void Tick(float DeltaSeconds) override;
	
	TObjectPtr<UBlackboardComponent> get_blackboard() const;

	void add_event(ADNCommonCharacter* character_in);
	void remove_event(ADNCommonCharacter* character_in);

public:
	void ordered_move(FVector destination_in, ADNUnEnemyCharacter* doll_in);
	void ordered_attack(ADNEnemyCharacter* enemy_in, ADNUnEnemyCharacter* doll_in);
	void order_stop();

public:
	UFUNCTION()
	void OnUpdated(TArray<AActor*> const& updated_actors);

	UFUNCTION()
	virtual void OnTargetDetected(AActor* actor, FAIStimulus const Stimulus);

	UFUNCTION()
	void SetPerceptionSystem();

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTreeComponent> behavior_tree_component;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTree> btree;

public:

	//AI Perception 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AISightRadius = 5000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AILoseSightRadius = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AIFieldOfView = 90.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AISightAge = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AILastSeenLocation = 900.f;




protected:
	TObjectPtr<UBlackboardComponent> _blackboard;
	TObjectPtr<UAISenseConfig_Sight> _sight_config;


public:
	UFUNCTION()
	void update_beginplay_ammo_handler(int64 count_in);

	UFUNCTION()
	void update_empty_ammo_handler();

	UFUNCTION()
	void update_get_ammo_handler(int64 count_in);

	UFUNCTION()
	void reset_target_handler();

};
