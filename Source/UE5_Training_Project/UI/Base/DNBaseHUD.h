

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


UCLASS()
class UE5_TRAINING_PROJECT_API ADNBaseHUD : public AHUD
{
	GENERATED_BODY()
	

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


private:
	UPROPERTY()
	TObjectPtr<UDNPanelLayer>	_panel_layer = nullptr;

	UPROPERTY()
	TObjectPtr<UDNIntroLayer>	_intro_layer = nullptr;

protected:
	E_UI_HUD_TYPE				_hud_type = E_UI_HUD_TYPE::UHT_NONE;

private:
	void add_layer();
	void remove_layer();

	UDNBaseLayer* create_layer(E_UI_LAYER_TYPE layer_type_in);


public:
	const E_UI_HUD_TYPE  get_hud_type() const { return _hud_type; };
	//const UGFIntroLayer* get_intro_layer() const { return _login_layer; };
};
