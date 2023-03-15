// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine
#include <CoreMinimal.h>
#include <GameFramework/Character.h>

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// generated
#include "DNCommonCharacter.generated.h"



/**
 *	플레이어, 그리폰 인형, 적군의 캐릭터가 되는 공통 클래스입니다.
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamageIndicator, float, damage, E_DAMAGE_TYPE, type_in);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamaged,int64, squad_index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInputStartDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnIteractionFinishDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAIAmmoDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWallJumpDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKnifeDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnThrowDelegate);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartAIAmmoDelegate,int64,ammo_count);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIteractionFinishItemDelegate,ADNCommonItem*, item );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeadDelegate, ADNCommonCharacter*, character);


class USpringArmComponent;
class UCameraComponent;
class UCapsuleComponent;
class UWidgetComponent;
class UDNPlayerLineTrace;
class UDNEnemyLineTrace;
class UDNStatusComponent;
class ADNCommonGrenade;

UCLASS()
class UE5_TRAINING_PROJECT_API ADNCommonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADNCommonCharacter();

	virtual void add_event();
	virtual void remove_event();
	virtual void init_ui_event();
	virtual void remove_ui_event();

protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
	// 캐릭터 상태 또는 변수를 통해 애니메이션을 재생합니다.
	virtual void idle();
	virtual void reload();
	virtual void fire();
	virtual void stop_fire();
	virtual void armed();
	virtual void crouch();
	virtual void aiming();
	virtual void stop_aiming();
	virtual void walk();
	virtual void sprint();
	virtual void stop_sprint();
	virtual void interaction();		//여기에 상호작용 전부 포함됨 해당 관련 컴포넌트 만들어서 알맞게 체크
	virtual void cover();
	virtual void attack_knife();
	virtual void throw_grenade();

public:
	E_CHARACTER_TYPE get_character_type() const { return _character_type; };
	E_CHARACTER_POSITION get_character_position() const { return _character_position; };
	uint8 get_position_index() const { return _position_index; };
	TObjectPtr<UDNStatusComponent> get_status_component() const { return _status; };

	void set_position_index(const uint8 num_in) { _position_index = num_in; };
	void set_idle_animation();


	FTransform set_camera_transform(bool flag_in);

public:
	// 메쉬
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<USkeletalMeshComponent> _character_skeletal_mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> _back_pack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> _weapon_armed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> _weapon_un_armed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> _knife_weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<UCapsuleComponent> _knife_collision;

	// 수류탄
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = bullet)
	TSubclassOf<ADNCommonGrenade> _grenade_class;

	// 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> _camera_boom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> _follow_camera;

	// 스테이터스 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UDNStatusComponent> _status;

	// 라인트레이스
	UPROPERTY(EditAnywhere, BlueprintReadWrite)		//에휴 잘못만들었다 부모 클래스 하나 만들걸
	TObjectPtr<UDNPlayerLineTrace> _line_trace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)		//에휴 잘못만들었다 부모 클래스 하나 만들걸
	TObjectPtr<UDNEnemyLineTrace> _enemy_line_trace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_CHARACTER_TYPE _character_type = E_CHARACTER_TYPE::CT_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_CHARACTER_POSITION _character_position = E_CHARACTER_POSITION::CP_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 _character_id;

	// 리소스매니저같은거 만들어서 거기서 호출하는 방식으로 가자...
	// 일단은 이렇게 만들어두고

	UPROPERTY(EditAnywhere, BlueprintReadWrite)		//사격 소리
	TObjectPtr<USoundBase> _fire_soundcue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)		//나이프 소리
	TObjectPtr<USoundBase> _knife_soundcue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)		//장전 소리
	TObjectPtr<USoundBase> _reload_soundcue;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)		//화났을 때
	TObjectPtr<USoundBase> _upset_soundcue;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)		//지휘관 걱정할 때
	TObjectPtr<USoundBase> _worry_soundcue;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)		//스킬쓸 때
	TObjectPtr<USoundBase> _skill_dialog_soundcue;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool _is_sprint;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool _is_crouch;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool _is_walk;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool _is_standing;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool _is_aiming;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool _is_near_wall;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool _is_reloading;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool _is_fire;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool _is_armed_weapon;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	E_CHARACTER_STATE _character_state = E_CHARACTER_STATE::CS_IDLE;


protected:
	float _default_max_speed = 0.0f;
	uint8 _position_index;
	FTimerHandle _fire_timer;
	



public:
	FRotator _aiming_rotation = FRotator(0.f, 0.f, 0.f);
	E_CHARACTER_STATE _pre_upper_character_state = E_CHARACTER_STATE::CS_NONE;
	bool _is_attacking;
	bool _cover_now = false;
	bool _is_wall_jump = false;
	bool _is_knife_overlap = false;

	FVector  _my_spawn_location = FVector(0.f, 0.f, 0.f);
	int64 _target_change_limit_ammo = 10;				// 병과마다 다르게 가야할듯?
	int64 _target_change_current_ammo = 0;




	// 델리게이트
public:
	FOnInputStartDelegate OnFire;
	FOnInputStartDelegate StopFire;
	FOnInputStartDelegate OnCoverFire;
	FOnInputStartDelegate OnReload;
	FOnWallJumpDelegate OnWallJump;
	FOnIteractionFinishItemDelegate OnItemPickup;
	FOnIteractionFinishDelegate OnVehicleRiding;
	FOnIteractionFinishDelegate OnNPCTalk;
	FOnAIAmmoDelegate OnEmptyAmmo;
	FOnAIAmmoDelegate OnStopShotAmmo;
	FOnStartAIAmmoDelegate OnAtStartAmmo;
	FOnDeadDelegate OnTargetDead;
	FOnKnifeDelegate OnKnife;
	FOnThrowDelegate OnThrow;

	FOnDamageIndicator OnDamageIndicator;
	FOnDamaged OnDamaged;

public:
	UFUNCTION()
	virtual void destroy_object_handler();		//월드상에서 안보이게 하는 핸들러

	UFUNCTION()
	void return_to_armed_handler();

	UFUNCTION()
	void reset_fire_state_handler(ADNCommonCharacter* chracter_in);

	UFUNCTION()
	void ammo_hit_handler();

	UFUNCTION()
	void throw_grenade_handler();

	UFUNCTION()
	void overlap_knife_handler(class UPrimitiveComponent* selfComp, class AActor* otherActor, UPrimitiveComponent* otherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
