

#pragma once

// Engine
#include <CoreMinimal.h>
#include <BehaviorTree/BTTaskNode.h>

// Generated
#include "DNSetTargetTask.generated.h"

/**
 * 
 */

class ADNBossMissile;

UCLASS(Blueprintable)
class UE5_TRAINING_PROJECT_API UDNSetTargetTask : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UDNSetTargetTask(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in);
	void TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds);

	ADNBossMissile* set_first_target_missile(APawn* pawn_in,float max_distance_in); // 최대 50미터 내의 미사일 공격타겟 설정


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DistanceFromNikke", meta = (AllowPrivateAccess = "true"))
	float _max_distance = 5000.f;				//몇 미터 내의 미사일을 타겟으로 설정할 것인가? 기본 50미터
};
