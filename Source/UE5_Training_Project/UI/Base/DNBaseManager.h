
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
	E_MANAGER_TYPE _manager_type = E_MANAGER_TYPE::MT_NONE;


protected:
	bool _is_initialize = false;
	bool _is_destroy = false;

public:
	virtual void initialize();
	virtual void destroy();

	E_MANAGER_TYPE get_manager_type() const { return _manager_type; };
};
