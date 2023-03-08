


#include "UE5_Training_Project/UI/Widget/DNDamageIndicator.h"

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"



void UDNDamageIndicator::NativeConstruct()
{
	set_panel_type(E_UI_PANEL_TYPE::UPT_DAMAGE_INDICATOR);

	Super::NativeConstruct();
}


void UDNDamageIndicator::NativeDestruct()
{

	Super::NativeDestruct();
}

void UDNDamageIndicator::add_event()
{

}

void UDNDamageIndicator::remove_event()
{

}


void UDNDamageIndicator::play_animation(E_DAMAGE_TYPE type_in)
{
	if (type_in == E_DAMAGE_TYPE::DT_NORMAL)
	{
		if (nullptr != umg_show_damage_normal)
		{
			PlayAnimation(umg_show_damage_normal);
		}
	}
	else if (type_in == E_DAMAGE_TYPE::DT_CRITICAL)
	{
		if (nullptr != umg_show_damage_critical)
		{
			PlayAnimation(umg_show_damage_critical);
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("I Check Damage 3 ")));
}

void UDNDamageIndicator::show_indicator(float damage_in, E_DAMAGE_TYPE type_in)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("I Check Damage 2 ")));
	if(nullptr == umg_damage_text)
		return;

	//대미지 타입별로 이미지를 바꾼다거나 애니메이션을 바꾼다거나 그런걸 할 수 있음

	int damage_int = damage_in;
	FString damage = FString::FromInt(damage_int);

	// 위치 랜덤 조정
	float rand_x = FMath::FRandRange(-15.f, 15.f);
	float rand_y = FMath::FRandRange(-15.f, 15.f);
	FVector2D position = FVector2D(rand_x, rand_y);

	umg_damage_text->SetText(FText::FromString(damage));

	UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(Slot);
	slot->SetPosition(position);


	// play animation
	play_animation(type_in);


}
