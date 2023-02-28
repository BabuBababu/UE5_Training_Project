

#pragma once

// Engine
#include <CoreMinimal.h>
#include <Components/TimeLineComponent.h>

// Character
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"

// Generated
#include "DNHeliCommonCharacter.generated.h"

/**
 * 
 */

class UFloatingPawnMovement;

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

	// 미정
	void set_rotor_mast();
	void set_rotor_back();
	void set_rotor_minigun();

public:
	// 메쉬
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<USkeletalMeshComponent> _heli_skeletal_mesh;

	// 무브 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> _floting_movement;


public:
	float _running_time;
	float _rotor_mast;
	float _rotor_back;
	float _rotor_minigun;

	UPROPERTY(EditAnywhere, Category = Move)
	float XValue;

	UPROPERTY(EditAnywhere, Category = Move)
	float YValue;

	UPROPERTY(EditAnywhere, Category = Move)
	float ZValue;
};
