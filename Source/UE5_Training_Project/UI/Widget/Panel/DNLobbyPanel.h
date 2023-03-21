

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBasePanel.h"

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNLobbyPanel.generated.h"

/**
 * 
 */



class UDNLobbySelectButton;
class UDNCommonButton;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNLobbyPanel : public UDNBasePanel
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;
	void NativeDestruct() override;

	void add_event() override;
	void remove_event() override;

private:
	UPROPERTY()
		TObjectPtr<UDNLobbySelectButton> umg_start_button;

	UPROPERTY()
		TObjectPtr<UDNCommonButton> umg_exit_button;

private:
	void init_panel();

public:
	const TObjectPtr<UDNLobbySelectButton> get_start_button() const { return  umg_start_button; };

};
