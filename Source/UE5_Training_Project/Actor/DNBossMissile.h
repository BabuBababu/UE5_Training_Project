

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
 *  bossmissile이 아니라 그냥 enemymissile로 바꿀거임
 */



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDestroyForTargetDelegate, AActor*, missile);



class USplineComponent;
class UAIPerceptionStimuliSourceComponent;

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USplineComponent> _spline_component;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UAIPerceptionStimuliSourceComponent> _perception_stimuli_source;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float _max_hp;

public:
	float _current_hp;
	float _boost_time;
	float _boost_current_time;
	bool _is_boost;


public:
	FOnDestroyForTargetDelegate OnDestroyMissile;

public:
	void overlap_actor_handler(class UPrimitiveComponent* selfComp, class AActor* otherActor, UPrimitiveComponent* otherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
