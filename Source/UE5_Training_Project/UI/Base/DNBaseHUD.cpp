


#include "UE5_Training_Project/UI/Base/DNBaseHUD.h"

// Layer
#include "UE5_Training_Project/UI/Widget/Layer/DNPanelLayer.h"
#include "UE5_Training_Project/UI/Widget/Layer/DNIntroLayer.h"



void ADNBaseHUD::BeginPlay()
{
	Super::BeginPlay();

	//NUI_MANAGER->set_hud(this);
	UE_LOG(LogTemp, Warning, TEXT("[UI] HUD Ready - %s"), *GetName());
	UE_LOG(LogTemp, Warning, TEXT("I will add_layer [2]"));

	add_layer();
}

void ADNBaseHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	remove_layer();

	Super::EndPlay(EndPlayReason);
}

void ADNBaseHUD::add_layer()
{
	switch (_hud_type)
	{
	//로그인
	case E_UI_HUD_TYPE::UHT_INTRO: // 게임 시작했을때 화면에 보여줄 레이어들
		if (_intro_layer == nullptr) _intro_layer = Cast<UDNIntroLayer>(create_layer(E_UI_LAYER_TYPE::ULT_INTRO));
		if (_intro_layer != nullptr) _intro_layer->AddToViewport();
		break;

	//로비
	case E_UI_HUD_TYPE::UHT_LOBBY_HUD:

		break;

	// 전투
	case E_UI_HUD_TYPE::UHT_COMBAT_HUD: // 게임 플레이할때 화면에 보여줄 레이어들
		//	if (!UNUIUtil::IsValid(_content_layer)) _content_layer = Cast<UNUIContentLayer>(create_layer(E_NUI_LAYER_TYPE::NLT_CONTENT));
		//	if (UNUIUtil::IsValid(_content_layer)) _content_layer->AddToViewport(NUI_CONTENT_LAYER_Z_INDEX);
		if (_panel_layer == nullptr) _panel_layer = Cast<UDNPanelLayer>(create_layer(E_UI_LAYER_TYPE::ULT_HUD));
		if (_panel_layer != nullptr) _panel_layer->AddToViewport();
		break;
	default:
		break;
	}
}

void ADNBaseHUD::remove_layer()
{
	if (_intro_layer != nullptr) _intro_layer->RemoveFromParent();
	//if (UNUIUtil::IsValid(_content_layer)) _content_layer->RemoveFromViewport();
	if (_panel_layer != nullptr) _panel_layer->RemoveFromParent();

	_intro_layer = nullptr;
	_panel_layer = nullptr;
}

UDNBaseLayer* ADNBaseHUD::create_layer(E_UI_LAYER_TYPE layer_type_in)
{
	UDNBaseLayer* return_layer = nullptr;
	UClass* layer_class = nullptr;
	switch (layer_type_in)
	{
	case E_UI_LAYER_TYPE::ULT_HUD: // 체력, 탄창 크로스헤어 등
		layer_class = LoadObject<UClass>(NULL, TEXT("/Game/Blueprint/UI/Layer/BP_DNPanelLayer.BP_DNPanelLayer_C")); //패널레이어가 들어가야함
		UE_LOG(LogTemp, Warning, TEXT(" i created_layer [3]"));
		if (layer_class != nullptr)
		{
			return_layer = CreateWidget<UDNPanelLayer>(GetWorld(), layer_class);
			UE_LOG(LogTemp, Warning, TEXT(" i made [4]"));
		}
		break;
	case E_UI_LAYER_TYPE::ULT_NOTICE:
		break;
	case E_UI_LAYER_TYPE::ULT_CONTENT:
		//layer_class = UNUIUtil::LoadObjectString<UClass>(TEXT("/NUI/Widget/Layer/WD_NUIContentLayer.WD_NUIContentLayer_C"));
		//if (UNUIUtil::IsValid(layer_class))
		//{
		//	return_layer = CreateWidget<UNUIContentLayer>(GetWorld(), layer_class);
		//}
		break;
	case E_UI_LAYER_TYPE::ULT_SYSTEM:
		break;
	case E_UI_LAYER_TYPE::ULT_SELECT_CHARACTER:
		break;

	case E_UI_LAYER_TYPE::ULT_NONE:
	case E_UI_LAYER_TYPE::ULT_COUNT:
	default:
		break;
	}

	return return_layer;
}
