


#include "UE5_Training_Project/UI/Widget/HUD/DNLobbyHUD.h"


void ADNLobbyHUD::NativeConstruct()
{

}
void ADNLobbyHUD::NativeDestruct()
{

}

void ADNLobbyHUD::BeginPlay()
{
	_hud_type = E_UI_HUD_TYPE::UHT_LOBBY_HUD;
	UE_LOG(LogTemp, Warning, TEXT("I set UHT_LOBBY [1]"));
	Super::BeginPlay();
}