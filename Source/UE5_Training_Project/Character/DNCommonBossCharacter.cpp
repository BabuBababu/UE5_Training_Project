


#include "UE5_Training_Project/Character/DNCommonBossCharacter.h"

// Animation
#include "UE5_Training_Project/Character/Animation/DNGunSpiderBossAnimInstance.h"

// Component
#include "UE5_Training_Project/Character/Component/DNEnemyLineTrace.h"

// Actor
#include "UE5_Training_Project/Actor/DNBossMissile.h"

ADNCommonBossCharacter::ADNCommonBossCharacter()
{

	_character_sub_skeletal_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SubBodySkeletalMesh"));
	_character_sub_skeletal_mesh->SetupAttachment(_character_skeletal_mesh);

	init_base();
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

	// 미사일 쿨타임 계산
	if (_fire_2_cool_time_start)
	{
		_fire_2_current_time += DeltaTime;
		if (_fire_2_current_time >= _fire_2_cool_time)
		{
			_fire_2_cool_time_start = false;
			_fire_2_current_time = 0.f;
		}
	}
}

void ADNCommonBossCharacter::init_base()
{
	_enemy_type = E_ENEMY_TYPE::ET_BOSS;

	_fire_2_current_time = 0.f;
	_fire_2_cool_time = 10.f;	//이것도 다 데이터테이블로 옮길예정, 근데 공격task에서 쿨타임으로 맞춰도 되지않나?
	_fire_2_cool_time_start = false;

	_missile_array.Empty();
}


void ADNCommonBossCharacter::fire_1(ADNCommonCharacter* target_in)
{
	
}

void ADNCommonBossCharacter::fire_2(ADNCommonCharacter* target_in)
{
	if (nullptr == _fire_2_class)
		return;

	for (int i = 0; i < 10; ++i)
	{
		FString socket_string = "Rocket_Muzzle_";
		FString num = FString::FromInt(i);
		socket_string.Append(num);

		FVector socket_location = _character_sub_skeletal_mesh->GetSocketLocation(FName(socket_string));
		ADNBossMissile* bullet = GetWorld()->SpawnActor<ADNBossMissile>(_fire_2_class, socket_location, GetActorRotation()); // 미사일 생성
		bullet->SetActorLocation(socket_location);
		//bullet->SetActorRotation(GetActorRotation());
		bullet->_owner = this;
		bullet->fire(target_in, socket_location);

		_missile_array.Add(bullet);

	}

	_fire_2_cool_time_start = true;

}

void ADNCommonBossCharacter::melee_1(ADNCommonCharacter* target_in)
{

}

void ADNCommonBossCharacter::melee_2(ADNCommonCharacter* target_in)
{

}