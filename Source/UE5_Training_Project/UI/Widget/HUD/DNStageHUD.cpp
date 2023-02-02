


#include "UE5_Training_Project/UI/Widget/HUD/DNStageHUD.h"


void ADNStageHUD::NativeConstruct()
{

}
void ADNStageHUD::NativeDestruct()
{

}

void ADNStageHUD::BeginPlay()
{
	_hud_type = E_UI_HUD_TYPE::UHT_COMBAT_HUD;
	UE_LOG(LogTemp, Warning, TEXT("I set UHT_Play [1]"));
	Super::BeginPlay();
}