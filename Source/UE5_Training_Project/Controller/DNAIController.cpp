// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5_Training_Project/Controller/DNAIController.h"


// Engine
#include <BehaviorTree/BehaviorTree.h>
#include <NavigationSystem.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <BehaviorTree/BehaviorTreeComponent.h>
#include <Perception/AIPerceptionComponent.h>
#include <Perception/AISenseConfig_Sight.h>
#include <Perception/AIPerceptionStimuliSourceComponent.h>
#include <Perception/AIPerceptionComponent.h>

#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"
#include "UE5_Training_Project/Character/DNPlayerCharacter.h"
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"
#include "UE5_Training_Project/Character/DNEnemyCharacter.h"

// Component
#include "UE5_Training_Project/Component/DNStatusComponent.h"
#include "UE5_Training_Project/Character/Component/DNPlayerLineTrace.h"

// BlackBoard
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"



ADNAIController::ADNAIController(FObjectInitializer const& object_initializer)
{

	behavior_tree_component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	_blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	//Perception초기화
	SetPerceptionSystem();

}

void ADNAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ADNCommonCharacter* character = Cast<ADNCommonCharacter>(GetPawn());
	if (nullptr != character)
	{
		
		if (character->_status->_dead)
		{
			_blackboard->SetValueAsBool(all_ai_bb_keys::can_see_enemy, false);
			_blackboard->SetValueAsObject(all_ai_bb_keys::target_actor, nullptr);

			return;
		}


		ADNUnEnemyCharacter* doll = Cast<ADNUnEnemyCharacter>(character);
		if (nullptr != doll)
		{
			_blackboard->SetValueAsBool(all_ai_bb_keys::is_armed, doll->_is_armed_weapon);
			_blackboard->SetValueAsBool(all_ai_bb_keys::is_ordered, doll->_is_ordered);
		}

	}



}


void ADNAIController::OnPossess(APawn* pawn_in)
{
	Super::OnPossess(pawn_in);

	ADNCommonCharacter* character = dynamic_cast<ADNCommonCharacter*>(pawn_in);

	if (character->get_character_type() == E_CHARACTER_TYPE::CT_GRIFFIN)
	{
		UBehaviorTree* BTObject = LoadObject<UBehaviorTree>(NULL, TEXT("/Game/Blueprint/AI/BT_Combat_UnEnemy.BT_Combat_UnEnemy"), NULL, LOAD_None, NULL);
		if (nullptr != BTObject)
		{
			if(nullptr ==btree)
				btree = BTObject;
			UE_LOG(LogTemp, Warning, TEXT("bt Griffin succeeded!"));
		}


	}
	else if (character->get_character_type() == E_CHARACTER_TYPE::CT_HELI)
	{
		UBehaviorTree* BTObject = LoadObject<UBehaviorTree>(NULL, TEXT("/Game/Blueprint/AI/BT_Combat_Heli.BT_Combat_Heli"), NULL, LOAD_None, NULL);
		if (nullptr != BTObject)
		{
			if (nullptr == btree)
				btree = BTObject;
			UE_LOG(LogTemp, Warning, TEXT("bt Heli succeeded!"));
		}


	}
	else if (character->get_character_type() == E_CHARACTER_TYPE::CT_ENEMY)
	{
		ADNEnemyCharacter* enemy = Cast<ADNEnemyCharacter>(character);

		if (nullptr == enemy)
		{
			return;
		}
		else
		{
			if (enemy->_enemy_type == E_ENEMY_TYPE::ET_MELEE)
			{
				UBehaviorTree* BTObject = LoadObject<UBehaviorTree>(NULL, TEXT("/Game/Blueprint/AI/BT_Combat_Melee_Enemy.BT_Combat_Melee_Enemy"), NULL, LOAD_None, NULL);
				if (nullptr != BTObject)
				{
					if (nullptr == btree)
						btree = BTObject;
					UE_LOG(LogTemp, Warning, TEXT("bt Enemy succeeded!"));
				}
			}
			else if (enemy->_enemy_type == E_ENEMY_TYPE::ET_BOSS)
			{
				UBehaviorTree* BTObject = LoadObject<UBehaviorTree>(NULL, TEXT("/Game/Blueprint/AI/BT_Combat_Boss.BT_Combat_Boss"), NULL, LOAD_None, NULL);
				if (nullptr != BTObject)
				{
					if (nullptr == btree)
						btree = BTObject;
					_sight_config->SightRadius = 200000.f;
					UE_LOG(LogTemp, Warning, TEXT("bt Boss succeeded!"));
				}
			}
			else   //일단은 이런식으로 적군 타입에 따라 BT를 다르게 초기화합니다.
			{
				UBehaviorTree* BTObject = LoadObject<UBehaviorTree>(NULL, TEXT("/Game/Blueprint/AI/BT_Combat_Enemy.BT_Combat_Enemy"), NULL, LOAD_None, NULL);
				if (nullptr != BTObject)
				{
					if (nullptr == btree)
						btree = BTObject;
					UE_LOG(LogTemp, Warning, TEXT("bt Enemy succeeded!"));
				}
			}


			
			
		}
		
	}


	if (_blackboard)
	{
		//비헤이비어트리에 있는 블랙보드로 초기화
		if(nullptr != btree)
			_blackboard->InitializeBlackboard(*btree->BlackboardAsset);
	}


	RunBehaviorTree(btree);			//beginplay되면서 폰에 빙의될때 실행
	behavior_tree_component->StartTree(*btree);

	add_event(character);

	get_blackboard()->SetValueAsObject(all_ai_bb_keys::self_actor, pawn_in);
	get_blackboard()->SetValueAsVector(all_ai_bb_keys::guard_location, character->GetActorLocation());		//에디터 상에서 최초로 스폰한 지점이 가드 위치입니다. 가드가 아니어도 일단 저장해둡니다.

	_owner = character;		// 자주 사용하기 위해 담아둡니다.

}

void ADNAIController::OnUnPossess()
{
	Super::OnUnPossess();

	ADNCommonCharacter* character = dynamic_cast<ADNCommonCharacter*>(GetPawn());
	if(nullptr != character)
		remove_event(character);
}

void ADNAIController::OnUpdated(TArray<AActor*> const& updated_actors)
{

}

void ADNAIController::OnTargetDetected(AActor* actor, FAIStimulus const Stimulus)
{
	// 본인
	ADNCommonCharacter* character = Cast<ADNCommonCharacter>(GetPawn());
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

	if (character->get_character_type() == E_CHARACTER_TYPE::CT_GRIFFIN || 
		character->get_character_type() == E_CHARACTER_TYPE::CT_HELI)
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
		else                                                                               //적이 아닐 경우
		{
		}
	}
	else if (character->get_character_type() == E_CHARACTER_TYPE::CT_ENEMY)
	{
		if (insight_me_character->get_character_type() == E_CHARACTER_TYPE::CT_GRIFFIN ||
			insight_me_character->get_character_type() == E_CHARACTER_TYPE::CT_PLAYER)
		{
			get_blackboard()->SetValueAsBool(all_ai_bb_keys::can_see_enemy, true);
			get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, insight_me_character);

			//성공적으로 감지하면 블랙보드에 true값을 넣고 타겟 액터도 넣어준다.
			if (Stimulus.WasSuccessfullySensed())
			{
				
			}

		
		}
		else                                                                               //적이 아닐 경우
		{
		}
	}

	
}

void ADNAIController::add_event(ADNCommonCharacter* character_in)
{
	character_in->OnEmptyAmmo.AddDynamic(this, &ADNAIController::update_empty_ammo_handler);
	character_in->OnAtStartAmmo.AddDynamic(this, &ADNAIController::update_beginplay_ammo_handler);
	character_in->OnStopShotAmmo.AddDynamic(this, &ADNAIController::reset_target_handler);

}


void ADNAIController::remove_event(ADNCommonCharacter* character_in)
{
	character_in->OnEmptyAmmo.RemoveDynamic(this, &ADNAIController::update_empty_ammo_handler);
	character_in->OnAtStartAmmo.RemoveDynamic(this, &ADNAIController::update_beginplay_ammo_handler);
	character_in->OnStopShotAmmo.RemoveDynamic(this, &ADNAIController::reset_target_handler);
}

void ADNAIController::SetPerceptionSystem()
{
	_sight_config = CreateOptionalDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateOptionalDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception")));


	_sight_config->SightRadius = AISightRadius;
	_sight_config->LoseSightRadius = _sight_config->SightRadius + AILoseSightRadius;
	_sight_config->PeripheralVisionAngleDegrees = AIFieldOfView;
	_sight_config->SetMaxAge(AISightAge);
	_sight_config->AutoSuccessRangeFromLastSeenLocation = AILastSeenLocation;

	_sight_config->DetectionByAffiliation.bDetectEnemies = true;
	_sight_config->DetectionByAffiliation.bDetectNeutrals = true;
	_sight_config->DetectionByAffiliation.bDetectFriendlies = true;

	GetPerceptionComponent()->SetDominantSense(*_sight_config->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ADNAIController::OnTargetDetected);
	GetPerceptionComponent()->ConfigureSense(*_sight_config);
}


TObjectPtr<UBlackboardComponent> ADNAIController::get_blackboard() const
{
	if (nullptr == _blackboard)
		return nullptr;

	return _blackboard;
}


void ADNAIController::ordered_move(FVector destination_in, ADNUnEnemyCharacter* doll_in)
{
	_blackboard->SetValueAsEnum(all_ai_bb_keys::order_type, static_cast<uint8>(E_ORDER_TYPE::OT_MOVEHOLD));
	_blackboard->SetValueAsVector(all_ai_bb_keys::target_location, destination_in);
}


void ADNAIController::ordered_attack(ADNEnemyCharacter* enemy_in, ADNUnEnemyCharacter* doll_in)
{
	_blackboard->SetValueAsEnum(all_ai_bb_keys::order_type, static_cast<uint8>(E_ORDER_TYPE::OT_ATTACK));
	_blackboard->SetValueAsObject(all_ai_bb_keys::target_actor, enemy_in);		//can_see_enemy는 그대로이므로 볼수있을때 사격
}

void ADNAIController::order_stop()
{
	_blackboard->SetValueAsEnum(all_ai_bb_keys::order_type, static_cast<uint8>(E_ORDER_TYPE::OT_NONE));
}

void ADNAIController::update_empty_ammo_handler()
{
	get_blackboard()->SetValueAsInt(all_ai_bb_keys::has_ammo, 0);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Update empty Ammo!!")));
}


void ADNAIController::update_get_ammo_handler(int64 count_in)
{
	int64 ammo_count = get_blackboard()->GetValueAsInt(all_ai_bb_keys::has_ammo) + count_in;
	get_blackboard()->SetValueAsInt(all_ai_bb_keys::has_ammo, ammo_count);
}

void ADNAIController::update_beginplay_ammo_handler(int64 count_in)
{
	get_blackboard()->SetValueAsInt(all_ai_bb_keys::has_ammo, count_in);
}


void ADNAIController::reset_target_handler()
{
	get_blackboard()->SetValueAsBool(all_ai_bb_keys::can_see_enemy, false);
	get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, nullptr);
}
