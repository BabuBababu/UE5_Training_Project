

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBaseContent.h"

// Generated
#include "DNScheduleWidget.generated.h"

/**
 * 
 */

class UDNScheduleList;
class UListView;
class UEditableTextBox;
class UButton;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNScheduleWidget : public UDNBaseContent
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;
	void NativeDestruct() override;
	void add_event() override;
	void remove_event() override;


public:
	TObjectPtr<UDNScheduleList> get_schedule_list() const { return umg_schedule_list; };

private:
	UPROPERTY()
	TObjectPtr<UDNScheduleList> umg_schedule_list;

	UPROPERTY()
	TObjectPtr<UListView> umg_character_list_view;

	UPROPERTY()
	TObjectPtr<UEditableTextBox> umg_work_time_edit_text;

	UPROPERTY()
	TObjectPtr<UEditableTextBox> umg_rest_time_edit_text;

	UPROPERTY()
	TObjectPtr<UButton> umg_confirm_button;
};
