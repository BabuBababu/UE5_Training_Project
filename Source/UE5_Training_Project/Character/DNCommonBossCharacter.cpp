


#include "UE5_Training_Project/Character/DNCommonBossCharacter.h"

// Animation
#include "UE5_Training_Project/Character/Animation/DNGunSpiderBossAnimInstance.h"

// Component
#include "UE5_Training_Project/Character/Component/DNEnemyLineTrace.h"

// Actor
#include "UE5_Training_Project/Actor/DNBossMissile.h"

ADNCommonBossCharacter::ADNCommonBossCharacter()
{
	_enemy_type = E_ENEMY_TYPE::ET_BOSS;

	_character_sub_skeletal_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SubBodySkeletalMesh"));
	_character_sub_skeletal_mesh->SetupAttachment(_character_skeletal_mesh);
}

void ADNCommonBossCharacter::add_event()
{
	UDNGunSpiderBossAnimInstance* anim_instance = Cast<UDNGunSpiderBossAnimInstance>(_character_skeletal_mesh->GetAnimInstance());
	if (nullptr == anim_instance)
		return;

	anim_instance->OnDieEnd.AddDynamic(this, &ADNCommonCharacter::destroy_object_handler);
	anim_instance->OnReloadEnd.AddDynamic(this, &ADNCommonCharacter::return_to_armed_handler);

	OnTargetDead.AddDynamic(this, &ADNCommonCharacter::reset_fire_state_handler);
	_enemy_line_trace->OnTargetHit.AddDynamic(this, &ADNCommonCharacter::ammo_hit_handler);


}

void ADNCommonBossCharacter::remove_event()
{

	Super::remove_event();
}


void ADNCommonBossCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADNCommonBossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void ADNCommonBossCharacter::fire_1(ADNCommonCharacter* target_in)
{
	
}

void ADNCommonBossCharacter::fire_2(ADNCommonCharacter* target_in)
{
	//if (nullptr != _fire_2_class)
	//{
	//	FVector socket_location = _character_sub_skeletal_mesh->GetSocketLocation(FName("Rocket_Muzzle_L"));
	//	ADNBossMissile* bullet = GetWorld()->SpawnActor<ADNBossMissile>(_fire_2_class, socket_location, GetActorRotation()); // 미사일 생성
	//	bullet->SetActorLocation(socket_location);
	//	//bullet->non_active_bullet();


	//	bullet->_owner = this;

	//	_missile = bullet;
	//}

	//if (nullptr != _missile)
	//{
	//	_missile->fire(target_in);
	//	_missile_cool_time_start = true;
	//}
}

void ADNCommonBossCharacter::melee_1(ADNCommonCharacter* target_in)
{

}

void ADNCommonBossCharacter::melee_2(ADNCommonCharacter* target_in)
{

}