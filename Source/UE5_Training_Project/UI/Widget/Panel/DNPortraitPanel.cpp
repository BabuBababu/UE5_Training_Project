


#include "UE5_Training_Project/UI/Widget/Panel/DNPortraitPanel.h"


UDNPortraitPanel::UDNPortraitPanel(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// 캐릭터 데이터 테이블 초기화
	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterDataObject(TEXT("/Game/Blueprint/Data/DT_DNCharacterData"));
	if (CharacterDataObject.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable Succeed!"));
		_character_datatable = CharacterDataObject.Object;
	}

	_chartacter_data = nullptr;
}

void UDNPortraitPanel::NativeConstruct()
{
	set_panel_type(E_UI_PANEL_TYPE::UPT_PORTRAIT);
	Super::NativeConstruct();

}

void UDNPortraitPanel::NativeDestruct()
{
	Super::NativeDestruct();

}




void UDNPortraitPanel::clear_panel()
{
	// 먼저 초기화
	if (IsValid(umg_normal_image) && IsValid(umg_die_image) && IsValid(umg_skill_cut_image))
	{
		umg_normal_image->SetBrushFromTexture(nullptr);
		umg_die_image->SetBrushFromTexture(nullptr);
		umg_skill_cut_image->SetBrushFromTexture(nullptr);
	}
}

void UDNPortraitPanel::init_data(int64 id_in)
{
	TArray<FDNCharacterData*> data_array;
	_character_datatable->GetAllRows<FDNCharacterData>("", data_array);

	for (auto& data : data_array)
	{
		if (data->character_id == id_in)
		{
			_chartacter_data = data;
		}
	}

	if (nullptr != _chartacter_data)
		set_image();
}


void UDNPortraitPanel::set_image()
{
	if (IsValid(umg_normal_image))
	{
		UTexture2D* texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *_chartacter_data->character_main_image_path));
		umg_normal_image->SetBrushFromTexture(texture);
	}

	if (IsValid(umg_die_image))
	{
		UTexture2D* texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *_chartacter_data->character_dead_image_path));
		umg_die_image->SetBrushFromTexture(texture);
	}

	// 스킬 사용 이미지는 일단 메인 이미지랑 동일하게 해둡니다. (마땅한 이미지가 없어서..)
	if (IsValid(umg_skill_cut_image))
	{
		UTexture2D* texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *_chartacter_data->character_main_image_path));
		umg_skill_cut_image->SetBrushFromTexture(texture);
	}
}

void UDNPortraitPanel::play_portrait_panel(int64 id_in, bool is_dead_in)
{
	init_data(id_in);

	if (IsValid(umg_main_image_animation) && IsValid(umg_die_image_animation))
	{
		if (is_dead_in)
		{
			if (false == IsAnimationPlaying(umg_die_image_animation))
				PlayAnimation(umg_die_image_animation);
		}
		else
		{
			if (false == IsAnimationPlaying(umg_main_image_animation))
				PlayAnimation(umg_main_image_animation);
		}
	}
}

void UDNPortraitPanel::add_event()
{

}


void UDNPortraitPanel::remove_event()
{

}