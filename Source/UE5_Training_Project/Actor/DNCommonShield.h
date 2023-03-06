

#pragma once

// Engine
#include <CoreMinimal.h>

// Actor
#include "UE5_Training_Project/Actor/DNCommonActor.h"

// Generated
#include "DNCommonShield.generated.h"

/**
 *	적군 방패 혹은 간혹 엄폐물을 들고 이동할 때 사용할 액터입니다.
 */


UCLASS()
class UE5_TRAINING_PROJECT_API ADNCommonShield : public ADNCommonActor
{
	GENERATED_BODY()
public:
	ADNCommonShield();

protected:
	virtual void BeginPlay() override;

	virtual void add_event() override;
	virtual void remove_event() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void reset();
	virtual void destroy_object();


public:
	float get_current_hp() const { return _hp; };
	void set_current_hp(const float hp_in) { _hp = hp_in; };
	void play_damaged_sound();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	float	_hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)			// 타격 소리
	TObjectPtr<USoundBase> _damaged_soundcue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)			// 부서지는 소리
	TObjectPtr<USoundBase> _destroy_soundcue;
};
