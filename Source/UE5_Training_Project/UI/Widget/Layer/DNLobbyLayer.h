

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBaseLayer.h"

// Generated
#include "DNLobbyLayer.generated.h"

/**
 * 
 */

class UDNLobbyPanel;
class UDNSelectSquadPanel;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNLobbyLayer : public UDNBaseLayer
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY()
	TObjectPtr<UDNLobbyPanel> umg_lobby_panel;
	UPROPERTY()
	TObjectPtr<UDNSelectSquadPanel> umg_make_squad_panel;

	
};
