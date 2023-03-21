

#pragma once

// Engine
#include <CoreMinimal.h>

// Component
#include "UE5_Training_Project/UI/Component/Button/DNCommonButton.h"

// Generated
#include "DNLobbySelectButton.generated.h"

/**
 * 
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSelectButtonEvent);



UCLASS()
class UE5_TRAINING_PROJECT_API UDNLobbySelectButton : public UDNCommonButton
{
	GENERATED_BODY()
	

protected:
	void add_component_event() override;
	void remove_component_event() override;


protected:
	UFUNCTION()
	void change_state_handler(bool flag_in);

	UFUNCTION()
	void selected_handler(UDNCommonButton* button_in);

public:
	UPROPERTY()
	FSelectButtonEvent OnSelected;


};
