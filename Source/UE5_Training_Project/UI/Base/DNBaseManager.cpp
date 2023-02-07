


#include "UE5_Training_Project/UI/Base/DNBaseManager.h"


UDNBaseManager::UDNBaseManager(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	_is_initialize = false;
}



bool UDNBaseManager::initialize()
{
	if (_is_initialize == true)
	{
		return false;
	}

	init_manager();
	_is_initialize = true;

	return true;
}

bool UDNBaseManager::destroy()
{
	if (_is_initialize == false)
	{
		return false;
	}

	destroy_manager();
	_is_initialize = false;

	return true;
}