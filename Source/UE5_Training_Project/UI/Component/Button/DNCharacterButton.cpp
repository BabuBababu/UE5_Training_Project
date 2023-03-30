


#include "UE5_Training_Project/UI/Component/Button/DNCharacterButton.h"




void UDNCharacterButton::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDNCharacterButton::NativeDestruct()
{
	Super::NativeDestruct();
}

void UDNCharacterButton::add_event()
{
	Super::add_event();
}

void UDNCharacterButton::remove_event()
{
	Super::remove_event();
}

void UDNCharacterButton::init()
{
	if (nullptr == _character_data)
		return;

	set_character_texture();
	set_character_text();
}


void UDNCharacterButton::set_character_texture()
{

	if (IsValid(umg_character_image))
	{
		UTexture2D* texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *_character_data->character_portrait_image_path));
		if (nullptr != texture)
		{
			umg_character_image->SetBrushFromTexture(texture);
		}
	}

	
}

void UDNCharacterButton::set_character_text()
{
	if (IsValid(umg_character_text))
	{
		umg_character_text->SetText(FText::FromString(_character_data->character_name));
	}
}