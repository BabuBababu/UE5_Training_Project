

#pragma once

// Engine
#include <CoreMinimal.h>
#include <NiagaraSystem.h>
#include <NiagaraFunctionLibrary.h>

// Actor
#include "UE5_Training_Project/Actor/DNCommonActor.h"

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNPatternTargetActor.generated.h"

/**
 * 
 */

class ADNCommonCharacter;

UCLASS()
class UE5_TRAINING_PROJECT_API ADNPatternTargetActor : public ADNCommonActor
{
	GENERATED_BODY()
public:
	ADNPatternTargetActor();
protected:
	virtual void BeginPlay() override;

	virtual void init() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = "Particle Effects")					//타겟 반짝임 파티클
	UNiagaraSystem* _target_deco_particle;


private:
	ADNCommonCharacter* _owner;
	bool _is_active;
	float _limit_time;
	float _max_hp;
	float _current_hp;
};
