


#include "UE5_Training_Project/Character/DNShieldEnemyCharacter.h"

// Engine
#include <Engine/Classes/Kismet/GameplayStatics.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"
#include "UE5_Training_Project/Character/DNPlayerCharacter.h"
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"

// Component
#include "UE5_Training_Project/Component/DNStatusComponent.h"

// Util
#include "UE5_Training_Project/Util/DNDamageOperation.h"



ADNShieldEnemyCharacter::ADNShieldEnemyCharacter()
{
	// 쉴드는 액터로 따로 만들었으므로 해당 액터에 콜리전이 있습니다. 따라서 여기에서는 소켓으로 붙여주기만 하면 됩니다.
	// 또한 이 스태틱매쉬 컴포넌트는 단순히 BP 쉴드를 담기 위함입니다. 추가로 설정할 필요없습니다.
	_weapon_left_shield = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponShield"));
	_weapon_left_shield->SetupAttachment(_character_skeletal_mesh,"weapon_l");


	//_weapon_armed는 총이 될수도 있고 이 캐릭터의 경우 검이 될 수도 있습니다. 캐릭터의 무기 공용입니다.
	_attack_sword_collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AttackSword"));
	_attack_sword_collision->SetupAttachment(_weapon_armed);



	init_base();
	init_ai();
}

void ADNShieldEnemyCharacter::BeginPlay()
{
	_is_attacking = false;
	_is_armed_weapon = true;
	_character_state = E_CHARACTER_STATE::CS_ARM;			//우선은 테스트를 위해 무기를 들었다고 설정
}

void ADNShieldEnemyCharacter::init_base()
{
	Super::init_base();
	_enemy_type = E_ENEMY_TYPE::ET_MELEE;
	_is_overlap = false;
	_damaged_character = nullptr;
}

void ADNShieldEnemyCharacter::add_event()
{
	Super::add_event();

	_attack_sword_collision->OnComponentBeginOverlap.AddDynamic(this, &ADNShieldEnemyCharacter::OnOverlapBegin);

}

void ADNShieldEnemyCharacter::remove_event()
{
	_attack_sword_collision->OnComponentBeginOverlap.RemoveDynamic(this, &ADNShieldEnemyCharacter::OnOverlapBegin);

	Super::remove_event();
}


void ADNShieldEnemyCharacter::fire()
{
	if (_is_fire)
	{
		OnFire.Broadcast();	//공격 애니메이션 재생
		UGameplayStatics::PlaySoundAtLocation(this, _fire_soundcue, GetActorLocation());

		if (_is_overlap)
		{
			float damage = _status->_chartacter_data->character_status_data.damage;
			if (nullptr != _damaged_character)
			{
				DNDamageOperation::melee_damage(damage, _damaged_character, this);
				DNDamageOperation::DamageShowUI(damage, _damaged_character, E_DAMAGE_TYPE::DT_NORMAL);	//헤드일 경우 약점 대미지로 판단, ReceiveDamage에서 약점부위를 판단하고 넣어야할듯.. 순서가.. 일단은 노멀로 통일

				_is_overlap = false;
			}
		}

		GetWorld()->GetTimerManager().SetTimer(_fire_timer, this, &ADNShieldEnemyCharacter::fire, _status->_chartacter_data->character_status_data.fire_speed, true);
	}
}


void ADNShieldEnemyCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (false == _is_fire)		//공격 안했는데 부딫힌거면 리턴
		return;


	ADNCommonCharacter* character = Cast<ADNCommonCharacter>(OtherActor);

	if (nullptr == character)
	{
		_is_overlap = false;
		return;
	}


	if (character->get_character_type() != E_CHARACTER_TYPE::CT_ENEMY)
	{
		_is_overlap = true;
		_damaged_character = character;
	}

}
