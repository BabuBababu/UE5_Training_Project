

#pragma once

// Engine
#include <CoreMinimal.h>
#include <BehaviorTree/BTTaskNode.h>

// Generated
#include "DNCheckMoveToTask.generated.h"

/**
 *  이동 도중에 타겟을 발견하면 해당 이동 테스크를 취소합니다.
 */
UCLASS(Blueprintable)
class UE5_TRAINING_PROJECT_API UDNCheckMoveToTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UDNCheckMoveToTask(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in);
	void TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds);

};
