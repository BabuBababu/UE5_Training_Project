


#include "UE5_Training_Project/UI/Widget/DNDamageIndicator.h"

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"



void UDNDamageIndicator::NativeConstruct()
{
	Super::NativeConstruct();
}


void UDNDamageIndicator::NativeDestruct()
{

	Super::NativeDestruct();
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

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("I Check Damage 3 ")));
}

void UDNDamageIndicator::show_indicator_handler(float damage_in, E_DAMAGE_TYPE type_in)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("I Check Damage 2 ")));
	if(nullptr == _umg_damage_text)
		return;

	//대미지 타입별로 이미지를 바꾼다거나 애니메이션을 바꾼다거나 그런걸 할 수 있음

	FString damage = FString::SanitizeFloat(damage_in);
	_umg_damage_text->SetText(FText::FromString(damage));


	// play animation
	play_animation(type_in);


}


void UDNDamageIndicator::add_function_handler(ADNCommonCharacter* character_in)
{

	if (nullptr == character_in)
		return;

	character_in->OnDamageIndicator.AddDynamic(this, &UDNDamageIndicator::show_indicator_handler);
	UE_LOG(LogTemp, Warning, TEXT("damage indicator add event!!!!"));
}

void UDNDamageIndicator::remove_function_handler(ADNCommonCharacter* character_in)
{
	if (nullptr == character_in)
		return;

	character_in->OnDamageIndicator.RemoveDynamic(this, &UDNDamageIndicator::show_indicator_handler);
	UE_LOG(LogTemp, Warning, TEXT("damage indicator remove event!!!!"));
}