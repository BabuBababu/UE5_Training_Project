

#pragma once

// Engine
#include <CoreMinimal.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"
#include "UE5_Training_Project/Character/DNCommonBossCharacter.h"

// Actor
#include "UE5_Training_Project/Actor/DNCommonShield.h"
#include "UE5_Training_Project/Actor/DNBossMissile.h"

// UI
#include "UE5_Training_Project/UI/Base/DNBasePanel.h"
#include "UE5_Training_Project/UI/Widget/DNDamageIndicator.h"
#include "UE5_Training_Project/UI/Widget/Panel/DNPortraitPanel.h"
#include "UE5_Training_Project/UI/Widget/Panel/DNCrosshairPanel.h"
#include "UE5_Training_Project/UI/Widget/Panel/DNCommentPanel.h"
#include "UE5_Training_Project/UI/Widget/Panel/DNEnemyStatusPanel.h"


// Util
#include "UE5_Training_Project/Util/DNItemSpawnSystem.h"

// Component
#include <UE5_Training_Project/Component/DNStatusComponent.h>

// Manager
#include "UE5_Training_Project/Manager/DNSoundManager.h"
#include "UE5_Training_Project/Manager/DNObjectManager.h"
#include "UE5_Training_Project/Manager/DNUIManager.h"


/**
 * 
 */

class UE5_TRAINING_PROJECT_API DNDamageOperation
{
public:

	// 캐릭터 사망시 행동할 함수
	static void die_from_damage(ADNCommonCharacter* damaged_character_in, ADNCommonCharacter* attack_character_in)
	{

		if (false == damaged_character_in->get_status_component().Get()->_dead)
		{
			// 인형 사망
			if (damaged_character_in->get_character_type() == E_CHARACTER_TYPE::CT_GRIFFIN)
			{
				// 전신샷 위젯 보여주기
				UDNBasePanel* panel = WIDGET_MANAGER->get_panel(E_UI_PANEL_TYPE::UPT_PORTRAIT);

				if (IsValid(panel))
				{
					UDNPortraitPanel* widget = Cast<UDNPortraitPanel>(panel);

					if (IsValid(widget))
					{
						widget->play_portrait_panel(damaged_character_in->_character_id, true);
					}
				}

				// 코멘트 출력
				UDNBasePanel* comment_panel = WIDGET_MANAGER->get_panel(E_UI_PANEL_TYPE::UPT_COMMENT);
				if (IsValid(comment_panel))
				{
					UDNCommentPanel* widget = Cast<UDNCommentPanel>(comment_panel);

					if (IsValid(widget))
					{
						widget->play_comment_isac(5);
					}
				}
			}
			
		}

		damaged_character_in->get_status_component().Get()->_dead = true;
		damaged_character_in->GetMovementComponent()->Deactivate();
		damaged_character_in->OnDead.Broadcast();
		attack_character_in->OnTargetDead.Broadcast();
		
	}

	// 원거리 사격
	static void gun_damage(float damage_in, FName bone_name_in, ADNCommonCharacter* damaged_character_in, ADNCommonCharacter* player_in)
	{

		// 스테이터스 위젯 애니메이션 재생
		UDNBasePanel* base_panel = WIDGET_MANAGER->get_panel(E_UI_PANEL_TYPE::UPT_ENEMY_STATUS);
		if (nullptr == base_panel)
			return;

		UDNEnemyStatusPanel* panel = dynamic_cast<UDNEnemyStatusPanel*>(base_panel);
		if (nullptr == panel)
			return;

		panel->play_damaged_animation(damaged_character_in);



		float after_hp = 0.f;

		// 헤드샷 적용 유무
		// 본마다 이름이 다른 경우가 있음!!
		if (bone_name_in == TEXT("neak_01") || bone_name_in == TEXT("head")) 
		{
			float head_damage = damage_in *= 2;

			// 플레이어라면 대미지 인디케이터 및 크로스헤어 표시
			if (player_in->get_character_type() == E_CHARACTER_TYPE::CT_PLAYER)
			{
				DNDamageOperation::ShowIndicatorUI(head_damage, damaged_character_in, E_DAMAGE_TYPE::DT_CRITICAL);
				DNDamageOperation::ShowCrossHairUI(true);
			}
			after_hp = damaged_character_in->get_status_component().Get()->get_current_hp() - head_damage;
			
		}
		else
		{
			// 플레이어라면 대미지 인디케이터 및 크로스헤어 표시
			if (player_in->get_character_type() == E_CHARACTER_TYPE::CT_PLAYER)
			{
				DNDamageOperation::ShowIndicatorUI(damage_in, damaged_character_in, E_DAMAGE_TYPE::DT_NORMAL);
				DNDamageOperation::ShowCrossHairUI(false);
			}
			after_hp = damaged_character_in->get_status_component().Get()->get_current_hp() - damage_in;
			
		}
		
		// 플레이어가 대미지를 받았다면 피격UI 표시
		if (damaged_character_in->get_character_type() == E_CHARACTER_TYPE::CT_PLAYER)
		{
			DNDamageOperation::ShowBloodUI();
		}

		damaged_character_in->get_status_component().Get()->set_current_hp(after_hp);
		SOUND_MANAGER->start_combat_sound();
		
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Griffin Damage to Enemy : %f"), damage_in));

		if (after_hp <= 0)
		{
			if (damaged_character_in->get_character_type() == E_CHARACTER_TYPE::CT_PLAYER ||
				damaged_character_in->get_character_type() == E_CHARACTER_TYPE::CT_GRIFFIN)
			{
				die_from_damage(damaged_character_in, player_in);
			}
			else
			{
				die_from_damage(damaged_character_in, player_in);
			}
		}
	}

	static void gun_damage_to_shield(float damage_in, ADNCommonShield* damaged_shield_in, ADNCommonCharacter* player_in)
	{
		float after_hp = damaged_shield_in->get_current_hp() - damage_in;
		damaged_shield_in->set_current_hp(after_hp);
		SOUND_MANAGER->start_combat_sound();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Griffin Damage to Enemy : %f"), damage_in));


		// 크로스헤어 표시
		if (player_in->get_character_type() == E_CHARACTER_TYPE::CT_PLAYER)
		{
			DNDamageOperation::ShowCrossHairUI(false);
		}

		if (after_hp <= 0)
		{
			damaged_shield_in->destroy_object();

		}
	}

	static void gun_damage_to_missile(float damage_in, ADNBossMissile* damaged_missile_in, ADNCommonCharacter* player_in)
	{
		float after_hp = damaged_missile_in->get_current_hp() - damage_in;
		damaged_missile_in->set_current_hp(after_hp);
		SOUND_MANAGER->start_combat_sound();

		// 크로스헤어 표시
		if (player_in->get_character_type() == E_CHARACTER_TYPE::CT_PLAYER)
		{
			DNDamageOperation::ShowCrossHairUI(false);
		}

		if (after_hp <= 0)
		{
			damaged_missile_in->destroy_object();

		}
	}

	// 원거리 사격 to 보스
	static void gun_damage_to_gun_spider_boss(float damage_in, FName bone_name_in, ADNCommonCharacter* damaged_character_in, ADNCommonCharacter* player_in)
	{

		// 스테이터스 위젯 애니메이션 재생
		UDNBasePanel* base_panel = WIDGET_MANAGER->get_panel(E_UI_PANEL_TYPE::UPT_ENEMY_STATUS);
		if (nullptr == base_panel)
			return;

		UDNEnemyStatusPanel* panel = dynamic_cast<UDNEnemyStatusPanel*>(base_panel);
		if (nullptr == panel)
			return;

		panel->play_damaged_animation(damaged_character_in);


		float after_hp = 0.f;

		// 헤드샷 적용 유무
		// 본마다 이름이 다른 경우가 있음!!
		if (bone_name_in == TEXT("knee1_jnt1") || bone_name_in == TEXT("knee1_jnt2") ||
			bone_name_in == TEXT("knee1_jnt3") || bone_name_in == TEXT("knee1_jnt4") ||
			bone_name_in == TEXT("vent_jnt"))
		{
			float head_damage = damage_in *= 2;

			// 플레이어라면 대미지 인디케이터 및 크로스헤어 표시
			if (player_in->get_character_type() == E_CHARACTER_TYPE::CT_PLAYER)
			{
				DNDamageOperation::ShowIndicatorUI(head_damage, damaged_character_in, E_DAMAGE_TYPE::DT_CRITICAL);
				DNDamageOperation::ShowCrossHairUI(true);
			}

			after_hp = damaged_character_in->get_status_component().Get()->get_current_hp() - head_damage;
			damaged_character_in->get_status_component().Get()->set_current_hp(after_hp);
			SOUND_MANAGER->start_combat_sound();
		}
		else
		{
			// 플레이어라면 대미지 인디케이터 및 크로스헤어 표시
			if (player_in->get_character_type() == E_CHARACTER_TYPE::CT_PLAYER)
			{
				DNDamageOperation::ShowIndicatorUI(damage_in, damaged_character_in, E_DAMAGE_TYPE::DT_NORMAL);
				DNDamageOperation::ShowCrossHairUI(false);
			}

			after_hp = damaged_character_in->get_status_component().Get()->get_current_hp() - damage_in;
			damaged_character_in->get_status_component().Get()->set_current_hp(after_hp);
			SOUND_MANAGER->start_combat_sound();
		}

		float left_hp_percent = (damaged_character_in->get_status_component().Get()->get_current_hp() / damaged_character_in->get_status_component().Get()->get_max_hp()) * 100;
		

		if (after_hp <= 0)
		{
			die_from_damage(damaged_character_in, player_in);

		}
		
		if (left_hp_percent / 100 <= 0.3f)
		{
			ADNCommonBossCharacter* boss = Cast<ADNCommonBossCharacter>(damaged_character_in);
			boss->show_smoke();
		}

	}


	static void melee_damage(float damage_in, ADNCommonCharacter* damaged_character_in, ADNCommonCharacter* player_in)
	{
		float after_hp = damaged_character_in->get_status_component().Get()->get_current_hp() - damage_in;
		damaged_character_in->get_status_component().Get()->set_current_hp(after_hp);
		SOUND_MANAGER->start_combat_sound();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Griffin Damage to Enemy : %f"), damage_in));

		
		if (damaged_character_in->get_character_type() == E_CHARACTER_TYPE::CT_PLAYER)				// 플레이어가 대미지를 받았다면 피격UI 표시
		{
			DNDamageOperation::ShowBloodUI();
		}

		if (after_hp <= 0)
		{
			die_from_damage(damaged_character_in, player_in);

		}
	}

	// 아군만 사용하는 메서드
	static void melee_damage_from_knife(float damage_in, ADNCommonCharacter* damaged_character_in, ADNCommonCharacter* player_in)
	{
		float after_hp = damaged_character_in->get_status_component().Get()->get_current_hp() - damage_in;
		damaged_character_in->get_status_component().Get()->set_current_hp(after_hp);
		SOUND_MANAGER->start_combat_sound();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Griffin Damage to Enemy : %f"), damage_in));

		if (damaged_character_in->get_character_type() == E_CHARACTER_TYPE::CT_ENEMY)			// 적이 대미지를 받았다면 대미지만 표시
		{
			DNDamageOperation::ShowIndicatorUI(damage_in, damaged_character_in, E_DAMAGE_TYPE::DT_CRITICAL);
			DNDamageOperation::ShowCrossHairUI(true);
		}

		if (after_hp <= 0)
		{
			die_from_damage(damaged_character_in, player_in);

		}
	}

	static void radial_damage_to_enemy(UObject* world_in,float damage_in, FVector damage_location_in, float damage_radius_in,  ADNCommonCharacter* player_in)
	{
		UGameplayStatics::ApplyRadialDamage(world_in, damage_in, damage_location_in, damage_radius_in, nullptr, OBJECT_MANAGER->_griffin_player_array, player_in);
	}

	static void radial_damage_to_all(UObject* world_in, float damage_in, FVector damage_location_in, float damage_radius_in, ADNCommonCharacter* player_in)
	{
		UGameplayStatics::ApplyRadialDamage(world_in, damage_in, damage_location_in, damage_radius_in, nullptr, TArray<AActor*>(), player_in);		//전원 타격
	}

	static void DamagedSquadUI(float damage_in, ADNCommonCharacter* damaged_character_in, E_DAMAGE_TYPE damage_type_in)
	{
		if (nullptr == damaged_character_in)
			return;



		// 스쿼드 위젯의 애니메이션 실행
		if (damaged_character_in->_character_type == E_CHARACTER_TYPE::CT_GRIFFIN)
		{
			ADNUnEnemyCharacter* doll = Cast<ADNUnEnemyCharacter>(damaged_character_in);
			doll->OnDamaged.Broadcast(doll->_squad_index);
		}
		
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("I Check Damage 1 ")));
	}


	static void ShowIndicatorUI(float damage_in, ADNCommonCharacter* damaged_character_in, E_DAMAGE_TYPE damage_type_in)
	{
		if (nullptr == damaged_character_in)
			return;

		// 대미지 인디케이터 위젯 보여주기
		if (damaged_character_in->_character_type == E_CHARACTER_TYPE::CT_ENEMY)
		{
			UDNBasePanel* panel = WIDGET_MANAGER->get_panel(E_UI_PANEL_TYPE::UPT_DAMAGE_INDICATOR);

			if (IsValid(panel))
			{
				UDNDamageIndicator* widget = Cast<UDNDamageIndicator>(panel);

				if (IsValid(widget))
				{
					widget->show_indicator(damage_in, damage_type_in);
				}
			}

		}


	}

	static void ShowCrossHairUI(bool is_critical_in)
	{
		UDNBasePanel* panel = WIDGET_MANAGER->get_panel(E_UI_PANEL_TYPE::UPT_CROSSHAIR);

		if (IsValid(panel))
		{
			UDNCrosshairPanel* widget = Cast<UDNCrosshairPanel>(panel);

			if (IsValid(widget))
			{
				if (is_critical_in)
					widget->play_critical_hit_animation();
				else
					widget->play_hit_animation();

			}
		}
	}

	static void ShowBloodUI()
	{
		UDNBasePanel* panel = WIDGET_MANAGER->get_panel(E_UI_PANEL_TYPE::UPT_CROSSHAIR);

		if (IsValid(panel))
		{
			UDNCrosshairPanel* widget = Cast<UDNCrosshairPanel>(panel);

			if (IsValid(widget))
			{
				widget->play_damaged_animation();

			}
		}
	}
};
