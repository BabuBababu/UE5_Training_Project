
#pragma once

// Engine
#include <CoreMinimal.h>
#include <UObject/NoExportTypes.h>

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNBaseManager.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class UE5_TRAINING_PROJECT_API UDNBaseManager : public UObject
{
	GENERATED_BODY()

public:
	UDNBaseManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	E_UI_MANAGER_TYPE _manager_type = E_UI_MANAGER_TYPE::UMT_NONE;


private:
	bool _is_initialize = false;
	bool _is_destroy = false;

public:
	bool initialize();
	bool destroy();

	E_UI_MANAGER_TYPE get_manager_type() const { return _manager_type; };

protected:
	virtual void init_manager() {};
	virtual void destroy_manager() {};
};
