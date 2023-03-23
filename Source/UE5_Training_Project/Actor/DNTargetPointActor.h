

#pragma once

// Engine
#include <CoreMinimal.h>

// Actor
#include "UE5_Training_Project/Actor/DNCommonActor.h"

// Generated
#include "DNTargetPointActor.generated.h"


/**
 *		지점으로 이동할 때 사용하는 액터입니다.
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNTargetPointActor : public ADNCommonActor
{
	GENERATED_BODY()

public:
	ADNTargetPointActor();

protected:
	virtual void BeginPlay() override;

	virtual void add_event() override;
	virtual void remove_event() override;

public:
	bool	_is_destroyed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	int64	_index;


public:

	UFUNCTION()
		void overlap_point_handler(class UPrimitiveComponent* selfComp, class AActor* otherActor, UPrimitiveComponent* otherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
