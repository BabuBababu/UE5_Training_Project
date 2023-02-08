// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBaseManager.h"


// generated
#include "DNUIManager.generated.h"

#define	UI_MANAGER				UDNUIManager::get_ui_manager()
#define WIDGET_MANAGER			UDNUIManager::get_ui_manager()->get_widget_manager()


/**
 *  위젯들을 관리하기 위한 매니저 클래스입니다.
 */

class UDNWidgetManager;
UCLASS()
class UE5_TRAINING_PROJECT_API UDNUIManager : public UDNBaseManager
{
	GENERATED_BODY()


protected:
	void init_manager() override;
	void destroy_manager() override;

private:
	UPROPERTY()
	TObjectPtr<UDNWidgetManager> _widget_manager = nullptr;

public:
	static TObjectPtr<UDNUIManager> get_ui_manager();


public:
	FORCEINLINE TObjectPtr<UDNWidgetManager> get_widget_manager() { return _widget_manager; };

};
