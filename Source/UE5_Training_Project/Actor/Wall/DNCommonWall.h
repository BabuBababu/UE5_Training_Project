

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
	
public:
	ADNCommonWall();

protected:
	virtual void BeginPlay() override;

	virtual void add_event() override;
	virtual void remove_event() override;

public:
	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* _left_box_collision_f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* _right_box_collision_f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* _left_box_collision_b;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* _right_box_collision_b;

public:
	FOnWallDelegate		OnOverlapWall;
	FOnWallDelegate		OffOverlapWall;


	UFUNCTION()
	void overlap_wall_handler(class UPrimitiveComponent* selfComp, class AActor* otherActor, UPrimitiveComponent* otherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void unoverlap_wall_handler(UPrimitiveComponent* OverlappedComp, AActor* otherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void overlap_left_collision_handler(class UPrimitiveComponent* selfComp, class AActor* otherActor, UPrimitiveComponent* otherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void unoverlap_left_collision_handler(UPrimitiveComponent* OverlappedComp, AActor* otherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
	void overlap_right_collision_handler(class UPrimitiveComponent* selfComp, class AActor* otherActor, UPrimitiveComponent* otherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void unoverlap_right_collision_handler(UPrimitiveComponent* OverlappedComp, AActor* otherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};
