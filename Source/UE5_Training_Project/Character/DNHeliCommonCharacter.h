

#pragma once

// Engine
#include <CoreMinimal.h>
#include <Components/TimeLineComponent.h>
#include <NiagaraSystem.h>
#include <NiagaraFunctionLibrary.h>

// Character
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"

// Generated
#include "DNHeliCommonCharacter.generated.h"

/**
 * 
 */

class UFloatingPawnMovement;
class UAudioComponent;
class ADNBullet;

UCLASS()
class UE5_TRAINING_PROJECT_API ADNHeliCommonCharacter : public ADNUnEnemyCharacter
{
	GENERATED_BODY()
public:
	ADNHeliCommonCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void add_event() override;
	void remove_event() override;


public:
	void set_flying_move(float DeltaTime);
	void init_base();
	void init_missile();

	void fire_missile(ADNCommonCharacter* target_in) override;


	// 미정
	void set_rotor_mast();
	void set_rotor_back();
	void set_rotor_minigun();

public:
	// 메쉬
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<USkeletalMeshComponent> _sub_character_skeletal_mesh;	//기관 사수 캐릭터

	// 무브 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> _floting_movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAudioComponent> _audio_component;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = bullet)
	TSubclassOf<ADNBullet> _missile_class;


public:
	float _running_time;
	float _rotor_mast;
	float _rotor_back;
	float _rotor_minigun;
	float _missile_cool_time;
	float _missile_current_time;

	bool _missile_cool_time_start;

	TObjectPtr<ADNBullet> _missile;

	UPROPERTY(EditAnywhere, Category = Move)
	float XValue;

	UPROPERTY(EditAnywhere, Category = Move)
	float YValue;

	UPROPERTY(EditAnywhere, Category = Move)
	float ZValue;

};
