


#include <UE5_Training_Project/Component/DNStatusComponent.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"


// Animation
#include "UE5_Training_Project/Character/Animation/DNCharacterAnimInstance.h"




// Sets default values for this component's properties
UDNStatusComponent::UDNStatusComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	// 캐릭터 데이터 테이블 초기화
	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterDataObject(TEXT("/Game/Blueprint/Data/DT_DNCharacterData"));
	if (CharacterDataObject.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable Succeed!"));
		_character_datatable = CharacterDataObject.Object;
	}


	// 경험치 테이블 초기화
	static ConstructorHelpers::FObjectFinder<UDataTable> EXPDataObject(TEXT("/Game/Blueprint/Data/DT_DNCharacterEXPData"));
	if (EXPDataObject.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable Succeed!"));
		_exp_datatable = EXPDataObject.Object;
	}

	_has_ammo = 5000;		// 테스트용 일단 여기에 초기화해둠
}


// Called when the game starts
void UDNStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}


// Called every frame
void UDNStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UDNStatusComponent::add_event(ADNCommonCharacter* character_in)
{
	ADNCommonCharacter* character = dynamic_cast<ADNCommonCharacter*>(character_in);
	if (nullptr != character)
	{
		character->OnFire.AddDynamic(this, &UDNStatusComponent::remove_ammo_handler);
	}

	UDNCharacterAnimInstance* anim_instance = dynamic_cast<UDNCharacterAnimInstance*>(character->_character_skeletal_mesh->GetAnimInstance());
	if (nullptr != anim_instance)
		anim_instance->OnReloadEnd.AddDynamic(this, &UDNStatusComponent::reload_ammo_handler);
		
}

void UDNStatusComponent::remove_event(ADNCommonCharacter* character_in)
{

}


void UDNStatusComponent::init()
{

	TArray<FDNCharacterData*> data_array;
	_character_datatable->GetAllRows<FDNCharacterData>("",data_array);

	for (auto& data : data_array)
	{
		if (data->character_id == _character_id)
		{
			_chartacter_data = data;
		}
	}

	apply_level();
	set_begin_status();


	// 잘 적용되었는지 디버깅
	if (_chartacter_data->character_id == 1)
	{

		UE_LOG(LogTemp, Warning, TEXT("My Name is %s"), *_chartacter_data->character_name);
		UE_LOG(LogTemp, Warning, TEXT("My Max Ammo is %d"), _chartacter_data->character_status_data.max_ammo);
	}


}

void UDNStatusComponent::reset()
{
	set_begin_status();
}

void UDNStatusComponent::set_begin_status()
{
	_dead = false;
	_current_level = 1;
	_current_exp = 0;
	_current_ammo = _chartacter_data->character_status_data.max_ammo;
	_current_hp = _chartacter_data->character_status_data.hp;
	_has_ammo = 5000;
}


void UDNStatusComponent::apply_level()
{
	_chartacter_data->character_status_data.hp		= _chartacter_data->character_status_data.hp + _current_level * _chartacter_data->character_status_data.hp_up;
	_chartacter_data->character_status_data.damage	= _chartacter_data->character_status_data.damage + _current_level * _chartacter_data->character_status_data.damage_up;
	_chartacter_data->character_status_data.armor	= _chartacter_data->character_status_data.armor + _current_level * _chartacter_data->character_status_data.armor_up;
}


float UDNStatusComponent::get_max_hp() const
{

	if (nullptr == _chartacter_data)
		return 0.f;

	return _chartacter_data->character_status_data.hp;
}


int64 UDNStatusComponent::get_max_ammo() const
{

	if (nullptr == _chartacter_data)
		return 0;

	return _chartacter_data->character_status_data.max_ammo;
}


void UDNStatusComponent::add_exp(int64 exp_in)
{
	_current_exp += exp_in;

	TArray<FDNEXPTableData*> data_array;
	_character_datatable->GetAllRows<FDNEXPTableData>("", data_array);

	for (auto& data : data_array)
	{
		if (data->level == _current_level)
		{
			if (_current_exp >= data->exp)
			{
				_current_level += 1;
				apply_level();
			}
		}
	}

}

void UDNStatusComponent::remove_ammo_handler()
{
	_current_ammo -= 1;
	UE_LOG(LogTemp, Warning, TEXT("My current ammo is %d"), _current_ammo);
}

void UDNStatusComponent::reload_ammo_handler()
{
	
	_has_ammo -= _chartacter_data->character_status_data.max_ammo - _current_ammo;

	if (_has_ammo < 0)			//예시) 남은총알이 40발 미만일 때
	{
		_current_ammo = _chartacter_data->character_status_data.max_ammo + _has_ammo;
		_has_ammo = 0;
	}
	else                        //예시) 남은총알이 40발 이상일 때
		_current_ammo = _chartacter_data->character_status_data.max_ammo;

}