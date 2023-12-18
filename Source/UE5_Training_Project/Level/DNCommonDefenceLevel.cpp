


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

#pragma optimize( "", off )

void ADNCommonDefenceLevel::BeginPlay()
{
	Super::BeginPlay();


	FVector target_point_1_location;
	FVector target_point_2_location;
	FVector target_point_3_location;
	FVector target_point_4_location;
	FVector target_point_5_location;

	TArray<AActor*> target_point_array;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), target_point_array);

	if (target_point_array.Num() != 0)
	{
		for (int32 index = 0; index < target_point_array.Num(); ++index)
		{
			if (index == 0){target_point_1_location = target_point_array[index]->GetActorLocation();}
			else if (index == 1){target_point_2_location = target_point_array[index]->GetActorLocation();}
			else if (index == 2) { target_point_3_location = target_point_array[index]->GetActorLocation(); }
			else if (index == 3) { target_point_4_location = target_point_array[index]->GetActorLocation(); }
			else if (index == 4) { target_point_5_location = target_point_array[index]->GetActorLocation(); }
		}
		
	}



	


	for (int count = 0; count < _target_1_count; ++count)
	{
		FVector temp_location = FVector(count * 100.f, 0.f, 500.f);
		ADNEnemyCharacter* target1 = GetWorld()->SpawnActor<ADNEnemyCharacter>(target_1_enemy, target_point_1_location + temp_location,FRotator::ZeroRotator);
		
	}

	for (int count = 0; count < _target_2_count; ++count)
	{
		FVector temp_location = FVector(count * 100.f, 0.f, 500.f);
		ADNEnemyCharacter* target2 = GetWorld()->SpawnActor<ADNEnemyCharacter>(target_2_enemy, target_point_2_location+ temp_location, FRotator::ZeroRotator);
	}

	for (int count = 0; count < _target_3_count; ++count)
	{
		FVector temp_location = FVector(count * 100.f, 0.f, 500.f);
		ADNEnemyCharacter* target3 = GetWorld()->SpawnActor<ADNEnemyCharacter>(target_3_enemy, target_point_3_location+ temp_location, FRotator::ZeroRotator);
	}

	for (int count = 0; count < _target_4_count; ++count)
	{
		FVector temp_location = FVector(count * 100.f, 0.f, 500.f);
		ADNEnemyCharacter* target4 = GetWorld()->SpawnActor<ADNEnemyCharacter>(target_4_enemy, target_point_4_location + temp_location, FRotator::ZeroRotator);
	}

	for (int count = 0; count < _target_5_count; ++count)
	{
		FVector temp_location = FVector(count * 100.f, 0.f, 500.f);
		ADNEnemyCharacter* target5 = GetWorld()->SpawnActor<ADNEnemyCharacter>(target_5_enemy, target_point_5_location + temp_location, FRotator::ZeroRotator);
	}
}

#pragma optimize( "", on )

void ADNCommonDefenceLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}