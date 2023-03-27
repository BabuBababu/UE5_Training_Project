﻿

#pragma once

// Engine
#include <CoreMinimal.h>
#include <BehaviorTree/BTTaskNode.h>

// Generated
#include "DNWakeUpTask.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UE5_TRAINING_PROJECT_API UDNWakeUpTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UDNWakeUpTask(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in);
	void TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds);

public:
	bool	_start_wakeup = false;
	bool	_is_play_animation = false;
	float	_rest_left_time = 0.f;

};