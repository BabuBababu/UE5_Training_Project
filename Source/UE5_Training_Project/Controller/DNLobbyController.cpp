


#include "UE5_Training_Project/Controller/DNLobbyController.h"

// Engine
#include <Engine/World.h>
#include <DrawDebugHelpers.h>
#include <Kismet/GameplayStatics.h>


// EnhancedInput
#include "EnhancedInput/Public/InputMappingContext.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "EnhancedInput/Public/InputActionValue.h"

// Character
#include "UE5_Training_Project/Character/DNPlayerCharacter.h"

// Controller
#include "UE5_Training_Project/Controller/DNPlayerController.h"

// HUD
#include "UE5_Training_Project/UI/Widget/HUD/DNStageHUD.h"

// Animation
#include "UE5_Training_Project/Character/Animation/DNLobbyCharacterAnimInstance.h"

// GameMode
#include "UE5_Training_Project/GameMode/DNLobbyGameMode.h"



ADNLobbyController::ADNLobbyController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
    _lobby_character = nullptr;
}





void ADNLobbyController::BeginPlay()
{
	Super::BeginPlay();

}

void ADNLobbyController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

    if (nullptr == _lobby_character)
        return;

    auto* anim = _lobby_character->_character_skeletal_mesh->GetAnimInstance();
    if (nullptr == anim)
        return;
    UDNLobbyCharacterAnimInstance* anim_instance = Cast<UDNLobbyCharacterAnimInstance>(anim);
    if (nullptr != anim_instance)
    {
        if (true == anim_instance->OnWalkingEnd.IsBound())
            anim_instance->OnWalkingEnd.RemoveDynamic(this, &ADNLobbyController::change_controller_character_handler);
        
        // 걷기 델리게이트 제거
        anim_instance->remove_event();
    }

}

void ADNLobbyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ADNLobbyController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Get the local player subsystem
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    // Clear out existing mapping, and add our mapping
    Subsystem->ClearAllMappings();
    Subsystem->AddMappingContext(InputMapping, 0);

    // Get the EnhancedInputComponent
    UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(InputComponent);

    // Bind the actions

    // Completed : 눌렀다 뗐을 때, Triggered : 누르고 있을 때 
    PEI->BindAction(InputActions->InputClick, ETriggerEvent::Completed, this, &ADNLobbyController::OnMouseClicked);

}



void ADNLobbyController::OnMouseClicked()
{

   

    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);

    GetHitResultUnderCursor(ECC_Visibility, false, HitResult);


    if (HitResult.bBlockingHit)
    {
        AActor* HitActor = HitResult.GetActor();
        if (HitActor)
        {
            UE_LOG(LogTemp, Warning, TEXT("Clicked on %s"), *HitActor->GetName());

            ADNPlayerCharacter* player = Cast<ADNPlayerCharacter>(HitActor);

            if (nullptr != player)
            {
                // 사용하게될 로비 캐릭터를 넣어줍니다.
                _lobby_character = player;

                // 애님인스턴스를 찾고 델리게이트 바인딩 체크를 한 다음 바인딩을 해줍니다.
                auto * anim = _lobby_character->_character_skeletal_mesh->GetAnimInstance();

                if (nullptr == anim)
                    return;
                UDNLobbyCharacterAnimInstance* anim_instance = Cast<UDNLobbyCharacterAnimInstance>(anim);
                if (nullptr != anim_instance)
                {
                    if (false == anim_instance->OnWalkingEnd.IsBound())
                        anim_instance->OnWalkingEnd.AddDynamic(this, &ADNLobbyController::change_controller_character_handler);

                    // 걷기 애니메이션을 위한 델리게이트 추가합니다.  캐릭터 생성->UI생성순이어서  add_event가 내부에서 실행되지않아 여기에서 다시 실행합니다.
                    anim_instance->add_event();
                }



                // 선택과 비선택에 따라  로비셀렉트 버튼에 신호를 보냅니다.
                if (player->_is_selected)
                {
                    player->_is_selected = false;
                    OnSelected.Broadcast(player->_is_selected);
                }
                else
                {
                    player->_is_selected = true;
                    OnSelected.Broadcast(player->_is_selected);
                }
            }
        }
    }
}

void ADNLobbyController::change_controller_character_handler()
{
    _lobby_character->_lobby_finished = true;
    
    // 애니메이션 동작이 끝났다면 레벨을 바꿔줍니다.
    UGameplayStatics::OpenLevel(this, "L_PlayerBase");




    // 애니메이션 동작이 끝났다면 컨트롤러와 캐릭터를 변경합니다.
    /*auto* GameMode = GetWorld()->GetAuthGameMode();

    if (nullptr == _change_character)
        return;
    if (nullptr == _change_controller)
        return;
    if (nullptr == _change_hud)
        return;

    if (nullptr != GameMode)
    {
        GameMode->DefaultPawnClass = _change_character;
        GameMode->PlayerControllerClass = _change_controller;
        GameMode->HUDClass = _change_hud;
    }*/
}