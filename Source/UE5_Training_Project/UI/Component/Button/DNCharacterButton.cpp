


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

	if (IsValid(umg_button))
		umg_button->OnClicked.AddDynamic(this, &UDNCharacterButton::click_button_handler);
}

void UDNCharacterButton::remove_event()
{

	if (IsValid(umg_button))
		umg_button->OnClicked.RemoveDynamic(this, &UDNCharacterButton::click_button_handler);

	Super::remove_event();
}

void UDNCharacterButton::init()
{
	if (_character_data->character_id == -1)
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


void UDNCharacterButton::click_button_handler()
{
	OnClickCharacterDataButton.Broadcast(*_character_data);
	OnClickCharacterButton.Broadcast();
}