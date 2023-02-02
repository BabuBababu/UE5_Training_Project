

#pragma once


// Engine
#include <CoreMinimal.h>
#include <Animation/AnimInstance.h>

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// generated
#include "DNCharacterAnimInstance.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMontageEndDelegate);


/**
 * 
 */

class UAnimMontage;
class ADNCommonCharacter;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UDNCharacterAnimInstance();

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void add_event();
	void remove_event();

public:
	FOnMontageEndDelegate OnDieEnd;
	FOnMontageEndDelegate OnReloadEnd;

public:
	UFUNCTION(BlueprintCallable)
	void on_die_montage_ended();

	UFUNCTION(BlueprintCallable)
	void on_reload_montage_ended();

public:
	UFUNCTION(BlueprintCallable)
	void calculate_speed_direction(APawn* pawn_in);

	UFUNCTION(BlueprintCallable)
	void play_reload_montage();

	UFUNCTION(BlueprintCallable)
	void play_fire_montage();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	float _speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	float _direction;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	FRotator _aiming_for_spine;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	bool _bIsInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	bool _sprinting;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	bool _aiming;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	bool _climbing;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	bool _crouching;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	bool _IK_Enabled;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	E_CHARACTER_STATE _character_state;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	bool _near_wall;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	float _ADS_BlendSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	bool _is_FPP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	float _mouse_x;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	FTransform _LeftHandIK_Socket;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	bool _firing;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	FVector _actor_location;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> die_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> fire_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> reload_montage;
private:
	bool	_playing_die_montage;
	bool	_playing_reload_montage;

	ADNCommonCharacter* _owner = nullptr;

};
