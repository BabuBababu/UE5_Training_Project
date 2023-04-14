

#pragma once

// Engine
#include <CoreMinimal.h>

// Base
#include "UE5_Training_Project/UI/Base/DNBaseManager.h"

// Generated
#include "DNLobbyNPCManager.generated.h"

/**
 * 
 */


#define LOBBY_MANAGER			UDNLobbyNPCManager::get_lobby_manager()

class ADNUnEnemyCharacter;
class ADNPlayerCharacter;
class ADNLobbyAIController;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNLobbyNPCManager : public UDNBaseManager
{
	GENERATED_BODY()

public:
	void initialize() override;
	void destroy() override;

	void initialize_ai_controller();

	void set_on_guard(ADNUnEnemyCharacter* doll_in);
	void set_on_patrol(ADNUnEnemyCharacter* doll_in);
	void set_on_post(ADNUnEnemyCharacter* doll_in);
	void set_on_rest(ADNUnEnemyCharacter* doll_in);					//반드시 처음 초기화할 때만 사용합니다.

	void set_off_guard(ADNUnEnemyCharacter* doll_in);
	void set_off_patrol(ADNUnEnemyCharacter* doll_in);
	void set_off_post(ADNUnEnemyCharacter* doll_in);

	void hide_weapon(ADNUnEnemyCharacter* doll_in);
	void show_weapon(ADNUnEnemyCharacter* doll_in);


	void apply_work();

public:
	static TObjectPtr<UDNLobbyNPCManager> get_lobby_manager();


public:
	// 키 : 인형 ID, 값 : 인형
	TMap<int64, ADNUnEnemyCharacter*> _guard_doll_array;			//입초근무
	TMap<int64, ADNUnEnemyCharacter*> _patrol_doll_array;			//순찰근무
	TMap<int64, ADNUnEnemyCharacter*> _post_doll_array;				//당직근무
	TMap<int64, ADNUnEnemyCharacter*> _rest_doll_array;				//미배정(휴식)


	TMap<int64,TObjectPtr<ADNLobbyAIController>>	_guard_ai_controller_array;			//2명 (임시)
	TMap <int64,TObjectPtr<ADNLobbyAIController>>	_patrol_ai_controller_array;		//2명 (임시)
	TMap <int64,TObjectPtr<ADNLobbyAIController>>	_post_ai_controller_array;			//1명 (임시)


	// 근무 시간
	float _working_time;			//위젯에서 변경할 수 있도록할 예정

	// 휴식 시간
	float _resting_time;			//위젯에서 변경할 수 있도록할 예정


};
