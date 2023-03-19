


#include "UE5_Training_Project/Level/DNCommonDefenceLevel.h"

// Engine
#include <EngineUtils.h>
#include <Engine/TargetPoint.h>
#include <Kismet/GameplayStatics.h>

// Character
#include "UE5_Training_Project/Character/DNCommonBossCharacter.h"
#include "UE5_Training_Project/Character/DNDogEnemyCharacter.h"
#include "UE5_Training_Project/Character/DNEnemyCharacter.h"
#include "UE5_Training_Project/Character/DNShieldEnemyCharacter.h"



void ADNCommonDefenceLevel::BeginPlay()
{
	Super::BeginPlay();


	FVector target_point_1_location;
	FVector target_point_2_location;
	FVector target_point_3_location;

	TArray<AActor*> target_point_array;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), target_point_array);


	for (auto& point : target_point_array)
	{
		if (point->GetActorLabel() == "TargetPoint")
		{
			target_point_1_location = point->GetActorLocation();
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("TargetPoint1 Vector :%s"), *point->GetActorLocation().ToString()));

		}
		else if (point->GetActorLabel() == "TargetPoint2")
			target_point_2_location = point->GetActorLocation();
		else if (point->GetActorLabel() == "TargetPoint3")
			target_point_3_location = point->GetActorLocation();
	}


	for (int count = 0; count < _shield_enemy_count; ++count)
	{
		FVector temp_location = FVector(count * 100.f, 0.f, 500.f);
		ADNShieldEnemyCharacter* shield = GetWorld()->SpawnActor<ADNShieldEnemyCharacter>(_shield_enemy, target_point_1_location + temp_location,FRotator::ZeroRotator);
		
	}

	for (int count = 0; count < _dog_enemy_count; ++count)
	{
		FVector temp_location = FVector(count * 100.f, 0.f, 500.f);
		ADNDogEnemyCharacter* dog = GetWorld()->SpawnActor<ADNDogEnemyCharacter>(_dog_enemy, target_point_2_location+ temp_location, FRotator::ZeroRotator);
	}

	for (int count = 0; count < _gun_enemy_count; ++count)
	{
		FVector temp_location = FVector(count * 100.f, 0.f, 500.f);
		ADNEnemyCharacter* gun = GetWorld()->SpawnActor<ADNEnemyCharacter>(_gun_enemy, target_point_3_location+ temp_location, FRotator::ZeroRotator);
	}

}

void ADNCommonDefenceLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}