

#pragma once

// Engine
#include <CoreMinimal.h>
#include <Animation/AnimInstance.h>

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNGunSpiderBossAnimInstance.generated.h"

/**
 * 
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBossMontageEndDelegate);


class UAnimMontage;
class ADNCommonCharacter;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNGunSpiderBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UDNGunSpiderBossAnimInstance();

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


	void add_event();
	void remove_event();

public:
	FOnBossMontageEndDelegate OnDieEnd;
	FOnBossMontageEndDelegate OnReloadEnd;

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
	void play_fire_1_montage();				// 기본 미사일 공격

	UFUNCTION(BlueprintCallable)
	void play_fire_2_montage();				// 서브 머신건 공격

	UFUNCTION(BlueprintCallable)
	void play_melee_1_montage();			// 기본 밀리 공격

	UFUNCTION(BlueprintCallable)
	void play_melee_2_montage();			// 서브 밀리 공격



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
		TObjectPtr<UAnimMontage> melee_1_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TObjectPtr<UAnimMontage> melee_2_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TObjectPtr<UAnimMontage> fire_1_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TObjectPtr<UAnimMontage> fire_2_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TObjectPtr<UAnimMontage> reload_montage;

private:
	bool	_playing_die_montage;
	bool	_playing_reload_montage;

	ADNCommonCharacter* _owner = nullptr;
};
