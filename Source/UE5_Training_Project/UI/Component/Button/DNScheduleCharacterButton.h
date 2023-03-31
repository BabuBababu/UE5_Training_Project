

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
#include "DNScheduleCharacterButton.generated.h"

/**
 *		UDNCharacterButton과 유사합니다.
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStopAnimationEvent, UDNScheduleCharacterButton*, button);


UCLASS()
class UE5_TRAINING_PROJECT_API UDNScheduleCharacterButton : public UDNBaseWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;
	void NativeDestruct() override;
	void add_event() override;
	void remove_event() override;

public:
	void init();

public:
	void set_character_texture();
	void set_character_text();
	void init_data(FDNCharacterData data_in);
	void reset_data();

	FDNCharacterData get_data() const { return _character_data; };

private:
	UPROPERTY()
	TObjectPtr<UButton> umg_button;

	UPROPERTY()
	TObjectPtr<UImage> umg_character_image;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_character_text;


private:
	FDNCharacterData			_character_data;


public:
	FOnStopAnimationEvent		OnStopAnimation;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_LOBBY_AI_TYPE				_work_type = E_LOBBY_AI_TYPE::LAT_NONE;
public:
	UFUNCTION()
	void change_manager_working_array_handler();
};
