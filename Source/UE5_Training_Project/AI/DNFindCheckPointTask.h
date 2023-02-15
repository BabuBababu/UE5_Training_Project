

#pragma once

// Engine
#include <CoreMinimal.h>
#include <BehaviorTree/BTTaskNode.h>

// Generated
#include "DNFindCheckPointTask.generated.h"

/**
 * 
 */

class ADNTargetPointActor;

UCLASS(Blueprintable)
class UE5_TRAINING_PROJECT_API UDNFindCheckPointTask : public UBTTaskNode
{
	GENERATED_BODY()
	

public:
	UDNFindCheckPointTask(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
		float _search_radius = 1000.f;


public:
	TObjectPtr<ADNTargetPointActor> _now_point;
};
