

#pragma once

// Engine
#include <CoreMinimal.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"

// Component
#include <UE5_Training_Project/Component/DNStatusComponent.h>

// Manager
#include "UE5_Training_Project/Manager/DNSoundManager.h"
#include "UE5_Training_Project/Manager/DNObjectManager.h"


/**
 * 
 */

class UE5_TRAINING_PROJECT_API DNDamageOperation
{
public:
	// 원거리 사격
	static void gun_damage(float damage_in, FName bone_name_in, ADNCommonCharacter* damaged_character_in, ADNCommonCharacter* player_in)
	{
		if (bone_name_in == TEXT("Head") || bone_name_in == TEXT("Spine2"))		//이건 본마다 이름이 달라서 일단은 내버려둠
		{
			damage_in *= 2;
		}
		
		float after_hp = damaged_character_in->get_status_component().Get()->get_current_hp() - damage_in;
		damaged_character_in->get_status_component().Get()->set_current_hp(after_hp);
		SOUND_MANAGER->start_combat_sound();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Griffin Damage to Enemy : %f"), damage_in));

		if (after_hp <= 0)
		{
			damaged_character_in->get_status_component().Get()->_dead = true;
			damaged_character_in->OnTargetDead.Broadcast(player_in);
			
		}
	}

	static void melee_damage(float damage_in, ADNCommonCharacter* damaged_character_in, ADNCommonCharacter* player_in)
	{
		float after_hp = damaged_character_in->get_status_component().Get()->get_current_hp() - damage_in;
		damaged_character_in->get_status_component().Get()->set_current_hp(after_hp);
		SOUND_MANAGER->start_combat_sound();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Griffin Damage to Enemy : %f"), damage_in));

		if (after_hp <= 0)
		{
			damaged_character_in->get_status_component().Get()->_dead = true;
			damaged_character_in->OnTargetDead.Broadcast(player_in);

		}
	}

	static void radial_damage(UObject* world_in,float damage_in, FVector damage_location_in, float damage_radius_in,  ADNCommonCharacter* player_in)
	{
		UGameplayStatics::ApplyRadialDamage(world_in, damage_in, damage_location_in, damage_radius_in, nullptr, OBJECT_MANAGER->_griffin_player_array, player_in);
	}

	static void DamageShowUI(float damage_in, ADNCommonCharacter* damaged_character_in, E_DAMAGE_TYPE damage_type_in)
	{
		if (nullptr == damaged_character_in)
			return;

		// 대미지 인디케이터 위젯 보여주기
		damaged_character_in->OnDamageIndicator.Broadcast(damage_in, damage_type_in);
		
		// 스쿼드 위젯의 애니메이션 실행
		if (damaged_character_in->_character_type == E_CHARACTER_TYPE::CT_GRIFFIN)
		{
			ADNUnEnemyCharacter* doll = Cast<ADNUnEnemyCharacter>(damaged_character_in);
			doll->OnDamaged.Broadcast(doll->_squad_index);
		}
		
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("I Check Damage 1 ")));
	}

};
