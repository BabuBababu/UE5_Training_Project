


#include "UE5_Training_Project/UI/Base/DNBaseHUD.h"

// Engine
#include <Metasound.h>

// Layer
#include "UE5_Training_Project/UI/Widget/Layer/DNPanelLayer.h"
#include "UE5_Training_Project/UI/Widget/Layer/DNIntroLayer.h"
#include "UE5_Training_Project/UI/Widget/Layer/DNLobbyLayer.h"



ADNBaseHUD::ADNBaseHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	_hud_type(E_UI_HUD_TYPE::UHT_NONE)
{
	add_audio_component();
}

void ADNBaseHUD::BeginPlay()
{
	Super::BeginPlay();

	//NUI_MANAGER->set_hud(this);
	UE_LOG(LogTemp, Warning, TEXT("[UI] HUD Ready - %s"), *GetName());
	UE_LOG(LogTemp, Warning, TEXT("I will add_layer [2]"));

	add_layer(); 
	set_audio_component();
}

void ADNBaseHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	remove_layer();
	remove_audio_component();

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
		if (_lobby_layer == nullptr) _lobby_layer = Cast<UDNLobbyLayer>(create_layer(E_UI_LAYER_TYPE::ULT_SELECT_CHARACTER));
		if (_lobby_layer != nullptr) _lobby_layer->AddToViewport();
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
		layer_class = LoadObject<UClass>(NULL, TEXT("/Game/Blueprint/UI/Layer/BP_DNPanelLayer.BP_DNPanelLayer_C")); //패널 레이어가 들어가야함
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
		layer_class = LoadObject<UClass>(NULL, TEXT("/Game/Blueprint/UI/Layer/BP_DNLobbyLayer.BP_DNLobbyLayer_C")); //로비 레이어가 들어가야함
		UE_LOG(LogTemp, Warning, TEXT(" i created_layer [3]"));
		if (layer_class != nullptr)
		{
			return_layer = CreateWidget<UDNLobbyLayer>(GetWorld(), layer_class);
			UE_LOG(LogTemp, Warning, TEXT(" i made [4]"));
		}
		break;

	case E_UI_LAYER_TYPE::ULT_NONE:
	case E_UI_LAYER_TYPE::ULT_COUNT:
	default:
		break;
	}

	return return_layer;
}


void ADNBaseHUD::add_audio_component()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("root_component"));

	_audio_component_component = CreateDefaultSubobject<UAudioComponent>(TEXT("audio_component_component"));
	if (!IsValid(_audio_component_component))
	{
		_audio_component_component->AddToRoot();
		_audio_component_component->SetUISound(true);
	}

	_audio_component_effect = CreateDefaultSubobject<UAudioComponent>(TEXT("audio_component_effect"));
	if (!IsValid(_audio_component_effect))
	{
		_audio_component_effect->AddToRoot();
		_audio_component_effect->SetUISound(true);
	}

	_audio_component_background = CreateDefaultSubobject<UAudioComponent>(TEXT("audio_component_background"));
	if (!IsValid(_audio_component_background))
	{
		_audio_component_background->AddToRoot();
		_audio_component_background->SetUISound(true);
	}
}

void ADNBaseHUD::remove_audio_component()
{
	if (IsValid(_audio_component_component))
	{
		_audio_component_component->RemoveFromRoot();
	}

	if (IsValid(_audio_component_effect))
	{
		_audio_component_effect->RemoveFromRoot();
	}

	if (IsValid(_audio_component_background))
	{
		_audio_component_background->RemoveFromRoot();
	}

	_audio_component_component = nullptr;
	_audio_component_effect = nullptr;
	_audio_component_background = nullptr;
}

void ADNBaseHUD::set_audio_component()
{
	if (IsValid(_audio_component_component))
	{
		SOUND_MANAGER->set_audio_component(E_SOUND_TYPE::ST_UI, _audio_component_component);
	}

	if (IsValid(_audio_component_effect))
	{
		SOUND_MANAGER->set_audio_component(E_SOUND_TYPE::ST_EFFECT, _audio_component_effect);
	}

	if (IsValid(_audio_component_background))
	{
		SOUND_MANAGER->set_audio_component(E_SOUND_TYPE::ST_BGM, _audio_component_background);
	}
}

//////////////////////////////////////////////////////////////////////////
// get set
//////////////////////////////////////////////////////////////////////////
UAudioComponent* ADNBaseHUD::get_audio_component(E_SOUND_TYPE sound_type_in)
{
	UAudioComponent* return_audio_component = nullptr;

	switch (sound_type_in)
	{
	case E_SOUND_TYPE::ST_UI:
		return_audio_component = _audio_component_component;
		break;
	case E_SOUND_TYPE::ST_EFFECT:
		return_audio_component = _audio_component_effect;
		break;
	case E_SOUND_TYPE::ST_BGM:
		return_audio_component = _audio_component_background;
		break;
	case E_SOUND_TYPE::ST_NONE:
	case E_SOUND_TYPE::ST_COUNT:
	default:
		break;
	}

	return return_audio_component;
}
