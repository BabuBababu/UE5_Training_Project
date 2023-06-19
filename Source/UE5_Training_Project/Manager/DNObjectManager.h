// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBaseManager.h"

// generated
#include "DNObjectManager.generated.h"

/**
 *	 아직은 확실히 정해두진 않았지만 
 *	 그리폰 인형 클래스와 스테이지에 생성하게 될 많은 적군 객체들을 관리하기 위해 만들었습니다.
 *	 총알 생성 및 파괴할 때 상당한 연산을 필요로 한다고 생각했어요. 
 *   파괴하지않고 사라지게 한다음 모아놨다가 재활용하면 어떨까 라는 생각을 했습니당!
 *	 그래서 오브젝트풀로서 관리를 할 수도 있겠다 싶어서 만든 매니저 클래스입니다!
 */


#define OBJECT_MANAGER			UDNObjectManager::get_object_manager()



class ADNTargetPointActor;
class ADNUnEnemyCharacter;
class ADNEnemyCharacter;
class ADNPlayerCharacter;
class ADNCommonFurniture;
class ADNCommonBed;
class ADNPostChair;
class ADNPatrolPointActor;
class ADNGuardPointActor;
class ADNBossMissile;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNObjectManager : public UDNBaseManager
{
	GENERATED_BODY()
	
public:
	void initialize() override;
	void destroy() override;


public:
	static TObjectPtr<UDNObjectManager> get_object_manager();

	void update_combat_squad_postion(int32 first_in, int32 second_in);


public:
	TMap<int64,ADNTargetPointActor*>	_target_location_actor_array;		//타겟 포인트액터 모음 맵
	TMap<int64, ADNPatrolPointActor*>	_patrol_location_actor_array;		//순찰 포인트액터 모음 맵
	TMap<int64, ADNGuardPointActor*>	_guard_location_actor_array;		//입초 포인트액터 모음 맵

	TArray<ADNBossMissile*>				_enemy_missile_array;				//맵에 생성된 모든 미사일 배열 (비활성,활성화 2 종류)
	TArray<ADNEnemyCharacter*>		    _all_spawned_enemy_array;			//맵에 생성된 모든 적 배열

	TMap<int64,ADNUnEnemyCharacter*>	_in_squad_doll_array;				//캐릭터의 스쿼드 ID, 캐릭터를 담은 배열
	TObjectPtr<ADNPlayerCharacter>		_player;

	TArray<ADNUnEnemyCharacter*>		_all_gained_doll_array;				//습득한 모든 아군 배열
	TArray<AActor*>						_griffin_player_array;				//아군,플레이어 담은 배열
	TMap<int64, ADNCommonBed*>			_lobby_bed_array;					//로비에 있는 침대를 담은 배열
	TMap<int64, ADNCommonFurniture*>	_lobby_furniture_array;				//침대, 당직용 의자 제외

	ADNPostChair* _post_chair;


};
