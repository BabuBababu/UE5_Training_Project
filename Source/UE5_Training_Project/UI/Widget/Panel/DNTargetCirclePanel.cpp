


#include "UE5_Training_Project/UI/Widget/Panel/DNTargetCirclePanel.h"

// Engine
#include "Materials/MaterialInstanceDynamic.h"

// Controller
#include "UE5_Training_Project/Controller/DNPlayerController.h"

// Actor
#include "UE5_Training_Project/Actor/DNPatternTargetActor.h"


void UDNTargetCirclePanel::NativeConstruct()
{
	set_panel_type(E_UI_PANEL_TYPE::UPT_TARGET_CIRCLE);
	Super::NativeConstruct();
	init();
}

void UDNTargetCirclePanel::NativeDestruct()
{
	Super::NativeDestruct();

}

void UDNTargetCirclePanel::add_event()
{
	Super::add_event();

}

void UDNTargetCirclePanel::remove_event()
{
	Super::remove_event();

}

void UDNTargetCirclePanel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// 위치 동기화
	//sync_position();

	// 시간 동기화
	set_time_percent(_current_time);

	// HP 동기화
	set_hp_percent(_current_hp);

	// 시간 계산
	_current_time -= InDeltaTime;
	if (_current_time <= 0)
	{
		init();
		SetVisibility(ESlateVisibility::Collapsed);	//시간이 다 되었으니 틱은 더이상 작동되면 안되므로
	}
}

void UDNTargetCirclePanel::set_widget(ADNPatternTargetActor* owner_in)
{
	if (false == IsValid(owner_in))
	{
		init();
		SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	if (false == IsValid(umg_main_overlay))
		return;

	if (false == IsValid(umg_target_time_circle_icon))
		return;

	if (false == IsValid(umg_target_circle_icon))
		return;


	_owner = owner_in;

	// 시간
	_max_time = owner_in->get_limit_max_time();
	_current_time = _owner->get_limit_current_time();

	// HP
	_max_hp = owner_in->get_max_hp();
	_current_hp = _owner->get_current_hp();

	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Current HP : %f"), _current_hp));

	if(_current_hp > 0)  // 살아 있을 경우
		SetVisibility(ESlateVisibility::HitTestInvisible);
	else
	{
		init();
		SetVisibility(ESlateVisibility::Collapsed);
	}

}

void UDNTargetCirclePanel::close_widget()
{
	SetVisibility(ESlateVisibility::Hidden);	//틱은 정상작동 되야하므로
}

void UDNTargetCirclePanel::set_time_percent(float time_in)
{
	float percent = time_in / _max_time;


	UMaterialInstanceDynamic* material = umg_target_time_circle_icon->GetDynamicMaterial();
	if (IsValid(material))
	{
		material->SetScalarParameterValue("percent", percent);
	}

	
}

void UDNTargetCirclePanel::set_hp_percent(float hp_in)
{
	float percent = hp_in / _max_hp;

	UMaterialInstanceDynamic* material = umg_target_circle_icon->GetDynamicMaterial();
	if (IsValid(material))
	{
		material->SetScalarParameterValue("percent", percent);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), percent));
	}

}

void UDNTargetCirclePanel::init()
{
	_max_time = 0.f;
	_current_time = 0.f;
	_current_hp = 0.f;
	_max_hp = 0.f;
	_owner = nullptr;
	close_widget();
}

void UDNTargetCirclePanel::play_hit_animation()
{
	if (nullptr != umg_hit_animation)
	{
		PlayAnimation(umg_hit_animation);
	}
}

//
//void UDNTargetCirclePanel::sync_position()
//{
//	// 플레이어 컨트롤러 가져오기
//	APlayerController* controller = GetWorld()->GetFirstPlayerController();
//	if (false == IsValid(controller))
//		return;
//
//	ADNPlayerController* player_controller = Cast<ADNPlayerController>(controller);
//	if (false == IsValid(player_controller))
//		return;
//
//	if (false == IsValid(_owner))
//	{
//		init();
//		SetVisibility(ESlateVisibility::Collapsed);
//		return;
//	}
//
//	// 뷰포트 사이즈 재설정
//	set_viewport_size();
//
//	// 대상의 3D 위치를 2D 뷰포트 좌표로 변환
//	FVector2D ScreenLocation;
//	if (UGameplayStatics::ProjectWorldToScreen(player_controller, _owner->GetActorLocation(), ScreenLocation))
//	{
//		if (false == IsValid(umg_main_overlay))
//			return;
//		UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(umg_main_overlay->Slot);
//
//		if (IsValid(slot))
//		{
//			FVector2D new_location;
//			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), _current_width));
//			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), _current_height));
//
//			
//
//			new_location.X = ScreenLocation.X - (_current_width / 2);
//			new_location.Y = ScreenLocation.Y - (_current_height / 2);
//
//			slot->SetPosition(new_location);
//			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Screen : %s"), *ScreenLocation.ToString()));
//			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Result : %s"), *new_location.ToString()));
//		}
//	
//	}
//}
//
//void UDNTargetCirclePanel::set_viewport_size()
//{
//	// 플레이어 컨트롤러 가져오기
//	APlayerController* controller = GetWorld()->GetFirstPlayerController();
//	if (false == IsValid(controller))
//		return;
//
//	ADNPlayerController* player_controller = Cast<ADNPlayerController>(controller);
//	if (false == IsValid(player_controller))
//		return;
//
//	// 뷰포트 크기 가져오기
//	int32 ViewportSizeX, ViewportSizeY;
//	player_controller->GetViewportSize(ViewportSizeX, ViewportSizeY);
//
//	// ViewportSize에 현재 해상도 값이 저장됩니다.
//	_current_width = ViewportSizeX;
//	_current_height = ViewportSizeY;
//}