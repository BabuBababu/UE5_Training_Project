// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine
#include <CoreMinimal.h>
#include <AIController.h>
#include <Perception/AIPerceptionTypes.h>

// generated
#include "DNAIController.generated.h"

/**
 *		그리폰 인형 또는 적군이 사용할 AI 컨트롤러입니다.
 */

class UBehaviorTreeComponent;
class UBehaviorTree;
class UBlackboardComponent;
class UAISenseConfig_Sight;

UCLASS()
class UE5_TRAINING_PROJECT_API ADNAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ADNAIController(FObjectInitializer const& object_initializer);
	virtual void OnPossess(APawn* pawn_in) override;
	virtual void OnUnPossess() override;

	TObjectPtr<UBlackboardComponent> get_blackboard() const;
public:
	UFUNCTION()
	void OnUpdated(TArray<AActor*> const& updated_actors);

	UFUNCTION()
	void OnTargetDetected(AActor* actor, FAIStimulus const Stimulus);

	UFUNCTION()
	void SetPerceptionSystem();

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTreeComponent> behavior_tree_component;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTree> btree;

public:
	static const FName HomePosKey;
	static const FName TargetLocation;

	//AI Perception 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AISightRadius = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AILoseSightRadius = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AIFieldOfView = 90.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AISightAge = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AILastSeenLocation = 900.f;




private:
	TObjectPtr<UBlackboardComponent> _blackboard;
	TObjectPtr<UAISenseConfig_Sight> _sight_config;

};
