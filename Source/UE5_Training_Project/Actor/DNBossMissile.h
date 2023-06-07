

#pragma once

// Engine
#include <CoreMinimal.h>

// Actor
#include "UE5_Training_Project/Actor/DNBullet.h"

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNBossMissile.generated.h"

/**
 * 
 */

class USplineComponent;

UCLASS()
class UE5_TRAINING_PROJECT_API ADNBossMissile : public ADNBullet
{
	GENERATED_BODY()

public:
	ADNBossMissile();

protected:
	virtual void BeginPlay() override;

public:
	void Tick(float DeltaTime) override;

	void add_event() override;
	void remove_event() override;

	void init() override;
	float get_current_hp() const { return _current_hp; };
	void set_current_hp(const float hp_in) { _current_hp = hp_in; };


	virtual void play_damaged_sound();
	virtual void destroy_object();

public:
	// 메쉬
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Move)
	TObjectPtr<USplineComponent> _spline_component;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float _max_hp;
public:
	float _current_hp;
	E_FIRE_TYPE _fire_type = E_FIRE_TYPE::FT_NONE;

public:
	void overlap_actor_handler(class UPrimitiveComponent* selfComp, class AActor* otherActor, UPrimitiveComponent* otherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;		//void overlap_actor_handler(const FHitResult& HitResult) override;

};
