

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBaseManager.h"

// Data
#include "UE5_Training_Project/Data/DNSoundData.h"

// Defs
#include  "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNSoundManager.generated.h"

/**
 * 
 */


#define	SOUND_MANAGER				UDNSoundManager::get_sound_manager()

class UAudioComponent;
class UMetaSoundSource;


UCLASS()
class UE5_TRAINING_PROJECT_API UDNSoundManager : public UDNBaseManager
{
	GENERATED_BODY()

public:
	UDNSoundManager();

public:
	void initialize() override;
	void destroy() override;

private:
	UPROPERTY()
	UDataTable* _sound_data = nullptr;

	UPROPERTY()
	UAudioComponent* _audio_component_ui = nullptr;

	UPROPERTY()
	UAudioComponent* _audio_component_effect = nullptr;

	UPROPERTY()
	UAudioComponent* _audio_component_background = nullptr;

	UPROPERTY()
	UDataTable* _effect_sound_data = nullptr;

	UPROPERTY()
	UDataTable* _ui_sound_data = nullptr;

	UPROPERTY()
	UDataTable* _background_sound_data = nullptr;

	UPROPERTY()
	UDataTable* _sound_mix_data = nullptr;

	int64				_temp_mix_id = 0;
	FName				_temp_input_name;
	float				_temp_mix_duration = 0.0f;

public:
	FTimerHandle	_initialhandle_timer;
	FTimerHandle	_periodhandle_timer;


	bool				_is_combat;
	bool				_is_bgm_playing_now;
	bool				_is_ui_danger_now;

private:
	UMetaSoundSource*	find_meta_sound_data(E_SOUND_TYPE type_in, int64 id_in);
	USoundMix*			find_sound_mix_data(int64 id_in);

public:
	void				play_meta_sound(E_SOUND_TYPE type_in, int64 id_in, float start_time_in = 0.0f);		//범용적으로 쓸 것
	void				play_combat_meta_sound();

	void				stop_meta_sound(E_SOUND_TYPE type_in, float delay_in);
	void				pause_meta_sound(E_SOUND_TYPE type_in, bool is_paused_in);

	void				add_sound_mix(E_SOUND_TYPE type_in, int64 id_in, UAudioComponent* audio_component_in);

	
	UAudioComponent*	get_audio_component(E_SOUND_TYPE type_in);
	void				set_audio_component(E_SOUND_TYPE type_in, UAudioComponent* component_in);


public:
	void				set_combat_off();
	void				start_combat_sound();

public:
	static TObjectPtr<UDNSoundManager> get_sound_manager();

};
