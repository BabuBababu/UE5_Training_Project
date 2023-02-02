// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Engine
#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/InputComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/Controller.h>
#include <GameFramework/SpringArmComponent.h>
#include <Engine/Classes/Kismet/GameplayStatics.h>


// UE5_Training_Project_Setting
#include "UE5_Training_Project_Setting/Core/DNCharacterAssetSetting.h"

// Controller
#include "UE5_Training_Project/Controller/DNPlayerController.h"

// Component
#include "UE5_Training_Project/Character/Component/DNPlayerLineTrace.h"
#include "UE5_Training_Project/Character/Component/DNEnemyLineTrace.h"
#include <UE5_Training_Project/Component/DNStatusComponent.h>

// AnimInstance
#include "UE5_Training_Project/Character/Animation/DNCharacterAnimInstance.h"



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



	// 에셋 불러오기 테스트
	auto DefaultSetting = GetDefault<UDNCharacterAssetSetting>();
	if (DefaultSetting->_character_assets.Num() > 0)
	{
		for (auto character_asset : DefaultSetting->_character_assets)
		{
			UE_LOG(LogTemp,Warning, TEXT("Character Asset : %s"), *character_asset.ToString());
		}
	}
	//_character_position = E_CHARACTER_POSITION::CP_RUSH; // 우선은 테스트를 위해 전위로 둡니다.
	_position_index = 0;								 // 이것도 임의로 0으로 둠
}

void ADNCommonCharacter::BeginPlay()
{
	Super::BeginPlay();
	add_event();

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
}

void ADNCommonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

	if (_status->_current_ammo == _status->_chartacter_data->character_status_data.max_ammo)	//총알이 꽉찼다면 장전 불가능
		return;

	if (false == _is_armed_weapon)	//총을 들고 있지 않다면 장전 불가능
		return;

	if (_is_reloading == false)
	{
		_is_reloading = true;
		_character_state = E_CHARACTER_STATE::CS_RELOAD;
		UGameplayStatics::PlaySoundAtLocation(this, _reload_soundcue, AActor::GetActorLocation());
		OnReload.Broadcast();
	}

}

void ADNCommonCharacter::fire()
{
	// 플레이어는 해당 함수를 사용하지 않음
	// .075f는 데이터 테이블을 이용하여 캐릭터별로 다르게 설정할 예정
	//UE_LOG(LogTemp, Warning, TEXT("Doll Name : %s"), *this->GetClass()->GetDefaultObjectName().ToString());

	if (_is_reloading)			//장전중이면 사격 안됨
		return;

	if (_is_sprint)				//전력질주할때 사격 안됨
		return;

	if (false == _is_armed_weapon)	//총을 들고 있지 않으면 사격 안됨
		return;

	if (_status->get_current_ammo() == 0) //총알이 0발이면 사격 안됨
	{
		reload();
		return;
	}

	if (_is_fire)
	{
		_is_aiming = true;
		OnFire.Broadcast();
		UGameplayStatics::PlaySoundAtLocation(this, _fire_soundcue, AActor::GetActorLocation());

		if (_character_type != E_CHARACTER_TYPE::CT_ENEMY)
			_line_trace->OnFire(this);
		else if (_character_type == E_CHARACTER_TYPE::CT_ENEMY)
			_enemy_line_trace->OnFire(this);

		GetWorld()->GetTimerManager().SetTimer(_fire_timer, this, &ADNCommonCharacter::fire, _status->_chartacter_data->character_status_data.fire_speed, true);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Doll Attack Now"));
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
	_character_state = E_CHARACTER_STATE::CS_INTERACTION;
}


void ADNCommonCharacter::set_idle_animation()
{
	_is_aiming = false;
	_is_fire = false;
	_is_attacking = false;
}


void ADNCommonCharacter::destroy_object_handler()
{
	Destroy();
}

void ADNCommonCharacter::return_to_armed_handler()
{
	_is_reloading = false;
	// 장전이 끝났을때 기준 총을 들고있다면 그거에 맞춰서 들고 있어야하므로 armed함수와는 반대로 돌아감
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