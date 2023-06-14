

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBasePanel.h"

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNPlayerCombatPanel.generated.h"

/**
 * 
 */

class UDNPlayerGaugeBar;
class ADNCommonCharacter;
class UDNSquadPanel;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNPlayerCombatPanel : public UDNBasePanel
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UCanvasPanel> umg_main_panel;

	UPROPERTY()
	TObjectPtr<UCanvasPanel> umg_sub_panel;

	UPROPERTY()
	TObjectPtr<UOverlay> umg_ammo_overlay;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_save_ammo_text;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_current_ammo_text;

	// 스킬1
	UPROPERTY()
	TObjectPtr<UOverlay> umg_skill1_overlay;

	UPROPERTY()
	TObjectPtr<UImage> umg_skill1_icon;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_skill1_cooltime_text;

	// 스킬2
	UPROPERTY()
	TObjectPtr<UOverlay> umg_skill2_overlay;

	UPROPERTY()
	TObjectPtr<UImage> umg_skill2_icon;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_skill2_cooltime_text;

	// 스킬3
	UPROPERTY()
	TObjectPtr<UOverlay> umg_skill3_overlay;

	UPROPERTY()
	TObjectPtr<UImage> umg_skill3_icon;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_skill3_cooltime_text;

	// 스킬4
	UPROPERTY()
	TObjectPtr<UOverlay> umg_skill4_overlay;

	UPROPERTY()
	TObjectPtr<UImage> umg_skill4_icon;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_skill4_cooltime_text;

	// 스킬5
	UPROPERTY()
	TObjectPtr<UOverlay> umg_skill5_overlay;

	UPROPERTY()
	TObjectPtr<UImage> umg_skill5_icon;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_skill5_cooltime_text;

	// 무기 타입
	UPROPERTY()
	TObjectPtr<UOverlay> umg_weapon_type_overlay;

	UPROPERTY()
	TObjectPtr<UImage> umg_weapon_type_icon;

	// 플레이어 타입
	UPROPERTY()
	TObjectPtr<UOverlay> umg_player_type_overlay;

	UPROPERTY()
	TObjectPtr<UImage> umg_player_type_icon;

	// 체력
	UPROPERTY()
	TObjectPtr<UDNPlayerGaugeBar> umg_bar_hp;
	

private:
	UPROPERTY()
	ADNCommonCharacter* _my_character = nullptr;

	float _current_hp = 0.0f;
	float _max_hp = 0.0f;

	int64 _current_ammo = 0;
	int64 _has_ammo = 0;

	float _current_sp = 0.0f;
	float _max_sp = 0.0f;

public:
	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* umg_shot_animation;

	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* umg_empty_animation;


protected:
	virtual void	NativeConstruct() override;
	virtual void	NativeDestruct() override;
	virtual void	NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void	add_event() override;
	virtual void	remove_event() override;


private:
	void init_gauge();
	void set_player_character();

	void sync_gauge();


public:
	void set_hp(float current_hp_in, float max_hp_in);

	void play_shot_animation();
	void play_empty_animation();


public:
	UFUNCTION()
	void play_shot_animation_handler(ADNPlayerCharacter* player_in);



};
