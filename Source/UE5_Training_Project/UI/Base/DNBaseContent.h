

#pragma once


// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBaseWidget.h"

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNBaseContent.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API UDNBaseContent : public UDNBaseWidget
{
	GENERATED_BODY()

	//////////////////////////////////////////////////////////////////////////
	// override
	//////////////////////////////////////////////////////////////////////////
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	//////////////////////////////////////////////////////////////////////////
	// base
	//////////////////////////////////////////////////////////////////////////
protected:
	E_UI_CONTENT_TYPE	content_type = E_UI_CONTENT_TYPE::UCT_NONE;

public:
	virtual void update_content();



	//////////////////////////////////////////////////////////////////////////
	// getter setter
	//////////////////////////////////////////////////////////////////////////
public:
	const E_UI_CONTENT_TYPE get_content_type() const { return content_type; };
	void set_content_type(E_UI_CONTENT_TYPE content_type_in) { content_type = content_type_in; };
};
