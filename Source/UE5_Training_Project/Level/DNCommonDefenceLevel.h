

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
		TSubclassOf<ADNEnemyCharacter> _gun_enemy;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
		TSubclassOf<ADNDogEnemyCharacter> _dog_enemy;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
		TSubclassOf<ADNShieldEnemyCharacter> _shield_enemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boss)
		TSubclassOf<ADNCommonBossCharacter> _boss_enemy;
	
};
