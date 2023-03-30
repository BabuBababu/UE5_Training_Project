

#pragma once

// Engine
#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>
#include <Blueprint/IUserObjectListEntry.h>

// Generated
#include "DNScheduleCharacterEntryWidget.generated.h"

/**
 * 
 */

class UDNCharacterButton;
class UTextBlock; 

UCLASS()
class UE5_TRAINING_PROJECT_API UDNScheduleCharacterEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;


public:
	UPROPERTY()
	TObjectPtr<UDNCharacterButton> umg_character_button;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_friendship_text;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_morality_text;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_composure_text;

	UPROPERTY()
	TObjectPtr<UTextBlock> umg_positiveness_text;
};
