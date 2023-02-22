// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Engine
#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/InputComponent.h>
#include <Components/WidgetComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/Controller.h>
#include <GameFramework/SpringArmComponent.h>
#include <Engine/Classes/Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>

// UE5_Training_Project_Setting
#include "UE5_Training_Project_Setting/Core/DNCharacterAssetSetting.h"

// Controller
#include "UE5_Training_Project/Controller/DNPlayerController.h"
#include "UE5_Training_Project/Controller/DNAIController.h"

// Component
#include "UE5_Training_Project/Character/Component/DNPlayerLineTrace.h"
#include "UE5_Training_Project/Character/Component/DNEnemyLineTrace.h"
#include <UE5_Training_Project/Component/DNStatusComponent.h>

// Item
#include "UE5_Training_Project/Actor/Item/DNCommonItem.h"

// Character
#include "UE5_Training_Project/Character/DNPlayerCharacter.h"

// AnimInstance
#include "UE5_Training_Project/Character/Animation/DNCharacterAnimInstance.h"

// UI
#include "UE5_Training_Project/UI/Widget/DNDamageIndicator.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"




ADNCommonCharacter::ADNCommonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;		// 이걸로 플레이어랑 컨트롤러랑 회전을 함께할지 결정 true면 컨트롤러의 회전과 함께 캐릭터도 회전합니다.
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	_default_max_speed = GetCharacterMovement()->MaxWalkSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Mesh
	_back_pack = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackPack"));
	_weapon_armed = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponArmed"));
	_weapon_un_armed = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponUnArmed"));
	_character_skeletal_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodySkeletalMesh"));


	_character_skeletal_mesh->SetupAttachment(RootComponent);

	_back_pack->SetupAttachment(_character_skeletal_mesh, TEXT("back_pack"));
	_weapon_armed->SetupAttachment(_character_skeletal_mesh, TEXT("weapon_r"));
	_weapon_un_armed->SetupAttachment(_character_skeletal_mesh, TEXT("weapon_unarmed"));


	// Create a camera boom (pulls in towards the player if there is a collision)
	_camera_boom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	_camera_boom->SetupAttachment(RootComponent);
	_camera_boom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	_camera_boom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	_follow_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	_follow_camera->SetupAttachment(_camera_boom); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	_follow_camera->bUsePawnControlRotation = true; // Camera does not rotate relative to arm

	// 위젯
	_damage_indicator_widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageIndicatorWidget"));
	_damage_indicator_widget->SetupAttachment(_character_skeletal_mesh);


	// 에셋 불러오기 테스트
	auto DefaultSetting = GetDefault<UDNCharacterAssetSetting>();
	if (DefaultSetting->_character_assets.Num() > 0)
	{
		for (auto character_asset : DefaultSetting->_character_assets)
		{
			//UE_LOG(LogTemp,Warning, TEXT("Character Asset : %s"), *character_asset.ToString());
		}
	}
	//_character_position = E_CHARACTER_POSITION::CP_RUSH; // 우선은 테스트를 위해 전위로 둡니다.
	_position_index = 0;								 // 이것도 임의로 0으로 둠
}

void ADNCommonCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 라인 트레이스 생성
	if (_line_trace == nullptr)
	{
		if(_character_type != E_CHARACTER_TYPE::CT_ENEMY)
			_line_trace = NewObject<UDNPlayerLineTrace>();

		else if(_character_type == E_CHARACTER_TYPE::CT_ENEMY)
			_enemy_line_trace = NewObject<UDNEnemyLineTrace>();
	}

	// 스테이터스 컴포넌트 생성
	if (_status == nullptr)
	{
		_status = NewObject<UDNStatusComponent>();
		_status->_character_id = _character_id;
		_status->init();
		_status->add_event(this);
	}

	OnAtStartAmmo.Broadcast(_status->_has_ammo);	//블랙보드 총알 등록
	add_event();									//기본 델리게이트 등록
	init_ui_event();								//이벤트 추가할 UI 델리게이트 등록

	_my_spawn_location = GetActorLocation();		//나중에 다시 스폰하기 위해 위치를 저장
}

void ADNCommonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 대미지 인디케이터를 항상 플레이어가 보는 방향으로 돌립니다.
	if (nullptr != _damage_indicator_widget)
	{
		ADNCommonCharacter* player = Cast<ADNCommonCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s"), *player->GetName()));

		if(nullptr != player)
			_damage_indicator_widget->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(_damage_indicator_widget->GetComponentLocation(), player->_camera_boom.Get()->GetComponentLocation()));
	}

}

void ADNCommonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ADNCommonCharacter::add_event()
{
	UDNCharacterAnimInstance* anim_instance = dynamic_cast<UDNCharacterAnimInstance*>(_character_skeletal_mesh->GetAnimInstance());
	if (nullptr == anim_instance)
		return;

	anim_instance->OnDieEnd.AddDynamic(this, &ADNCommonCharacter::destroy_object_handler);

	anim_instance->OnReloadEnd.AddDynamic(this, &ADNCommonCharacter::return_to_armed_handler);
	OnTargetDead.AddDynamic(this, &ADNCommonCharacter::reset_fire_state_handler);

	if (_character_type == E_CHARACTER_TYPE::CT_GRIFFIN)
	{
		_line_trace->OnTargetHit.AddDynamic(this, &ADNCommonCharacter::ammo_hit_handler);
	}
	else if (_character_type == E_CHARACTER_TYPE::CT_ENEMY)
	{
		_enemy_line_trace->OnTargetHit.AddDynamic(this, &ADNCommonCharacter::ammo_hit_handler);
	}
}



void ADNCommonCharacter::remove_event()
{

}


void ADNCommonCharacter::idle()
{
	_character_state = E_CHARACTER_STATE::CS_IDLE;

}

void ADNCommonCharacter::walk()
{

}

void ADNCommonCharacter::sprint()
{
	_is_sprint = true;
	GetCharacterMovement()->MaxWalkSpeed = _default_max_speed + 300.f;
}

void ADNCommonCharacter::stop_sprint()
{
	_is_sprint = false;
	GetCharacterMovement()->MaxWalkSpeed = _default_max_speed;
}


void ADNCommonCharacter::reload()
{
	if (_status->_has_ammo == 0)																//총알이 없다면 장전 불가능
		return;

	if (_status->_current_ammo == _status->_chartacter_data->character_status_data.max_ammo)	//총알이 꽉찼다면 장전 불가능
		return;

	if (false == _is_armed_weapon)																//총을 들고 있지 않다면 장전 불가능
		return;

	if (_is_reloading == false)
	{

		if (true == _is_near_wall)	//벽 근처에서 장전할 때 앉기
			_is_crouch = true;

		_is_reloading = true;
		_character_state = E_CHARACTER_STATE::CS_RELOAD;
		UGameplayStatics::PlaySoundAtLocation(this, _reload_soundcue,GetActorLocation());
		OnReload.Broadcast();
	}

}

void ADNCommonCharacter::fire()
{
	// 플레이어는 해당 함수를 사용하지 않음
	// .075f는 데이터 테이블을 이용하여 캐릭터별로 다르게 설정할 예정
	//UE_LOG(LogTemp, Warning, TEXT("Doll Name : %s"), *this->GetClass()->GetDefaultObjectName().ToString());

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Character::Fire"));

	if (_is_reloading)			//장전중이면 사격 안됨
		return;

	if (_is_sprint)				//전력질주할때 사격 안됨
		return;

	if (false == _is_armed_weapon)	//총을 들고 있지 않으면 사격 안됨
		return;

	if (_status->get_current_ammo() == 0) //총알이 0발이면 사격 안됨
	{
		if (_status->_has_ammo + _status->_current_ammo == 0)		// 남은 총알도 없을 경우
		{
			OnEmptyAmmo.Broadcast();
		}

		reload();
		return;
	}

	if (_target_change_current_ammo >= _target_change_limit_ammo)	//제한 총알 개수만큼 오사격을 했을 경우
	{
		_target_change_current_ammo = 0;
		OnStopShotAmmo.Broadcast();
		return;
	}


	if (_is_fire)
	{
		_is_aiming = true;
		OnFire.Broadcast();
		_target_change_current_ammo += 1;
		UGameplayStatics::PlaySoundAtLocation(this, _fire_soundcue, GetActorLocation());

		if (_character_type != E_CHARACTER_TYPE::CT_ENEMY)
			_line_trace->OnFire(this);
		else if (_character_type == E_CHARACTER_TYPE::CT_ENEMY)
			_enemy_line_trace->OnFire(this);

		GetWorld()->GetTimerManager().SetTimer(_fire_timer, this, &ADNCommonCharacter::fire, _status->_chartacter_data->character_status_data.fire_speed, true);
	}


}

void ADNCommonCharacter::stop_fire()
{
	_is_fire = false;
}


void ADNCommonCharacter::armed()
{
	if (_is_armed_weapon == false)
	{
		bUseControllerRotationYaw = true;
		_weapon_armed->SetVisibility(true);
		_weapon_un_armed->SetVisibility(false);
		_is_armed_weapon = true;
		_pre_upper_character_state = _character_state;
		_character_state = E_CHARACTER_STATE::CS_ARM;

	}
	else
	{
		bUseControllerRotationYaw = false;
		_weapon_armed->SetVisibility(false);
		_weapon_un_armed->SetVisibility(true);
		_is_armed_weapon = false;
		_character_state = _pre_upper_character_state;

		//SOUND_MANAGER->set_combat_flag(false);		//반대로
	}

}

void ADNCommonCharacter::crouch()
{
	if (_is_crouch == false)
	{
		_is_crouch = true;
	}
	else
	{
		_is_crouch = false;
	}


}

void ADNCommonCharacter::aiming()
{
	if (_is_reloading)			//장전중이면 안됨
		return;

	if (_is_armed_weapon == false)
		return;

	_is_aiming = true;
}

void ADNCommonCharacter::stop_aiming()
{
	_is_aiming = false;
}

void ADNCommonCharacter::interaction()
{
	//일단 임시방편으로 이렇게 작성 해둠. 함수 하나 만들어서 이름값이나 타입,ID값을 통해 기능을 넣을 예정
	if (false == _line_trace->_is_targeted)
		return;
	
	if (_line_trace->_item->_item_data->type == E_ITEM_TYPE::IT_AMMO)
	{
		_status->_has_ammo += _line_trace->_item->_item_data->count;
		OnItemPickup.Broadcast(_line_trace->_item);
	}

}


void ADNCommonCharacter::set_idle_animation()
{
	_is_aiming = false;
	_is_fire = false;
	_is_attacking = false;
}


void ADNCommonCharacter::destroy_object_handler()
{


	if(_character_type == E_CHARACTER_TYPE::CT_GRIFFIN)
		SOUND_MANAGER->play_meta_sound(E_SOUND_TYPE::ST_UI, 2);		//에이전트 다운

	SetActorLocation(_my_spawn_location);
	_status->reset();

	//SetActorHiddenInGame(true);
	//SetActorEnableCollision(false);

}

void ADNCommonCharacter::return_to_armed_handler()
{
	_is_reloading = false;
	// 장전이 끝났을때 기준 총을 들고있다면 그거에 맞춰서 들고 있어야하므로 armed함수와는 반대로 돌아감

	if(_character_type != E_CHARACTER_TYPE::CT_PLAYER)	//플레이어는 제외
		_is_crouch = false;

	if (_is_armed_weapon == false)
	{

		bUseControllerRotationYaw = false;
		_weapon_armed->SetVisibility(false);
		_weapon_un_armed->SetVisibility(true);
		_is_armed_weapon = false;
		_character_state = _pre_upper_character_state;

	}
	else
	{

		bUseControllerRotationYaw = true;
		_weapon_armed->SetVisibility(true);
		_weapon_un_armed->SetVisibility(false);
		_is_armed_weapon = true;
		_pre_upper_character_state = _character_state;
		_character_state = E_CHARACTER_STATE::CS_ARM;
	}
}

void ADNCommonCharacter::init_ui_event()
{
	UDNDamageIndicator* widget = Cast<UDNDamageIndicator>(_damage_indicator_widget->GetWidget());

	if (nullptr != widget)
		widget->add_function_handler(this);
}

void ADNCommonCharacter::remove_ui_event()
{
	UDNDamageIndicator* widget = Cast<UDNDamageIndicator>(_damage_indicator_widget->GetWidget());

	if (nullptr != widget)
		widget->remove_function_handler(this);
}

void ADNCommonCharacter::reset_fire_state_handler(ADNCommonCharacter* chracter_in)
{
	if (this == chracter_in)
	{
		set_idle_animation();
	}
}


void ADNCommonCharacter::ammo_hit_handler()
{
	_target_change_current_ammo = 0;
}