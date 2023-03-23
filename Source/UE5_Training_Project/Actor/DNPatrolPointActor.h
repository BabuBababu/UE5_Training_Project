

#pragma once


// Engine
#include <CoreMinimal.h>

// Actor
#include "UE5_Training_Project/Actor/DNCommonActor.h"

// Generate
#include "DNPatrolPointActor.generated.h"

/**
 *		지점을 순찰할 때 사용하는 액터입니다.
 *		아군 적군 구분을 하고 싶다면 이 액터의 속성 defs를 만들고 함수 2개를 추가로 만들어서 해당 속성에 따라 add_event를 해줘도 될것같습니다.
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNPatrolPointActor : public ADNCommonActor
{
	GENERATED_BODY()

public:
	ADNPatrolPointActor();

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

	UFUNCTION()
	void unoverlap_point_handler(class UPrimitiveComponent* selfComp, class AActor* otherActor, UPrimitiveComponent* otherComp,
		int32 OtherBodyIndex);

};
