

#pragma once

// Engine
#include <CoreMinimal.h>

// Character
#include "UE5_Training_Project/Character/DNAirRaptureCharacter.h"

// Generated
#include "DNRaptureResVolitansCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNRaptureResVolitansCharacter : public ADNAirRaptureCharacter
{
	GENERATED_BODY()
	
public:
	ADNRaptureResVolitansCharacter();

protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	void add_event() override;
	void remove_event() override;

public:
	void init_base() override;
	void fire_1(ADNCommonCharacter* target_in) override;  // 대형 호밍 미사일
	virtual void fire_2(ADNCommonCharacter* target_in);	  // 도탄 미사일
	virtual void fire_3(ADNCommonCharacter* target_in);   // 소형 연발 호밍 미사일



public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = bullet)
	TSubclassOf<ADNBossMissile> _fire_2_class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = bullet)
	TSubclassOf<ADNBossMissile> _fire_3_class;

	UPROPERTY(EditAnywhere, Category = "Particle Effects")					//공중에 떠 있음 나이아가라 컴포넌트
	TObjectPtr<UNiagaraComponent> _flying_niagara_component;

	UPROPERTY(EditAnywhere, Category = "Particle Effects")					//공격시 나이아가라 컴포넌트
	TObjectPtr<UNiagaraComponent> _attack_niagara_component;


public:
	float _fire_2_cool_time;
	float _fire_2_current_time;

	bool _fire_2_cool_time_start;


	float _fire_3_cool_time;
	float _fire_3_current_time;

	bool _fire_3_cool_time_start;
};
