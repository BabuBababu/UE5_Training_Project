

#pragma once

// Engine
#include <CoreMinimal.h>
#include <GameFramework/Character.h>

// Generated
#include "DNLobbyCameraCharacter.generated.h"



class USplineComponent;
class UCameraComponent;

UCLASS()
class UE5_TRAINING_PROJECT_API ADNLobbyCameraCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADNLobbyCameraCharacter();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	TObjectPtr<UCameraComponent> _follow_camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	TObjectPtr<USplineComponent> _spline_component;


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
