

#pragma once

// Engine
#include <CoreMinimal.h>
#include <Components/ActorComponent.h>

// Data
#include "UE5_Training_Project/Data/DNCharacterData.h"

// Generated
#include "DNStatusComponent.generated.h"


class UDataTable;
class ADNCommonCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_TRAINING_PROJECT_API UDNStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDNStatusComponent();
	void add_event(ADNCommonCharacter* character_in);
	void remove_event(ADNCommonCharacter* character_in);


	void init();				//레벨 적용전 한번 초기화
	void apply_level();			//레벨 적용
	void set_begin_status();	//초기 hp, 장탄수 current 적용


protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void set_current_hp(const float after_hp_in) { _current_hp = after_hp_in; };

	int64 get_current_level() const { return _current_level; };
	int64 get_current_exp() const { return _current_exp; };
	float get_current_hp() const { return _current_hp; };
	int64 get_current_ammo() const { return _current_ammo; };

	float get_max_hp() const;
	int64 get_max_ammo() const;
	
	void add_exp(int64 exp_in);


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)		// 에디터 상에서 해당 캐릭터의 ID를 입력합니다. 이 ID를 통해 데이터를 가져와 적용합니다.
	int64				_character_id;

public:
	bool				_dead;
	int64				_current_level;
	int64				_current_exp;

	float				_current_hp;
	int64				_current_ammo;
	
	UDataTable*			_character_datatable;
	UDataTable*			_exp_datatable;
	FDNCharacterData*	_chartacter_data;

		

public:
	UFUNCTION()
	void remove_ammo_handler();


	UFUNCTION()
	void reload_ammo_handler();
};
