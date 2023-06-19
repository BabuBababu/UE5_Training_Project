

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
	void init_base();
	void init_missile();

	virtual void fire_1(ADNCommonCharacter* target_in);


	virtual void show_smoke();
	virtual void hide_smoke();
	void destroy_object_handler() override;

public:

	// 무브 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> _floting_movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAudioComponent> _audio_component;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = bullet)
	TSubclassOf<ADNBossMissile> _fire_1_class;

	UPROPERTY(EditAnywhere, Category = "Particle Effects")					//체력 적음 파티클
	UNiagaraSystem* _danger_particle;

	UPROPERTY(EditAnywhere, Category = "Particle Effects")					//체력 적음용 나이아가라 컴포넌트 공중 보스에 적용 예정
	TObjectPtr<UNiagaraComponent> _niagara_component;

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
