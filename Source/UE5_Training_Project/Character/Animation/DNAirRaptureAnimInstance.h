

#pragma once

// Engine
#include <CoreMinimal.h>
#include <Animation/AnimInstance.h>

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNAirRaptureAnimInstance.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAirRaptureMontageEndDelegate);


class UAnimMontage;
class ADNCommonCharacter;
class ADNAirRaptureCharacter;


UCLASS()
class UE5_TRAINING_PROJECT_API UDNAirRaptureAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UDNAirRaptureAnimInstance();

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


	void add_event();
	void remove_event();

public:
	FOnAirRaptureMontageEndDelegate OnDieEnd;

public:
	UFUNCTION(BlueprintCallable)
		void on_die_montage_ended();

public:
	UFUNCTION(BlueprintCallable)
		void calculate_speed_direction(APawn* pawn_in);

	UFUNCTION(BlueprintCallable)
		void play_fire_1_montage();				// 기본 미사일 공격



private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
		float _speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
		float _direction;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
		float _pitch;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
		float _yaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
		float _pitch_min = -90.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
		float _pitch_max = 90.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
		bool _firing;			//블루프린트에서 shooting

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
		bool _aiming;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
		bool _bIsInAir;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TObjectPtr<UAnimMontage> die_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TObjectPtr<UAnimMontage> fire_1_montage;


private:
	bool	_playing_die_montage;
	ADNAirRaptureCharacter* _owner = nullptr;


};
