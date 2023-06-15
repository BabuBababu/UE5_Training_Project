


#include "UE5_Training_Project/Character/DNRaptureCubeCharacter.h"

// Engine
#include <NiagaraComponent.h>
#include <Kismet/KismetMathLibrary.h>


ADNRaptureCubeCharacter::ADNRaptureCubeCharacter()
{
	_enemy_type = E_ENEMY_TYPE::ET_RANGER_LC;
}


void ADNRaptureCubeCharacter::BeginPlay()
{
	Super::BeginPlay();

	init_base();
}


void ADNRaptureCubeCharacter::init_base()
{

	_fire_1_current_time = 0.f;
	_fire_2_current_time = 0.f;

	_fire_1_cool_time = 0.75f;
	_fire_2_cool_time = 20.f;	//이것도 다 데이터테이블로 옮길예정, 근데 공격task에서 쿨타임으로 맞추니 우선적으로 적용됨....

	_fire_1_cool_time_start = false;
	_fire_2_cool_time_start = false;

	if (IsValid(_danger_particle))
	{
		_niagara_component->SetAsset(_danger_particle);
		_niagara_component->Deactivate();
	}

}


void ADNRaptureCubeCharacter::rotate_head(float deleta_time_in, ADNCommonCharacter* target_in)
{
	// 타겟 바라보기
	if (nullptr == target_in)
		return;

	FVector target_location = target_in->GetActorLocation();
	FVector self_actor_location = _character_sub_skeletal_mesh->GetComponentLocation();
	FRotator FocusRotation = UKismetMathLibrary::FindLookAtRotation(self_actor_location, target_location);

	FRotator current_rotation = _character_sub_skeletal_mesh->GetComponentRotation();

	FRotator NewRotation = FMath::RInterpTo(current_rotation, FocusRotation, deleta_time_in, 4.f);

	_character_sub_skeletal_mesh->SetWorldRotation(NewRotation);

}
