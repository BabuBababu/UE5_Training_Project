


#include "UE5_Training_Project/UI/Base/DNBaseComponent.h"


// Engine
#include <Blueprint/WidgetBlueprintLibrary.h>
#include <Components/SizeBox.h>




void UDNBaseComponent::NativePreConstruct()
{
	Super::NativePreConstruct();

	update_component();
}

void UDNBaseComponent::NativeConstruct()
{
	Super::NativeConstruct();

	add_component_event();

	init_component();
}

void UDNBaseComponent::NativeDestruct()
{
	remove_component_event();

	Super::NativeDestruct();
}

void UDNBaseComponent::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}



void UDNBaseComponent::init_component()
{
	update_component();
}

void UDNBaseComponent::update_component()
{
	native_component_enabled(is_component_enabled);
	set_component_size(component_size);
	set_component_index(component_index);
}


void UDNBaseComponent::native_component_enabled(bool is_enabled_in)
{
	is_component_enabled = is_enabled_in;

	if (false == IsValid(umg_size_box)) return;

	if (!is_component_enabled)
	{
		umg_size_box->SetRenderOpacity(0.6f);
		umg_size_box->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		umg_size_box->SetRenderOpacity(1.0f);
		umg_size_box->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}


void UDNBaseComponent::set_is_component_enabled(bool is_enabled_in)
{
	native_component_enabled(is_enabled_in);
}

void UDNBaseComponent::set_component_size(FVector2D size_in)
{
	component_size = size_in;

	if (component_size.IsZero())
	{
		component_auto_size = true;
	}

	if (component_auto_size)
	{
		if (true == IsValid(umg_size_box))
		{
			umg_size_box->ClearWidthOverride();
			umg_size_box->ClearHeightOverride();
		}
	}
	else
	{
		if (true == IsValid(umg_size_box))
		{
			if (component_size.X <= 0.0f)
			{
				umg_size_box->ClearWidthOverride();
			}
			else
			{
				umg_size_box->SetWidthOverride(component_size.X);
			}

			if (component_size.Y <= 0.0f)
			{
				umg_size_box->ClearHeightOverride();
			}
			else
			{
				umg_size_box->SetHeightOverride(component_size.Y);
			}
		}
	}
}