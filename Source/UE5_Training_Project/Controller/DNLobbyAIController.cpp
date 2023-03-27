


#include "UE5_Training_Project/Controller/DNLobbyAIController.h"


// Engine
#include <Kismet/GameplayStatics.h>
#include <Navigation/PathFollowingComponent.h>
#include <BehaviorTree/BehaviorTree.h>
#include <NavigationSystem.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <BehaviorTree/BehaviorTreeComponent.h>
#include <Perception/AIPerceptionComponent.h>
#include <Perception/AISenseConfig_Sight.h>
#include <Perception/AIPerceptionStimuliSourceComponent.h>
#include <Perception/AIPerceptionComponent.h>


// BlackBoard
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"

//Furniture
#include "UE5_Training_Project/Actor/Furniture/DNCommonBed.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"
#include "UE5_Training_Project/Manager/DNLobbyNPCManager.h"



void ADNLobbyAIController::OnPossess(APawn* pawn_in)
{

	ADNCommonCharacter* character = Cast<ADNCommonCharacter>(pawn_in);

	if (character->get_character_type() == E_CHARACTER_TYPE::CT_GRIFFIN)
	{
		if (_ai_type == E_LOBBY_AI_TYPE::LAT_GUARD)
		{
			UBehaviorTree* BTObject = LoadObject<UBehaviorTree>(NULL, TEXT("/Game/Blueprint/AI/BT_Combat_UnEnemy_Guard.BT_Combat_UnEnemy_Guard"), NULL, LOAD_None, NULL);
			if (nullptr != BTObject)
			{
				if (nullptr == btree)
					btree = BTObject;
				UE_LOG(LogTemp, Warning, TEXT("bt guard succeeded!"));
			}
			
		}
		else if (_ai_type == E_LOBBY_AI_TYPE::LAT_PATROL)
		{
			UBehaviorTree* BTObject = LoadObject<UBehaviorTree>(NULL, TEXT("/Game/Blueprint/AI/BT_Combat_UnEnemy_Patrol.BT_Combat_UnEnemy_Patrol"), NULL, LOAD_None, NULL);
			if (nullptr != BTObject)
			{
				if (nullptr == btree)
					btree = BTObject;
				UE_LOG(LogTemp, Warning, TEXT("bt patrol succeeded!"));
			}
			character->_character_origin_state = E_CHARACTER_STATE::CS_PATROL;
		}
		else if (_ai_type == E_LOBBY_AI_TYPE::LAT_REST)
		{
			UBehaviorTree* BTObject = LoadObject<UBehaviorTree>(NULL, TEXT("/Game/Blueprint/AI/BT_Combat_UnEnemy_Rest.BT_Combat_UnEnemy_Rest"), NULL, LOAD_None, NULL);
			if (nullptr != BTObject)
			{
				if (nullptr == btree)
					btree = BTObject;
				UE_LOG(LogTemp, Warning, TEXT("bt rest succeeded!"));
			}
			character->_character_origin_state = E_CHARACTER_STATE::CS_REST;
		}
		else if (_ai_type == E_LOBBY_AI_TYPE::LAT_CITIZEN)
		{
			UBehaviorTree* BTObject = LoadObject<UBehaviorTree>(NULL, TEXT("/Game/Blueprint/AI/BT_Combat_UnEnemy_Citizen.BT_Combat_UnEnemy_Citizen"), NULL, LOAD_None, NULL);
			if (nullptr != BTObject)
			{
				if (nullptr == btree)
					btree = BTObject;
				UE_LOG(LogTemp, Warning, TEXT("bt citizen succeeded!"));
			}
			character->_character_origin_state = E_CHARACTER_STATE::CS_IDLE;
		}
		else if (_ai_type == E_LOBBY_AI_TYPE::LAT_POST)
		{
			UBehaviorTree* BTObject = LoadObject<UBehaviorTree>(NULL, TEXT("/Game/Blueprint/AI/BT_Combat_UnEnemy_Post.BT_Combat_UnEnemy_Post"), NULL, LOAD_None, NULL);
			if (nullptr != BTObject)
			{
				if (nullptr == btree)
					btree = BTObject;
				UE_LOG(LogTemp, Warning, TEXT("bt post succeeded!"));
			}
			character->_character_origin_state = E_CHARACTER_STATE::CS_POST;
		}

	}


	Super::OnPossess(pawn_in);


}


void ADNLobbyAIController::OnUnPossess()
{
	Super::OnUnPossess();

}


void ADNLobbyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (false == _finish_work)
	{
		_current_time += DeltaSeconds;
		if (LOBBY_MANAGER->_working_time <= _current_time)
		{
			if (true == OBJECT_MANAGER->_lobby_bed_array.IsEmpty())
				return;
			
			get_blackboard()->SetValueAsBool(all_ai_bb_keys::is_finish_work, true);			// 일정 시간이 만료되면 일을 끝냈다고 블랙보드에 값을 넣습니다.

			for (auto& bed : OBJECT_MANAGER->_lobby_bed_array)
			{
				if(bed.Key == _owner->_character_id)// 일단은 오브젝트 매니저에 있는 침대를 캐릭터 고유ID와 맞춰서 사용합니다.
					get_blackboard()->SetValueAsObject(all_ai_bb_keys::house_bed, bed.Value);
			}		
			_finish_work = true;
			_current_time = 0.f;
		}
	}

}



void ADNLobbyAIController::add_event(ADNCommonCharacter* character_in)
{
	
	Super::add_event(character_in);

}


void ADNLobbyAIController::remove_event(ADNCommonCharacter* character_in)
{
	Super::remove_event(character_in);
}



void ADNLobbyAIController::OnTargetDetected(AActor* actor, FAIStimulus const Stimulus)
{
	// 본인
	ADNUnEnemyCharacter* character = Cast<ADNUnEnemyCharacter>(GetPawn());
	// 타겟
	ADNCommonCharacter* insight_me_character = dynamic_cast<ADNCommonCharacter*>(actor);

	if (nullptr == actor)
	{
		get_blackboard()->SetValueAsBool(all_ai_bb_keys::can_see_enemy, false);
		get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, nullptr);

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I lost sight")));

	}

	if (nullptr == insight_me_character)
	{
		get_blackboard()->SetValueAsBool(all_ai_bb_keys::can_see_enemy, false);
		get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, nullptr);
		return;
	}

	if (nullptr == character)
		return;

	if (character->get_character_type() == E_CHARACTER_TYPE::CT_GRIFFIN)					// 그리핀일 경우
	{
		if (insight_me_character->get_character_type() == E_CHARACTER_TYPE::CT_ENEMY)		//적일 경우
		{
			get_blackboard()->SetValueAsBool(all_ai_bb_keys::can_see_enemy, true);
			get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, insight_me_character);

			//성공적으로 감지하면 블랙보드에 true값을 넣고 타겟 액터도 넣어준다.
			if (Stimulus.WasSuccessfullySensed())
			{
			}

		}
	}
	

}
