

#pragma once

// Engine
#include <CoreMinimal.h>
#include <Engine/LevelScriptActor.h>

// Generated
#include "DNCommonDefenceLevel.generated.h"

/**
 * 
 */

class ADNEnemyCharacter;
class ADNShieldEnemyCharacter;
class ADNDogEnemyCharacter;
class ADNCommonBossCharacter;


UCLASS()
class UE5_TRAINING_PROJECT_API ADNCommonDefenceLevel : public ALevelScriptActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
		TSubclassOf<ADNEnemyCharacter> target_1_enemy;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
		TSubclassOf<ADNEnemyCharacter> target_2_enemy;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
		TSubclassOf<ADNEnemyCharacter> target_3_enemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
		TSubclassOf<ADNEnemyCharacter> target_4_enemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
		TSubclassOf<ADNEnemyCharacter> target_5_enemy;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	int64	_target_1_count = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	int64	_target_2_count = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	int64	_target_3_count = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	int64	_target_4_count = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	int64	_target_5_count = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boss)
	TSubclassOf<ADNCommonBossCharacter> _boss_enemy;
	
};
