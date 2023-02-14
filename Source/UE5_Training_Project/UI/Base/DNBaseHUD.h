

#pragma once


// Engine
#include <CoreMinimal.h>
#include <GameFramework/HUD.h>

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNBaseHUD.generated.h"

/**
 * 
 */

class UDNBaseLayer;
class UDNPanelLayer;
class UDNIntroLayer;

class UAudioComponent;

UCLASS()
class UE5_TRAINING_PROJECT_API ADNBaseHUD : public AHUD
{
	GENERATED_BODY()

public:
	ADNBaseHUD(const FObjectInitializer& ObjectInitializer);

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


private:
	UPROPERTY()
	TObjectPtr<UDNPanelLayer>	_panel_layer = nullptr;

	UPROPERTY()
	TObjectPtr<UDNIntroLayer>	_intro_layer = nullptr;


private:
	UPROPERTY()
	TObjectPtr<UAudioComponent> _audio_component_component = nullptr;

	UPROPERTY()
	TObjectPtr<UAudioComponent> _audio_component_effect = nullptr;

	UPROPERTY()
	TObjectPtr<UAudioComponent> _audio_component_background = nullptr;

protected:
	E_UI_HUD_TYPE				_hud_type = E_UI_HUD_TYPE::UHT_NONE;

private:
	void add_layer();
	void remove_layer();

	UDNBaseLayer* create_layer(E_UI_LAYER_TYPE layer_type_in);


public:
	const E_UI_HUD_TYPE  get_hud_type() const { return _hud_type; };
	//const UGFIntroLayer* get_intro_layer() const { return _login_layer; };


private:
	void					add_audio_component();
	void					remove_audio_component();

	void					set_audio_component();

public:
	UAudioComponent* get_audio_component(E_SOUND_TYPE sound_type_in);
};
