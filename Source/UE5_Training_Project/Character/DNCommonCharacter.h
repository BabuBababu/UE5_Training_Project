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


class USpringArmComponent;
class UCameraComponent;
class UDNPlayerLineTrace;


UCLASS()
class UE5_TRAINING_PROJECT_API ADNCommonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADNCommonCharacter();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
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


	E_CHARACTER_TYPE get_character_type() const { return _character_type; };
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

	// 라인트레이스
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDNPlayerLineTrace* _line_trace;


	//

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
	E_CHARACTER_TYPE _character_type = E_CHARACTER_TYPE::CT_NONE;


public:
	FRotator _aiming_rotation = FRotator(0.f, 0.f, 0.f);
	E_CHARACTER_STATE _pre_upper_character_state = E_CHARACTER_STATE::CS_NONE;

};
