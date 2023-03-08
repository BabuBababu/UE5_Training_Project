


#include "UE5_Training_Project/UI/Widget/Panel/DNCommentPanel.h"



#define ISAC -1
#define NONE -1


UDNCommentPanel::UDNCommentPanel(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// 캐릭터 데이터 테이블 초기화
	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterDataObject(TEXT("/Game/Blueprint/Data/DT_DNCharacterData"));
	if (CharacterDataObject.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Character DataTable Succeed!"));
		_character_datatable = CharacterDataObject.Object;
	}

	// 캐릭터 대사용 테이블 하나 더 초기화해야할듯
	// 그리고 set_image_comment에서 대사를 따로 저장해야함
	static ConstructorHelpers::FObjectFinder<UDataTable> DialogDataObject(TEXT("/Game/Blueprint/Data/DT_DNDialogData"));
	if (DialogDataObject.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Dialog DataTable Succeed!"));
		_dialog_datatable = DialogDataObject.Object;
	}


	_chartacter_data = nullptr;
}

void UDNCommentPanel::NativeConstruct()
{
	set_panel_type(E_UI_PANEL_TYPE::UPT_COMMENT);
	Super::NativeConstruct();

}

void UDNCommentPanel::NativeDestruct()
{
	Super::NativeDestruct();

}

void UDNCommentPanel::clear_panel()
{
	// 먼저 초기화
	if (IsValid(umg_face_image) && IsValid(umg_comment_text))
	{
		umg_face_image->SetBrushFromTexture(nullptr);
		umg_comment_text->SetText(FText::FromString(""));
	}
}

void UDNCommentPanel::init_data(int64 id_in, int64 comment_id_in)
{
	TArray<FDNCharacterData*> data_array;
	_character_datatable->GetAllRows<FDNCharacterData>("", data_array);

	TArray<FDNCharacterDialogData*> dialog_data_array;
	_dialog_datatable->GetAllRows<FDNCharacterDialogData>("", dialog_data_array);


	//  부관
	if (id_in == ISAC)
	{
		for (auto& data : dialog_data_array)
		{
			if (data->character_id == id_in)
			{
				_dialog_data = data;
			}
		}

		set_image_comment_isac(comment_id_in);
	}
	else
	{
		for (auto& data : data_array)
		{
			if (data->character_id == id_in)
			{
				_chartacter_data = data;
			}
		}

		for (auto& data : dialog_data_array)
		{
			if (data->character_id == id_in)
			{
				_dialog_data = data;
			}
		}

		set_image_comment_character(comment_id_in);
	}
	

	
}

void UDNCommentPanel::set_image_comment_isac(int64 comment_id_in)
{
	if (IsValid(umg_comment_text))
	{
		// 코멘트 id를 가져와서 초기화합니다.
	}
}


void UDNCommentPanel::set_image_comment_character(int64 comment_id_in)
{
	if (IsValid(umg_face_image))
	{
		UTexture2D* texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *_chartacter_data->character_portrait_image_path));
		umg_face_image->SetBrushFromTexture(texture);
	}

	if (IsValid(umg_comment_text))
	{

	}
}

void UDNCommentPanel::play_comment_isac(int64 comment_id_in)
{
	clear_panel();
	init_data(ISAC, comment_id_in);

	if (IsValid(umg_show_comment_animation))
	{
		PlayAnimation(umg_show_comment_animation);
	}
	
}

void UDNCommentPanel::play_comment_character(int64 id_in, int64 comment_id_in)
{
	clear_panel();
	init_data(id_in, comment_id_in);

	if (IsValid(umg_show_comment_animation))
	{
		if (false == IsAnimationPlaying(umg_show_comment_animation))
			PlayAnimation(umg_show_comment_animation);
	}
	
}




void UDNCommentPanel::add_event()
{

}


void UDNCommentPanel::remove_event()
{

}