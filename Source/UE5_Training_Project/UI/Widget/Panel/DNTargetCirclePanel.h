

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBasePanel.h"

// Generated
#include "DNTargetCirclePanel.generated.h"

/**
 * 
 */

class ADNPatternTargetActor;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNTargetCirclePanel : public UDNBasePanel
{
	GENERATED_BODY()
	
protected:
	void NativeConstruct() override;
	void NativeDestruct() override;
	void add_event() override;
	void remove_event() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
public:
	void set_widget(ADNPatternTargetActor* owner_in);
	void close_widget();

	void set_time_percent(float time_in);
	void set_hp_percent(float hp_in);
	void init();


private:
	UPROPERTY()
	TObjectPtr<UOverlay> umg_main_overlay;
	
	UPROPERTY()
	TObjectPtr<UImage> umg_target_time_circle_icon;

	UPROPERTY()
	TObjectPtr<UImage> umg_target_circle_icon;
private:
	float _max_time;
	float _current_time;
	float _current_hp;
	float _max_hp;

	ADNPatternTargetActor* _owner;
};
