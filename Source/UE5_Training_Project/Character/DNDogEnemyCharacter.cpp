


#include "UE5_Training_Project/Character/DNDogEnemyCharacter.h"

// Engine
#include <Engine/Classes/Kismet/GameplayStatics.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"
#include "UE5_Training_Project/Character/DNPlayerCharacter.h"
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"

// Component
#include "UE5_Training_Project/Component/DNStatusComponent.h"



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
	}
}

void ADNDogEnemyCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (false == _is_fire)		//공격 안했는데 부딫힌거면 리턴
		return;


	ADNCommonCharacter* character = Cast<ADNCommonCharacter>(OtherActor);

	if (nullptr == character)
		return;


	float damage = _status->_chartacter_data->character_status_data.damage;
	if (character->get_character_type() != E_CHARACTER_TYPE::CT_ENEMY)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DangDang Overlap Begin!!"));
		//해당 캐릭터에 대미지 입력

	}

}
