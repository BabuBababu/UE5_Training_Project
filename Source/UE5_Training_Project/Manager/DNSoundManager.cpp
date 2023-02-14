


#include "UE5_Training_Project/Manager/DNSoundManager.h"

// Engine
#include <Engine/DataTable.h>
#include <Components/AudioComponent.h>
#include <Kismet/GameplayStatics.h>

// meta sound
#include <MetasoundSource.h>



UDNSoundManager::UDNSoundManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>effect(TEXT("/Game/Blueprint/Data/DT_DNEffectSoundData.DT_DNEffectSoundData"));
	_effect_sound_data = effect.Object;

	////if (UNUIUtil::IsValid(_effect_sound_data)) //UE_LOG(LogTemp, Warning, TEXT("[NUI] UNUISoundManager - Effect Sound Data Load Completed"));
	static ConstructorHelpers::FObjectFinder<UDataTable>ui(TEXT("/Game/Blueprint/Data/DT_DNUISoundData.DT_DNUISoundData"));
	_ui_sound_data = ui.Object;

	////if (UNUIUtil::IsValid(_component_sound_data)) //UE_LOG(LogTemp, Warning, TEXT("[NUI] UNUISoundManager - component Sound Data Load Completed"));
	static ConstructorHelpers::FObjectFinder<UDataTable> bgm(TEXT("/Game/Blueprint/Data/DT_DNBGMSoundData.DT_DNBGMSoundData"));
	_background_sound_data = bgm.Object;

	////if (UNUIUtil::IsValid(_background_sound_data)) //UE_LOG(LogTemp, Warning, TEXT("[NUI] UNUISoundManager - Background Sound Data Load Completed"));
	static ConstructorHelpers::FObjectFinder<UDataTable> mix(TEXT("/Game/Blueprint/Data/DT_DNSoundMixData.DT_DNSoundMixData"));
	_sound_mix_data = mix.Object;


	_is_combat = false;
	_is_bgm_playing_now = false;	//BGM
	_is_ui_danger_now = false;		//UI
}

void UDNSoundManager::initialize()
{
	_manager_type = E_MANAGER_TYPE::MT_SOUND_MANAGER;

	Super::initialize();
}

void UDNSoundManager::destroy()
{
	Super::destroy();
}


UMetaSoundSource* UDNSoundManager::find_meta_sound_data(E_SOUND_TYPE type_in, int64 id_in)
{
	UMetaSoundSource* return_sound_source = nullptr;
	TArray<FDNMetaSoundSourceData*> meta_sound_source_data_array;

	switch (type_in)
	{
	case E_SOUND_TYPE::ST_EFFECT:
		if (nullptr != _effect_sound_data)
		{
			_effect_sound_data->GetAllRows(TEXT("SoundManager - Check Effect Sound Data"), meta_sound_source_data_array);
		}
		break;
	case E_SOUND_TYPE::ST_UI:
		if (nullptr != _ui_sound_data)
		{
			_ui_sound_data->GetAllRows(TEXT("SoundManager - Check Component Sound Data"), meta_sound_source_data_array);
		}
		break;
	case E_SOUND_TYPE::ST_BGM:
		if (nullptr != _background_sound_data)
		{
			_background_sound_data->GetAllRows(TEXT("SoundManager - Check Background Sound Data"), meta_sound_source_data_array);
		}
		break;
	case E_SOUND_TYPE::ST_NONE:
		break;
	default:
		break;
	}

	if (meta_sound_source_data_array.Num() > 0)
	{
		for (FDNMetaSoundSourceData* sound_source_data : meta_sound_source_data_array)
		{
			if (sound_source_data->id == id_in)
			{
				return_sound_source = sound_source_data->meta_sound_source_asset;
				_temp_mix_id = sound_source_data->sound_mix_id;
				_temp_input_name = sound_source_data->input_name;
				_temp_mix_duration = sound_source_data->sound_mix_duration;
				break;
			}
		}
	}

	return return_sound_source;
}

USoundMix* UDNSoundManager::find_sound_mix_data(int64 id_in)
{
	USoundMix* return_sound_mix = nullptr;
	TArray<FDNMetaSoundMIxData*> sound_mix_data_array;

	if (nullptr != _sound_mix_data)
	{
		_sound_mix_data->GetAllRows(TEXT(""), sound_mix_data_array);
		if (sound_mix_data_array.Num() > 0)
		{
			for (FDNMetaSoundMIxData* sound_mix_data : sound_mix_data_array)
			{
				if (sound_mix_data->id == id_in)
				{
					return_sound_mix = sound_mix_data->meta_sound_mix_asset;
					break;
				}
			}
		}
	}

	return return_sound_mix;
}



void UDNSoundManager::play_meta_sound(E_SOUND_TYPE type_in, int64 id_in, float start_time_in)
{
	UAudioComponent* target_audio_component = get_audio_component(type_in);
	int64 temp_check = 0;

	if (nullptr != target_audio_component)
	{
		target_audio_component->SetSound(find_meta_sound_data(type_in, id_in));

		if (_temp_mix_id == 0)
		{
			////UE_LOG(LogTemp, Warning, TEXT("00000000000000000000000"));
		}
		else
		{
			add_sound_mix(type_in, _temp_mix_id, target_audio_component);
		}

		//트리거 입력값이 None일때
		if (_temp_input_name == "None")
		{
			target_audio_component->Play();
		}
		//트리거 입력값이 존재할때
		else
		{
			target_audio_component->Play();
			target_audio_component->SetTriggerParameter(_temp_input_name);
			target_audio_component->SetBoolParameter(_temp_input_name, true);

		}

		// 설정해주었으면 다음 사운드를 위해 임시값 초기화
		_temp_mix_id = 0;
		_temp_input_name = "None";
		_temp_mix_duration = 0.0f;
	}
	//else //UE_LOG(LogTemp, Warning, TEXT("SoundManager - Audio Component Is Not Valid"));
}

void UDNSoundManager::stop_meta_sound(E_SOUND_TYPE type_in, float delay_in)
{
	UAudioComponent* target_audio_component = get_audio_component(type_in);
	if (nullptr !=  target_audio_component)
	{
		target_audio_component->StopDelayed(delay_in);
	}
	//else //UE_LOG(LogTemp, Warning, TEXT("SoundManager - Audio Component Is Not Valid"));
}

void UDNSoundManager::pause_meta_sound(E_SOUND_TYPE type_in, bool is_paused_in)
{
	UAudioComponent* target_audio_component = get_audio_component(type_in);
	if (nullptr != target_audio_component)
	{
		target_audio_component->SetPaused(is_paused_in);
	}
	//else //UE_LOG(LogTemp, Warning, TEXT("SoundManager - Audio Component Is Not Valid"));
}

void UDNSoundManager::add_sound_mix(E_SOUND_TYPE type_in, int64 id_in, UAudioComponent* audio_component_in)    //play_meta_sound에서 호출하고 이곳에서 해당 uid가 있다면 믹스 실행, 없으면 그냥 넘어가는 방식으로.
{																													 //사운드 믹스에 딜레이값을 줘서 언제 적용시킬지를 추가하면 사운드팀이 테스트하기 편할듯?
																													 // duration 값, 딜레이값을  메타사운드에서 조절하는것이 좋을듯.
	USoundMix* return_sound_mix = find_sound_mix_data(id_in);
	if (nullptr != audio_component_in)
	{
		if (nullptr != return_sound_mix)
		{
			return_sound_mix->Duration = _temp_mix_duration;

			UGameplayStatics::PushSoundMixModifier(audio_component_in, return_sound_mix);
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("SoundManager - SoundMix Is Not Valid.. Maybe you didn't set it! "));
		}
	}
	//else //UE_LOG(LogTemp, Warning, TEXT("SoundManager - Audio Component Is Not Valid"));
}

UAudioComponent* UDNSoundManager::get_audio_component(E_SOUND_TYPE type_in)
{
	UAudioComponent* return_audio_component = nullptr;

	switch (type_in)
	{
	case E_SOUND_TYPE::ST_EFFECT:
		return_audio_component = _audio_component_effect;
		break;
	case E_SOUND_TYPE::ST_UI:
		return_audio_component = _audio_component_ui;
		break;
	case E_SOUND_TYPE::ST_BGM:
		return_audio_component = _audio_component_background;
		break;
	case E_SOUND_TYPE::ST_NONE:
		break;
	default:
		break;
	}

	return return_audio_component;
}

void UDNSoundManager::set_audio_component(E_SOUND_TYPE type_in, UAudioComponent* component_in)
{
	switch (type_in)
	{
	case E_SOUND_TYPE::ST_EFFECT:
		_audio_component_effect = component_in;
		break;
	case E_SOUND_TYPE::ST_UI:
		_audio_component_ui = component_in;
		break;
	case E_SOUND_TYPE::ST_BGM:
		_audio_component_background = component_in;
		break;
	case E_SOUND_TYPE::ST_NONE:
		break;
	default:
		break;
	}

	//UE_LOG(LogTemp, Warning, TEXT("SoundManager - Sound play Ready"));
}




TObjectPtr<UDNSoundManager> UDNSoundManager::get_sound_manager()
{
	TArray<UObject*> object_array;
	GetObjectsOfClass(UDNSoundManager::StaticClass(), object_array);

	if (object_array.Num() > 0)
	{
		return Cast<UDNSoundManager>(object_array[0]);
	}

	return nullptr;
}




void UDNSoundManager::play_combat_meta_sound(E_SOUND_TYPE type_in, int64 id_in, float start_time_in)
{

	if (false == _is_combat)
	{
		stop_meta_sound(type_in, 1.f);
		GetWorld()->GetTimerManager().ClearTimer(_periodhandle_timer);
		GetWorld()->GetTimerManager().ClearTimer(_initialhandle_timer);
		_is_bgm_playing_now = false;
			
	}

}

void UDNSoundManager::set_combat_off()
{
	_is_combat = false;
}

void UDNSoundManager::start_combat_sound(E_SOUND_TYPE type_in, int64 id_in, float start_time_in)
{

	if (false == _is_bgm_playing_now)											//처음 한번만 실행
	{
		stop_meta_sound(type_in, 1.f);
		play_meta_sound(type_in, id_in, start_time_in);
		_is_bgm_playing_now = true;
	}
	
	_is_combat = true; 


	// BGM이라면 15초마다 전투가 종료되었는지 체크하고 종료되었다면 꺼줍니다.
	if (type_in == E_SOUND_TYPE::ST_BGM)
	{
		GetWorld()->GetTimerManager().SetTimer(_periodhandle_timer, FTimerDelegate::CreateUObject(this, &UDNSoundManager::play_combat_meta_sound, type_in, id_in, start_time_in), 15.f, true);
		GetWorld()->GetTimerManager().SetTimer(_initialhandle_timer, this, &UDNSoundManager::set_combat_off, 14.f, true);	//14초마다 컴뱃오프

	}
		
}