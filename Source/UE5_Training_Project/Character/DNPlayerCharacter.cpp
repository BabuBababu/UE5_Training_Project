


#include "UE5_Training_Project/Character/DNPlayerCharacter.h"

// Engine
#include <Engine/Classes/Kismet/GameplayStatics.h>
#include <Components/WidgetComponent.h>

// Controller
#include "UE5_Training_Project/Controller/DNPlayerController.h"

// Character
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"

// Component
#include "UE5_Training_Project/Character/Component/DNPlayerLineTrace.h"
#include "UE5_Training_Project/Component/DNStatusComponent.h"

// Actor
#include "UE5_Training_Project/Actor/Wall/DNCommonWall.h"

// Manager
#include "UE5_Training_Project/Manager/DNSoundManager.h"
#include "UE5_Training_Project/Manager/DNObjectManager.h"
// UI
#include "UE5_Training_Project/UI/Widget/Panel/DNInteractionPanel.h"
#include "UE5_Training_Project/UI/Widget/DNDamageIndicator.h"


void ADNPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	OBJECT_MANAGER->_player = this;
	OBJECT_MANAGER->_griffin_player_array.Add(this);

	if (_spawn_level_type == E_CHARACTER_SPAWN_LEVEL_TYPE::CSLT_LOBBY)
		SOUND_MANAGER->_can_play = false;




}

void ADNPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	_line_trace->OnInteraction(this);


	
}


void ADNPlayerCharacter::start_fire()
{
	_is_fire = true;
	fire();

	
}


void ADNPlayerCharacter::reload()
{
	if (_status->_has_ammo == 0)																//총알이 없다면 장전 불가능
		return;

	if (_status->_current_ammo == _status->_chartacter_data->character_status_data.max_ammo)	//총알이 꽉찼다면 장전 불가능
		return;

	if (false == _is_armed_weapon)																//총을 들고 있지 않다면 장전 불가능
		return;

	if (_is_reloading == false)
	{

		_is_reloading = true;
		//_character_state = E_CHARACTER_STATE::CS_RELOAD;
		UGameplayStatics::PlaySoundAtLocation(this, _reload_soundcue, GetActorLocation());
		OnReload.Broadcast();
	}

}


void ADNPlayerCharacter::fire()
{
	if (_is_reloading)			//장전중이면 사격 안됨
		return;

	if (_is_sprint)				//전력질주할때 사격 안됨
		return;

	if (false == _is_armed_weapon)	//총을 들고 있지 않으면 사격 안됨
		return;

	if (_status->get_current_ammo() == 0) //총알이 0발이면 사격 안됨
		return;

	if (false ==  _is_aiming) //조준하고 있지않으면 사격 안됨
		return;

	if (nullptr != _near_wall)
	{
		if (_near_wall->_wall_type == E_WALL_TYPE::WT_HIGH)	//높은벽에 엄폐할 때 좌우가 아니면 사격 안됨
		{
			if (false == _cover_left && false == _cover_right)
				return;
		}
	}

	if (_is_fire)
	{
		_line_trace->OnFire(this);
		OnFire.Broadcast();
		ADNPlayerController* controller = dynamic_cast<ADNPlayerController*>(GetController());
		UGameplayStatics::PlaySoundAtLocation(this, _fire_soundcue, GetActorLocation());
		if (controller->get_camera_shake() != nullptr)
			controller->ClientStartCameraShake(controller->get_camera_shake());




		GetWorld()->GetTimerManager().SetTimer(_fire_timer, this, &ADNCommonCharacter::fire, _status->_chartacter_data->character_status_data.fire_speed, true);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Character::Fire"));

	}

}

void ADNPlayerCharacter::wall_jump()
{
	// 커버중에는 불가능
	if (_cover_now)
		return;

	if (_near_wall->_wall_type == E_WALL_TYPE::WT_HIGH)
		return;

	_is_wall_jump = true;
	OnWallJump.Broadcast();
}

void ADNPlayerCharacter::armed()
{
	Super::armed();

	player_arm_event(_is_armed_weapon);
}


void ADNPlayerCharacter::crouch()
{
	Super::crouch();
	player_crouch_event(_is_crouch);
}


void ADNPlayerCharacter::sprint()
{
	Super::sprint();
	player_sprint_event(_is_sprint);
}

void ADNPlayerCharacter::stop_sprint()
{
	Super::stop_sprint();
	player_sprint_event(_is_sprint);
}



void ADNPlayerCharacter::aiming()
{
	Super::aiming();

	//카메라 시점 및 속도를 변경합니다.

	
	if (_cover_now)
	{
		if (GetVelocity().Length() > 0.f)		//엄폐 + 이동중이면 조준 불가
			_is_aiming = false;

		if(_cover_left)
			_camera_boom->SetRelativeTransform(set_left_cover_camera_transform(true));
		else if (_cover_right)
			_camera_boom->SetRelativeTransform(set_right_cover_camera_transform(true));
		else if (false == _cover_left && false == _cover_right)
			_camera_boom->SetRelativeTransform(set_center_cover_camera_transform(true));

	}
	else
	{
		_camera_boom->SetRelativeTransform(set_camera_transform(true));
		GetCharacterMovement()->MaxWalkSpeed = _aiming_max_walk_speed;
	}

	_line_trace->OnAiming(this);

}

void ADNPlayerCharacter::stop_aiming()
{
	Super::stop_aiming();

	
	if (_cover_now)
	{
		if (_cover_left)
			_camera_boom->SetRelativeTransform(set_left_cover_camera_transform(false));
		else if (_cover_right)
			_camera_boom->SetRelativeTransform(set_right_cover_camera_transform(false));
		else if (false == _cover_left && false == _cover_right)
			_camera_boom->SetRelativeTransform(set_center_cover_camera_transform(false));
	}
	else
	{
		_camera_boom->SetRelativeTransform(set_camera_transform(false));
		if (_is_sprint)
			GetCharacterMovement()->MaxWalkSpeed = _sprint_max_walk_speed;
		else
			GetCharacterMovement()->MaxWalkSpeed = _default_max_speed;
	}


}

void ADNPlayerCharacter::cover()
{
	Super::cover();
}


FTransform ADNPlayerCharacter::set_camera_transform(bool flag_in)
{
	// 카메라와 뷰포트 거리 , 좌우, 높이
	const FVector OriginLocation(50.f, 90.f, 25.f);
	const FRotator OriginCameraRotation(0.f, 0.f, 0.f);
	const FVector OriginCameraScale(1.f, 1.f, 1.f);

	// 카메라가 바라보는 방향 기준
	FRotator rotate = _follow_camera->GetComponentRotation();
	FVector roatate_vector = FRotator(rotate.Pitch, 0.f, 0.f).Vector();

	FVector AimCameraLocation = OriginLocation + roatate_vector * 100.f + FVector(0.f, 0.f, 0.f);



	const FTransform AimCameraTransform(OriginCameraRotation, AimCameraLocation, OriginCameraScale);
	const FTransform OriginCameraTransform(OriginCameraRotation, OriginLocation, OriginCameraScale);

	if (true != flag_in)
		return OriginCameraTransform;

	return AimCameraTransform;
}

FTransform ADNPlayerCharacter::set_center_cover_camera_transform(bool flag_in)
{
	
	// 카메라와 뷰포트 거리 , 좌우, 높이
	const FVector OriginLocation(100.f, 90.f, 0.f);
	const FRotator OriginCameraRotation(0.f, 0.f, 0.f);
	const FVector OriginCameraScale(1.f, 1.f, 1.f);

	// 카메라가 바라보는 방향 기준
	FRotator rotate = _follow_camera->GetComponentRotation();
	FVector roatate_vector = FRotator(rotate.Pitch, 0.f, 0.f).Vector();
	//200 30 -15
	FVector AimCameraLocation = OriginLocation + roatate_vector * 100.f + FVector(0.f, -45.f, 0.f);



	const FTransform AimCameraTransform(OriginCameraRotation, AimCameraLocation, OriginCameraScale);
	const FTransform OriginCameraTransform(OriginCameraRotation, OriginLocation, OriginCameraScale);

	if (true != flag_in)
		return OriginCameraTransform;

	return AimCameraTransform;
}


FTransform ADNPlayerCharacter::set_left_cover_camera_transform(bool flag_in)
{

	// 카메라와 뷰포트 거리 , 좌우, 높이
	const FVector OriginLocation(100.f, 90.f, 0.f);
	const FRotator OriginCameraRotation(0.f, 0.f, 0.f);
	const FVector OriginCameraScale(1.f, 1.f, 1.f);

	// 카메라가 바라보는 방향 기준
	FRotator rotate = _follow_camera->GetComponentRotation();
	FVector roatate_vector = FRotator(rotate.Pitch, 0.f, 0.f).Vector();

	FVector AimCameraLocation = OriginLocation + roatate_vector * 100.f + FVector(0.f, -135.f, 0.f); //z값 -55.f였음



	const FTransform AimCameraTransform(OriginCameraRotation, AimCameraLocation, OriginCameraScale);
	const FTransform OriginCameraTransform(OriginCameraRotation, OriginLocation, OriginCameraScale);

	if (true != flag_in)
		return OriginCameraTransform;

	return AimCameraTransform;
}



FTransform ADNPlayerCharacter::set_right_cover_camera_transform(bool flag_in)
{

	// 카메라와 뷰포트 거리 , 좌우, 높이
	const FVector OriginLocation(100.f, 90.f, 0.f);
	const FRotator OriginCameraRotation(0.f, 0.f, 0.f);
	const FVector OriginCameraScale(1.f, 1.f, 1.f);

	// 카메라가 바라보는 방향 기준
	FRotator rotate = _follow_camera->GetComponentRotation();
	FVector roatate_vector = FRotator(rotate.Pitch, 0.f, 0.f).Vector();
	//200 30 -15
	FVector AimCameraLocation = OriginLocation + roatate_vector * 100.f + FVector(0.f, -45.f, 0.f);



	const FTransform AimCameraTransform(OriginCameraRotation, AimCameraLocation, OriginCameraScale);
	const FTransform OriginCameraTransform(OriginCameraRotation, OriginLocation, OriginCameraScale);

	if (true != flag_in)
		return OriginCameraTransform;

	return AimCameraTransform;
}




void ADNPlayerCharacter::order_move(FVector destination_in, ADNUnEnemyCharacter* doll_in)
{
	OnOrderMove.Broadcast(destination_in, doll_in);
	for (auto& doll : OBJECT_MANAGER->_in_squad_doll_array)
	{
		if (doll.Value == doll_in)
			doll.Value->OnOrdered.Broadcast(true);
	}
}


void ADNPlayerCharacter::order_attack(ADNEnemyCharacter* enemy_in, ADNUnEnemyCharacter* doll_in)
{
	OnOrderAttack.Broadcast(enemy_in, doll_in);
	for (auto& doll : OBJECT_MANAGER->_in_squad_doll_array)
	{
		if (doll.Value == doll_in)
			doll.Value->OnOrdered.Broadcast(true);
	}
}


void ADNPlayerCharacter::player_arm_event(bool armed_in)
{
	on_armed.Broadcast(armed_in);
	for (auto& doll : OBJECT_MANAGER->_in_squad_doll_array)
	{
		if(nullptr != doll.Value)
			doll.Value->OnArmed.Broadcast(armed_in);
	}
}

void ADNPlayerCharacter::player_crouch_event(bool crouch_in)
{
	//on_crouch.Broadcast(crouch_in);		일단 기능을 꺼둡니다. 플레이어가 숙일 때 다른 인형들도 숙이는 기능
}

void ADNPlayerCharacter::player_sprint_event(bool sprint_in)
{
	on_sprint.Broadcast(sprint_in);
}


void ADNPlayerCharacter::init_ui_event()
{

	 //인터렉션 위젯 
	UDNBasePanel* base_panel = WIDGET_MANAGER->get_panel(E_UI_PANEL_TYPE::UPT_INTERACTION);
	if (nullptr == base_panel)
		return;

	UDNInteractionPanel* panel = dynamic_cast<UDNInteractionPanel*>(base_panel);
	if (nullptr == panel)
		return;

	panel->add_function_handler(this->_line_trace);


}

void ADNPlayerCharacter::remove_ui_event()
{
	//인터렉션 위젯 
	UDNBasePanel* base_panel = WIDGET_MANAGER->get_panel(E_UI_PANEL_TYPE::UPT_INTERACTION);
	if (nullptr == base_panel)
		return;

	UDNInteractionPanel* panel = dynamic_cast<UDNInteractionPanel*>(base_panel);
	if (nullptr == panel)
		return;

	panel->remove_function_handler(this->_line_trace);

	Super::remove_ui_event();
}