

#pragma once

// Engine
#include <UMG.h>
#include <Blueprint/UserWidget.h>

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Manager
#include "UE5_Training_Project/Manager/DNUIManager.h"
#include "UE5_Training_Project/UI/Manager/DNWidgetManager.h"

// Instance
#include "UE5_Training_Project/Core/DNGameInstance.h"

// Generated
#include "DNBaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API UDNBaseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct();
	virtual void NativeDestuct();

	virtual void add_event();
	virtual void remove_event();


public:
	const int64		get_widget_index() const { return _widget_index; };
	void			set_widget_index(int64 index_in) { _widget_index = index_in; };

private:
	UPROPERTY()
	int64	_widget_index = -1;

};
