

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DNForcedMoveToTask.generated.h"

/**
 *  타겟액터를 발견했더라도 공격하지않고 쳐다보지도 않고 이동하는 테스크입니다.
 *	안쳐다보고 가는건 좋은데 이동하면서 공격할 때 모션이 이상해서 일단 안쓰기로.
 */
UCLASS(Blueprintable)
class UE5_TRAINING_PROJECT_API UDNForcedMoveToTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UDNForcedMoveToTask(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in);
	void TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds);
};
