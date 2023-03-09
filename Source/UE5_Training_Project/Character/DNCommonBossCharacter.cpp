


#include "UE5_Training_Project/Character/DNCommonBossCharacter.h"



ADNCommonBossCharacter::ADNCommonBossCharacter()
{
	_enemy_type = E_ENEMY_TYPE::ET_BOSS;

	_character_sub_skeletal_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SubBodySkeletalMesh"));
	_character_sub_skeletal_mesh->SetupAttachment(_character_skeletal_mesh);
}

void ADNCommonBossCharacter::add_event()
{
	Super::add_event();

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