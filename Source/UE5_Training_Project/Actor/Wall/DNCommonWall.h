

#pragma once

// Engine
#include <CoreMinimal.h>

// Actor
#include "UE5_Training_Project/Actor/DNCommonActor.h"

// Generated
#include "DNCommonWall.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWallDelegate);


/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNCommonWall : public ADNCommonActor
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;

	virtual void add_event() override;
	virtual void remove_event() override;

public:
	virtual void Tick(float DeltaTime) override;


private:
	void init();

public:
	FOnWallDelegate		OnOverlapWall;
	FOnWallDelegate		OffOverlapWall;


	UFUNCTION()
	void overlap_wall_handler(class UPrimitiveComponent* selfComp, class AActor* otherActor, UPrimitiveComponent* otherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void unoverlap_wall_handler(UPrimitiveComponent* OverlappedComp, AActor* otherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
