


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



ADNLobbyController::ADNLobbyController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}





void ADNLobbyController::BeginPlay()
{
	Super::BeginPlay();

}

void ADNLobbyController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
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


    // Check if an object was hit
    if (HitResult.bBlockingHit)
    {
        // Get a reference to the hit actor
        AActor* HitActor = HitResult.GetActor();
        if (HitActor)
        {
            // Do something with the hit actor, such as storing a reference to it
            UE_LOG(LogTemp, Warning, TEXT("Clicked on %s"), *HitActor->GetName());

            ADNPlayerCharacter* player = Cast<ADNPlayerCharacter>(HitActor);

            if (nullptr != player)
            {
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