

#pragma once

// Engine
#include <CoreMinimal.h>
#include <GameFramework/PlayerController.h>

// Generated
#include "DNLobbyController.generated.h"

/**
 *	로비에서 캐릭터 선택할 때 사용하게될 컨트롤러입니다.
 */
UCLASS()
class UE5_TRAINING_PROJECT_API ADNLobbyController : public APlayerController
{
	GENERATED_BODY()

public:
	ADNLobbyController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;
};
