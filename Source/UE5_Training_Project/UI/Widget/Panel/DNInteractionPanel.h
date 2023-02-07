

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBasePanel.h"

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNInteractionPanel.generated.h"

/**
 * 
 */

class ADNCommonActor;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNInteractionPanel : public UDNBasePanel
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;


private:
	UPROPERTY()
	TObjectPtr<UCanvasPanel> umg_main_panel;

	UPROPERTY()
	TObjectPtr<UTextBlock> _umg_item_text;

	UPROPERTY()
	TObjectPtr<UTextBlock> _umg_vehicle_text;

	UPROPERTY()
	TObjectPtr<UTextBlock> _umg_npc_text;

	UPROPERTY()
	TObjectPtr<UImage> _umg_item_image;

	UPROPERTY()
	TObjectPtr<UImage> _umg_vehicle_image;
	
	UPROPERTY()
	TObjectPtr<UImage> _umg_npc_image;


public:
	E_UI_INTERACTION_TYPE	_interaction_type = E_UI_INTERACTION_TYPE::UIT_NONE;


public:
	TObjectPtr<UTextBlock> get_item_text() { return _umg_item_text; };
	TObjectPtr<UTextBlock> get_vehicle_text() { return _umg_vehicle_text; };
	TObjectPtr<UTextBlock> get_npc_text() { return _umg_npc_text; };

	TObjectPtr<UImage> get_item_image() { return _umg_item_image; };
	TObjectPtr<UImage> get_vehicle_image() { return _umg_vehicle_image; };
	TObjectPtr<UImage> get_npc_image() { return _umg_npc_image; };

	void change_interaction_type(E_UI_INTERACTION_TYPE type_in);


//private:
//	ADNCommonActor* _actor_data;						/이건 보류, 일단 라인트레이스에서 데이터를 가지고 있음
//
//public:
//	void set_actor_data(ADNCommonActor* actor_in) { _actor_data = actor_in; };	




};
