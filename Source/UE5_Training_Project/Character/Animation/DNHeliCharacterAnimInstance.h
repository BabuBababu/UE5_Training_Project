

#pragma once


// Engine

#include <CoreMinimal.h>
#include <Animation/AnimInstance.h>

// Generated
#include "DNHeliCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE5_TRAINING_PROJECT_API UDNHeliCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UDNHeliCharacterAnimInstance();

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	float _rotor_mast_anim;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	float _rotor_back_anim;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	float _rotor_minigun_anim;
};
