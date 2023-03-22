

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DNFindReportToPlayerPosTask.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UE5_TRAINING_PROJECT_API UDNFindReportToPlayerPosTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UDNFindReportToPlayerPosTask(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in);


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SearchFromPlayer", meta = (AllowPrivateAccess = "true"))
		float _search_radius = 50.f;
};
