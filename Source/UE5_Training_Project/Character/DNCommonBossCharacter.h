

#pragma once

// Engine
#include <CoreMinimal.h>

// Character
#include "UE5_Training_Project/Character/DNEnemyCharacter.h"

// Generated
#include "DNCommonBossCharacter.generated.h"

/**
 * 
 */
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

	
public:
	// 메쉬
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<USkeletalMeshComponent> _character_sub_skeletal_mesh;
	
};
