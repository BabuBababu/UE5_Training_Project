

#pragma once

// Engine
#include <CoreMinimal.h> 
#include <GameFramework/Actor.h>
#include <NiagaraSystem.h>
#include <NiagaraFunctionLibrary.h>

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// Generated
#include "DNBullet.generated.h"


//
//	우선은 미사일 발사용 클래스로 만들었습니다.
//	아이템의 총알이 아닙니다.
//
//




class UProjectileMovementComponent;
class ADNHeliCommonCharacter;
class ADNCommonCharacter;
class UBoxComponent;

UCLASS()
class UE5_TRAINING_PROJECT_API ADNBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ADNBullet();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void add_event();
	virtual void remove_event();


public:
	void fire(ADNCommonCharacter* target_in,  FVector location_in);
	virtual void init();
	void active_bullet();
	void non_active_bullet();
	void delay_destroy();



public:
	// 메쉬
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> _actor_static_mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* _box_collision;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	TObjectPtr<UProjectileMovementComponent> _projectile_movement_component;



	UPROPERTY(EditAnywhere, Category = "Particle Effects")					//직격 파티클
	UNiagaraSystem* _bomb_particle;
	
	UPROPERTY(EditAnywhere, Category = "Particle Effects")					//꼬리 파티클
	UNiagaraSystem* _tail_particle;

	UPROPERTY(EditAnywhere, Category = "Particle Effects")					//체력 적음용 나이아가라 컴포넌트
	TObjectPtr<UNiagaraComponent> _niagara_component;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)								//발사 소리
	TObjectPtr<USoundBase> _missile_fire_soundcue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)								//직격 소리
	TObjectPtr<USoundBase> _bomb_soundcue;



	ADNCommonCharacter*		_owner;
	float					_limit_time;
	bool					_ready_destroy;


public:
	UFUNCTION()
	virtual	void overlap_actor_handler(const FHitResult& HitResult);
};
