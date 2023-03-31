

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBaseManager.h"

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNWidgetManager.generated.h"

/**
 * 
 */


class UDNBasePanel;
class UDNBaseContent;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNWidgetManager : public UDNBaseManager
{
	GENERATED_BODY()

public:
	void initialize() override;
	void destroy() override;

public:
	// 레이어
	
	// 스크린



	// 패널
private:
	UPROPERTY()
	TMap<E_UI_PANEL_TYPE, UDNBasePanel*> _panel_array;

private:
	void clear_panel_data();

public:
	void add_panel(UDNBasePanel* panel_in);

	void remove_panel(UDNBasePanel* panel_in);
	void remove_panel(E_UI_PANEL_TYPE paenl_type_in);

	void open_panel(E_UI_PANEL_TYPE panel_type_in);
	void close_panel(E_UI_PANEL_TYPE panel_type_in);

	UDNBasePanel* get_panel(E_UI_PANEL_TYPE panel_type_in) const;



	// 컨텐츠

private:
	UPROPERTY()
		TMap<E_UI_CONTENT_TYPE, UDNBaseContent*> _content_array;

private:
	void clear_content_data();

public:
	void add_content(UDNBaseContent* content_in);

	void remove_content(UDNBaseContent* content_in);
	void remove_content(E_UI_CONTENT_TYPE content_type_in);

	void open_content(E_UI_CONTENT_TYPE content_type_in);
	void close_content(E_UI_CONTENT_TYPE content_type_in);

	UDNBaseContent* get_content(E_UI_CONTENT_TYPE content_type_in) const;

	// 팝업

	// 컨텍스트 메뉴

	// 툴팁
};
