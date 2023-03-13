

#pragma once

// Engine
#include <CoreMinimal.h>
#include <NiagaraSystem.h>
#include <NiagaraFunctionLibrary.h>

// Character
#include "UE5_Training_Project/Character/DNEnemyCharacter.h"

// Generated
#include "DNCommonBossCharacter.generated.h"

/**
 *  fire_1은 기관총 공격, fire_2는 미사일 공격
 */

class ADNBossMissile;

UCLASS()
class UE5_TRAINING_PROJECT_API ADNCommonBossCharacter : public ADNEnemyCharacter
{
	GENERATED_BODY()
public:
	ADNCommonBossCharacter();

	virtual void add_event() override;
	virtual void remove_event() override;

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void fire_1(ADNCommonCharacter* target_in);
	virtual void fire_2(ADNCommonCharacter* target_in);
	virtual void melee_1(ADNCommonCharacter* target_in);
	virtual void melee_2(ADNCommonCharacter* target_in);
	virtual void show_smoke();

	void init_base();
public:
	// 메쉬
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<USkeletalMeshComponent> _character_sub_skeletal_mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = bullet)
	TSubclassOf<ADNBossMissile> _fire_2_class;


	UPROPERTY(EditAnywhere, Category = "Particle Effects")					//체력 적음 파티클
	UNiagaraSystem* _danger_particle;

public:
	float _fire_1_cool_time;
	float _fire_2_cool_time;
	float _melee_1_cool_time;
	float _melee_2_cool_time;

	float _fire_1_current_time;
	float _fire_2_current_time;
	float _melee_1_current_time;
	float _melee_2_current_time;

	bool _fire_2_cool_time_start;

	TArray<TObjectPtr<ADNBossMissile>> _missile_array;
};
