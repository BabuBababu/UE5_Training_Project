

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBaseWidget.h"

// Data
#include "UE5_Training_Project/Data/DNCharacterData.h"

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNCharacterButton.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API UDNCharacterButton : public UDNBaseWidget
{
	GENERATED_BODY()
protected:
	void NativeConstruct() override;
	void NativeDestruct() override;
	void add_event() override;
	void remove_event() override;

public:
	void set_data(FDNCharacterData* data_in) { _character_data = data_in; };
	FDNCharacterData* get_data() const { return _character_data; };
	void init();

public:
	void set_character_texture();
	void set_character_text();

private:
	UPROPERTY()
	TObjectPtr<UButton> umg_button;

	UPROPERTY()
	TObjectPtr<UImage> umg_character_image;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_character_text;


private:
	FDNCharacterData* _character_data;
};
