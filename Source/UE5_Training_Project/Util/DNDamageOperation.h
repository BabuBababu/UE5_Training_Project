

#pragma once

// Engine
#include <CoreMinimal.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Component
#include <UE5_Training_Project/Component/DNStatusComponent.h>

/**
 * 
 */

class UE5_TRAINING_PROJECT_API DNDamageOperation
{
public:
	static void DNReceiveDamage(float damage_in, FName bone_name_in, ADNCommonCharacter* damaged_character_in)
	{
		if (bone_name_in == TEXT("Head") || bone_name_in == TEXT("Spine2"))
		{
			damage_in *= 2;
		}
		
		float after_hp = damaged_character_in->get_status_component().Get()->get_current_hp() - damage_in;
		damaged_character_in->get_status_component().Get()->set_current_hp(after_hp);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Griffin Damage to Enemy : %f"), damage_in));

		if (after_hp <= 0)
		{
			damaged_character_in->get_status_component().Get()->_dead = true;
		}
	}

};
