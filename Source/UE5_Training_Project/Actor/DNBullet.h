

#pragma once

// Engine
#include <CoreMinimal.h> 
#include <GameFramework/Actor.h>

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNBullet.generated.h"


//
//	우선은 미사일 발사용 클래스로 만들었습니다.
//
//
//




class UProjectileMovementComponent;
class ADNHeliCommonCharacter;
class ADNCommonCharacter;
class UBoxComponent;

UCLASS()
class UE5_TRAINING_PROJECT_API ADNBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ADNBullet();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void add_event();
	virtual void remove_event();


public:
	void fire(ADNCommonCharacter* target_in );
	void init();
	void active_bullet();
	void non_active_bullet();
	void delay_destroy();



public:
	// 메쉬
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> _actor_static_mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* _box_collision;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	TObjectPtr<UProjectileMovementComponent> _projectile_movement_component;



	ADNHeliCommonCharacter* _owner;
	float					_limit_time;
	bool					_ready_destroy;


public:
	UFUNCTION()
		void overlap_actor_handler(const FHitResult& HitResult);
};
