// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Engine
#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/InputComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/Controller.h>
#include <GameFramework/SpringArmComponent.h>

// UE5_Training_Project_Setting
#include "UE5_Training_Project_Setting/Core/DNCharacterAssetSetting.h"

// Controller
#include "UE5_Training_Project/Controller/DNPlayerController.h"

// Component
#include "UE5_Training_Project/Character/Component/DNPlayerLineTrace.h"



// Sets default values
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

// Called when the game starts or when spawned
void ADNCommonCharacter::BeginPlay()
{
	Super::BeginPlay();
	

	// 라인 트레이스 생성
	if (_line_trace == nullptr)
	{
		_line_trace = NewObject<UDNPlayerLineTrace>();
	}
}

// Called every frame
void ADNCommonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADNCommonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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
	if (_is_reloading == false)
	{
		_is_reloading = true;
		_character_state = E_CHARACTER_STATE::CS_RELOAD;
	}

	// 장전이 끝나면 armed상태로 가야함
}

void ADNCommonCharacter::fire()
{
	// 플레이어는 해당 함수를 사용하지 않음
	// .075f는 데이터 테이블을 이용하여 캐릭터별로 다르게 설정할 예정
	//UE_LOG(LogTemp, Warning, TEXT("Doll Name : %s"), *this->GetClass()->GetDefaultObjectName().ToString());

	if (_is_armed_weapon == false)
		return;

	if (_is_fire)
	{
		_is_aiming = true;
		_line_trace->OnFire(this);

		GetWorld()->GetTimerManager().SetTimer(_fire_timer, this, &ADNCommonCharacter::fire, 0.1f, true);
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