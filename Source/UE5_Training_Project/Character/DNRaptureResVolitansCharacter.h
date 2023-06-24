

#pragma once

// Engine
#include <CoreMinimal.h>

// Character
#include "UE5_Training_Project/Character/DNAirRaptureCharacter.h"

// Generated
#include "DNRaptureResVolitansCharacter.generated.h"

/**
 * 
 */



UCLASS()
class UE5_TRAINING_PROJECT_API ADNRaptureResVolitansCharacter : public ADNAirRaptureCharacter
{
	GENERATED_BODY()
	
public:
	ADNRaptureResVolitansCharacter();

protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	void add_event() override;
	void remove_event() override;
	void destroy_object_handler() override;

public:
	void init_base() override;
	void fire_1(ADNCommonCharacter* target_in) override;  // 대형 호밍 미사일
	virtual void fire_2(ADNCommonCharacter* target_in);	  // 도탄 미사일
	virtual void fire_3(ADNCommonCharacter* target_in);   // 소형 연발 호밍 미사일

	virtual void play_damaged_parts();
	virtual void destroy_parts();
	

	void show_smoke();
	void hide_smoke();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> _parts_mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = bullet)
	TSubclassOf<ADNBossMissile> _fire_2_class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = bullet)
	TSubclassOf<ADNBossMissile> _fire_3_class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)								//부위 파괴 사운드
	TObjectPtr<USoundBase> _damaged_parts_soundcue;



	UPROPERTY(EditAnywhere, Category = "Particle Effects")					//체력 적음 파티클
	UNiagaraSystem* _danger_particle;

	UPROPERTY(EditAnywhere, Category = "Particle Effects")					//공격시 파티클
	UNiagaraSystem* _attack_particle;

	UPROPERTY(EditAnywhere, Category = "Particle Effects")					//부위 파괴 파티클
	UNiagaraSystem* _damaged_particle;


	UPROPERTY(EditAnywhere, Category = "Particle Effects")					//체력 적음용 나이아가라 컴포넌트 공중 보스에 적용 예정
	TObjectPtr<UNiagaraComponent> _danger_component;


	UPROPERTY(EditAnywhere, Category = "Particle Effects")					//공격시 나이아가라 컴포넌트
	TObjectPtr<UNiagaraComponent> _attack_niagara_component;

	UPROPERTY(EditAnywhere, Category = "Particle Effects")					//부위 파괴 나이아가라 컴포넌트
	TObjectPtr<UNiagaraComponent> _damaged_niagara_component;

	UPROPERTY(EditAnywhere, Category = "Particle Effects")					//공중에 떠 있음 나이아가라 컴포넌트
		TObjectPtr<UNiagaraComponent> _flying_niagara_component;


public:
	float _fire_2_cool_time;
	float _fire_2_current_time;

	bool _fire_2_cool_time_start;


	float _fire_3_cool_time;
	float _fire_3_current_time;

	bool _fire_3_cool_time_start;

	bool _destroyed_parts;
};
