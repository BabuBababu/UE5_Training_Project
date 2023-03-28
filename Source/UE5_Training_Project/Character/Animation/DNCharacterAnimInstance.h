

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

	virtual void add_event();
	virtual void remove_event();

public:
	FOnMontageEndDelegate OnDieEnd;
	FOnMontageEndDelegate OnReloadEnd;
	FOnMontageEndDelegate OnKnifeEnd;
	FOnMontageEndDelegate OnThrowEnd;
	FOnMontageEndDelegate OnSaluteEnd;
	FOnMontageEndDelegate OnSleepEnd;			//일단 만들어둠 안쓰는중
	FOnMontageEndDelegate OnWakeUpEnd;

public:
	UFUNCTION(BlueprintCallable)
	void on_die_montage_ended();

	UFUNCTION(BlueprintCallable)
	void on_reload_montage_ended();

	UFUNCTION(BlueprintCallable)
	void on_knife_montage_ended();

	UFUNCTION(BlueprintCallable)
	void on_throw_montage_ended();

	UFUNCTION(BlueprintCallable)
	void on_salute_montage_ended();

	UFUNCTION(BlueprintCallable)
	void on_start_sleep_montage_ended();

	UFUNCTION(BlueprintCallable)
	void on_wakeup_montage_ended();

public:
	UFUNCTION(BlueprintCallable)
	void calculate_speed_direction(APawn* pawn_in);

	UFUNCTION(BlueprintCallable)
	void play_reload_montage();

	UFUNCTION(BlueprintCallable)
	void play_wall_jump_montage();

	UFUNCTION(BlueprintCallable)
	void play_fire_montage();

	UFUNCTION(BlueprintCallable)
	void play_cover_fire_montage();

	UFUNCTION(BlueprintCallable)
	void play_knife_montage();

	UFUNCTION(BlueprintCallable)
	void play_throw_montage();

	UFUNCTION(BlueprintCallable)
	void unlock_cover_animation();

	////////////////////////////
	// 로비
	////////////////////////////
	UFUNCTION(BlueprintCallable)
	void play_salute_montage();

	UFUNCTION(BlueprintCallable)
	void play_start_sleep_montage();

	UFUNCTION(BlueprintCallable)
	void play_loop_sleep_montage();

	UFUNCTION(BlueprintCallable)
	void play_wakeup_montage();
	

	// 밑의 2개는 아직 사용 X
	UFUNCTION(BlueprintCallable)
	void play_cover_turn_left_montage();

	UFUNCTION(BlueprintCallable)
	void play_cover_turn_right_montage();

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
	bool _cover_now;


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
	bool _input_left;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	bool _input_right;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	FVector _actor_location;

	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = Battle)
	TObjectPtr<UAnimMontage> die_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Battle)
	TObjectPtr<UAnimMontage> fire_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Battle)
	TObjectPtr<UAnimMontage> knife_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Battle)
	TObjectPtr<UAnimMontage> throw_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Battle)
	TObjectPtr<UAnimMontage> wall_jump_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Battle)
	TObjectPtr<UAnimMontage> cover_fire_left_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Battle)
	TObjectPtr<UAnimMontage> cover_fire_right_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Battle)
	TObjectPtr<UAnimMontage> cover_turn_left_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Battle)
	TObjectPtr<UAnimMontage> cover_turn_right_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Battle)
	TObjectPtr<UAnimMontage> reload_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lobby)
	TObjectPtr<UAnimMontage> salute_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lobby)
	TObjectPtr<UAnimMontage> start_sleep_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lobby)
	TObjectPtr<UAnimMontage> loop_sleep_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lobby)
	TObjectPtr<UAnimMontage> wakeup_montage;
	

private:
	bool	_playing_die_montage;
	bool	_playing_reload_montage;
	bool	_playing_cover_fire_montage;
	bool	_cover_fire_lock;
	bool	_playing_cover_turn_montage;
	bool	_playing_wall_jump_montage;
	bool	_playing_knife_montage;
	bool	_playing_throw_montage;




public:
	// 로비 //
	bool	_playing_salute_montage;
	bool	_check_salute_ended = false;
	bool	_playing_start_sleep_montage;
	bool	_check_start_sleep_ended = false;
	bool	_playing_loop_sleep_montage;
	bool	_playing_wakeup_montage;
	bool	_check_wakeup_ended = false;

private:
	ADNCommonCharacter* _owner = nullptr;


};
