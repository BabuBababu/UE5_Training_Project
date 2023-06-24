

#pragma once

// Engine
#include <CoreMinimal.h>
#include <NiagaraSystem.h>
#include <NiagaraFunctionLibrary.h>


// Character
#include "UE5_Training_Project/Character/DNEnemyCharacter.h"

// Generated
#include "DNAirRaptureCharacter.generated.h"

/**
 * 
 */


class UFloatingPawnMovement;
class UAudioComponent;
class ADNBossMissile;



UCLASS()
class UE5_TRAINING_PROJECT_API ADNAirRaptureCharacter : public ADNEnemyCharacter
{
	GENERATED_BODY()

public:
	ADNAirRaptureCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void add_event() override;
	void remove_event() override;


public:
	void set_flying_move(float DeltaTime);
	virtual void init_base() override;
	void init_missile();

	virtual void fire_1(ADNCommonCharacter* target_in);

	void destroy_object_handler() override;

public:

	// 무브 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> _floting_movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAudioComponent> _audio_component;							// 실시간으로 재생되는 사운드. 계속 작동하고 있는 느낌의 사운드를 넣어도 될듯

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = bullet)
	TSubclassOf<ADNBossMissile> _fire_1_class;

public:
	float _running_time;
	float _fire_1_cool_time;
	float _fire_1_current_time;

	bool _fire_1_cool_time_start;

	UPROPERTY(EditAnywhere, Category = Move)
	float XValue;

	UPROPERTY(EditAnywhere, Category = Move)
	float YValue;

	UPROPERTY(EditAnywhere, Category = Move)
	float ZValue;
};
