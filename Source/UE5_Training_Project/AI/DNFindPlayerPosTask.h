

#pragma once

// Engine
#include <CoreMinimal.h>
#include <BehaviorTree/BTTaskNode.h>

// Data
#include "UE5_Training_Project/Data/DNCharacterData.h"

// generated
#include "DNFindPlayerPosTask.generated.h"

/**
 * 
 */


class UDataTable;

UCLASS(Blueprintable)
class UE5_TRAINING_PROJECT_API UDNFindPlayerPosTask : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UDNFindPlayerPosTask(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in);


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SearchFromPlayer", meta = (AllowPrivateAccess = "true"))
	float _search_radius = 50.f;

public:
	UDataTable* _position_datatable;
	FDNCharacterPositionData* _chartacter_position_data;
};
