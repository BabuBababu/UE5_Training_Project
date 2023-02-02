

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBaseLayer.h"

// Generated
#include "DNPanelLayer.generated.h"

/**
 * 
 */

class UImage;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNPanelLayer : public UDNBaseLayer
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY()
	TObjectPtr<UImage> umg_crosshair_image;

	//PlayerUI를 C++ 클래스로 만들고 umg로 넣어서 관리해야함 일단은 그냥 부르는걸로 .
};
