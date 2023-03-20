


#include "UE5_Training_Project/Character/DNLobbyCameraCharacter.h"

// Engine
#include <Components/SplineComponent.h>
#include <Engine/Classes/Kismet/GameplayStatics.h>
#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>


ADNLobbyCameraCharacter::ADNLobbyCameraCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;


	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;		// 이걸로 플레이어랑 컨트롤러랑 회전을 함께할지 결정 true면 컨트롤러의 회전과 함께 캐릭터도 회전합니다.
	bUseControllerRotationRoll = false;

	_spline_component = CreateDefaultSubobject<USplineComponent>(TEXT("SplineForMove"));
	_follow_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));

	_spline_component->SetupAttachment(RootComponent);


}

void ADNLobbyCameraCharacter::BeginPlay()
{
	Super::BeginPlay();
	_follow_camera->SetWorldLocation(_spline_component->GetComponentLocation());
	_follow_camera->SetWorldRotation(_spline_component->GetComponentRotation());
	
}	

void ADNLobbyCameraCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADNLobbyCameraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

