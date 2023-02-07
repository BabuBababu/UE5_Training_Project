﻿// Fill out your copyright notice in the Description page of Project Settings.

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



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInputStartDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnIteractionFinishDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIteractionFinishItemDelegate,ADNCommonItem*, item );


class USpringArmComponent;
class UCameraComponent;
class UDNPlayerLineTrace;
class UDNEnemyLineTrace;
class UDNStatusComponent;

UCLASS()
class UE5_TRAINING_PROJECT_API ADNCommonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADNCommonCharacter();

	virtual void add_event();
	virtual void remove_event();

protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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




	// 델리게이트
public:
	FOnInputStartDelegate OnFire;
	FOnInputStartDelegate OnReload;
	FOnIteractionFinishItemDelegate OnItemPickup;
	FOnIteractionFinishDelegate OnVehicleRiding;
	FOnIteractionFinishDelegate OnNPCTalk;

public:
	UFUNCTION()
	void destroy_object_handler();

	UFUNCTION()
	void return_to_armed_handler();

};
