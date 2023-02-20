


#include "UE5_Training_Project/Character/DNDogEnemyCharacter.h"

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


ADNDogEnemyCharacter::ADNDogEnemyCharacter()
{

	AttackHead = CreateDefaultSubobject<USphereComponent>(TEXT("AttackHead"));
	AttackHead->SetupAttachment(_character_skeletal_mesh, TEXT("Bone_PowerDoor"));
	
	init_base();
	init_ai();
}

void ADNDogEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	_is_attacking = false;
	_is_armed_weapon = true;
	_character_state = E_CHARACTER_STATE::CS_ARM;			//우선은 테스트를 위해 무기를 들었다고 설정
}


void ADNDogEnemyCharacter::init_base()
{
	Super::init_base();
	_enemy_type = E_ENEMY_TYPE::ET_MELEE;
	_is_overlap = false;
	_damaged_character = nullptr;
}


void ADNDogEnemyCharacter::add_event()
{
	Super::add_event();

	AttackHead->OnComponentBeginOverlap.AddDynamic(this, &ADNDogEnemyCharacter::OnOverlapBegin);
}

void ADNDogEnemyCharacter::remove_event()
{
	AttackHead->OnComponentBeginOverlap.RemoveDynamic(this, &ADNDogEnemyCharacter::OnOverlapBegin);

	Super::remove_event();
}


void ADNDogEnemyCharacter::fire()
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

		GetWorld()->GetTimerManager().SetTimer(_fire_timer, this, &ADNDogEnemyCharacter::fire, _status->_chartacter_data->character_status_data.fire_speed, true);
	}
}

void ADNDogEnemyCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
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
