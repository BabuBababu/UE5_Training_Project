

#pragma once


// Engine
#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Data
#include "UE5_Training_Project/Data/DNUIData.h"

// Generated
#include "DNBaseComponent.generated.h"

/**
 * 
 */


class USizeBox;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNBaseComponent : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	TObjectPtr<USizeBox> umg_size_box;




public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	int32		component_index = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	bool		component_auto_size = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	FVector2D	component_size = FVector2D(40.0f, 40.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	bool		is_component_enabled = true;


protected:
	virtual void	NativePreConstruct() override;
	virtual void	NativeConstruct() override;
	virtual void	NativeDestruct() override;
	virtual void	NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


protected:
	virtual void	init_component();
	virtual void	update_component();

	virtual void	add_component_event() {};
	virtual void	remove_component_event() {};

	virtual void	native_component_enabled(bool is_enabled_in);
public:
	int32				const get_component_index() const { return component_index; };
	void				set_component_index(int32 index_in) { component_index = index_in; };

	const bool			get_is_component_enabled() const { return is_component_enabled; };
	void				set_is_component_enabled(bool is_enabled_in);

	const FVector2D		get_component_size() const { return component_size; };
	void				set_component_size(FVector2D size_in);


};
