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
#include "UE5_Training_Project/Character/DNRaptureResVolitansCharacter.h"

// Actor
#include "UE5_Training_Project/Actor/DNBossMissile.h"

// Component
#include "UE5_Training_Project/Component/DNStatusComponent.h"
#include "UE5_Training_Project/Character/Component/DNPlayerLineTrace.h"

// BlackBoard
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"



ADNAIController::ADNAIController(FObjectInitializer const& object_initializer)
{

	behavior_tree_component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	_blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
	_target_array.Empty();

	//Perception초기화
	SetPerceptionSystem();

}

void ADNAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
}


void ADNAIController::OnPossess(APawn* pawn_in)
{
	Super::OnPossess(pawn_in);

	ADNCommonCharacter* character = Cast<ADNCommonCharacter>(pawn_in);

	if (false == IsValid(character))
		return;

	if (character->get_character_type() == E_CHARACTER_TYPE::CT_GRIFFIN)
	{
		UBehaviorTree* BTObject = LoadObject<UBehaviorTree>(NULL, TEXT("/Game/Blueprint/AI/BT_Combat_UnEnemy.BT_Combat_UnEnemy"), NULL, LOAD_None, NULL);
		if (nullptr != BTObject)
		{
			if(nullptr ==btree)
				btree = BTObject;
			UE_LOG(LogTemp, Warning, TEXT("bt Griffin succeeded!"));
		}

		// 아군 전투AI에서는 항상 IDLE상태
		character->_character_origin_state = E_CHARACTER_STATE::CS_IDLE;

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

		// 아군 전투AI에서는 항상 IDLE상태
		character->_character_origin_state = E_CHARACTER_STATE::CS_IDLE;

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
					UE_LOG(LogTemp, Warning, TEXT("bt Melee succeeded!"));
				}
			}
			else if (enemy->_enemy_type == E_ENEMY_TYPE::ET_BOSS)			//랩쳐 스프레드
			{
				UBehaviorTree* BTObject = LoadObject<UBehaviorTree>(NULL, TEXT("/Game/Blueprint/AI/BT_Combat_Boss.BT_Combat_Boss"), NULL, LOAD_None, NULL);
				if (nullptr != BTObject)
				{
					if (nullptr == btree)
						btree = BTObject;
					_sight_config->SightRadius = 200000.f;
					UE_LOG(LogTemp, Warning, TEXT("bt Boss Spread succeeded!"));
				}
			}
			else if (enemy->_enemy_type == E_ENEMY_TYPE::ET_BOSS_RESVOLITAN)			//랩쳐 레스볼리탄
			{
				UBehaviorTree* BTObject = LoadObject<UBehaviorTree>(NULL, TEXT("/Game/Blueprint/AI/BT_Combat_Rapture_ResVolitans.BT_Combat_Rapture_ResVolitans"), NULL, LOAD_None, NULL);
				if (nullptr != BTObject)
				{
					if (nullptr == btree)
						btree = BTObject;
					_sight_config->SightRadius = 200000.f;
					UE_LOG(LogTemp, Warning, TEXT("bt Boss ResVolitans succeeded!"));
				}
			}
			else if (enemy->_enemy_type == E_ENEMY_TYPE::ET_RANGER_LC)		//랩쳐 큐브 
			{
				UBehaviorTree* BTObject = LoadObject<UBehaviorTree>(NULL, TEXT("/Game/Blueprint/AI/BT_Combat_Rapture_Cube.BT_Combat_Rapture_Cube"), NULL, LOAD_None, NULL);
				if (nullptr != BTObject)
				{
					if (nullptr == btree)
						btree = BTObject;
					_sight_config->SightRadius = 200000.f;
					UE_LOG(LogTemp, Warning, TEXT("bt Rapture_LC succeeded!"));
				}
			}
			else if (enemy->_enemy_type == E_ENEMY_TYPE::ET_AIR_LC)		//랩쳐 디스커스
			{
				UBehaviorTree* BTObject = LoadObject<UBehaviorTree>(NULL, TEXT("/Game/Blueprint/AI/BT_Combat_Rapture_Discus.BT_Combat_Rapture_Discus"), NULL, LOAD_None, NULL);
				if (nullptr != BTObject)
				{
					if (nullptr == btree)
						btree = BTObject;
					_sight_config->SightRadius = 200000.f;
					UE_LOG(LogTemp, Warning, TEXT("bt AIR_LC succeeded!"));
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

	// behavior_tree_component->StartTree(*btree);를 넣으면 터짐

	RunBehaviorTree(btree);			//beginplay되면서 폰에 빙의될때 실행
	//behavior_tree_component->StartTree(*btree);

	if(nullptr != character)
		add_event(character);

	get_blackboard()->SetValueAsObject(all_ai_bb_keys::self_actor, pawn_in);
	
																										
	_owner = character;		// 자주 사용하기 위해 담아둡니다.

}

void ADNAIController::OnUnPossess()
{
	Super::OnUnPossess();

	ADNUnEnemyCharacter* character = Cast<ADNUnEnemyCharacter>(GetPawn());
	if(nullptr != character)
		remove_event(character);


	ADNEnemyCharacter* enemy = Cast<ADNEnemyCharacter>(GetPawn());
	if (nullptr != character)
		remove_event(enemy);



	behavior_tree_component->StopTree();
	btree = nullptr;
}

void ADNAIController::OnUpdated(TArray<AActor*> const& updated_actors)
{
}

void ADNAIController::OnTargetDetected(AActor* actor, FAIStimulus const Stimulus)
{
	// 본인
	ADNCommonCharacter* character = Cast<ADNCommonCharacter>(GetPawn());
	// 캐릭터
	ADNCommonCharacter* insight_me_character = Cast<ADNCommonCharacter>(actor);
	// 미사일
	ADNBossMissile* missile = Cast<ADNBossMissile>(actor);


	if (nullptr == character)
		return;

	

	if (character->get_character_type() == E_CHARACTER_TYPE::CT_GRIFFIN)       // 인형
	{
		if (nullptr == insight_me_character)
		{
			//혹시 공중보스?
			ADNRaptureResVolitansCharacter* other_character = Cast<ADNRaptureResVolitansCharacter>(actor);
			if (IsValid(other_character))
			{
				if (false == _target_array.Contains(other_character))
				{
					other_character->OnDeadForTarget.AddDynamic(this, &ADNAIController::remove_target_from_array_handler);
					_target_array.Add(other_character);

					return;
				}
			}
				
		}
		else
		{
			if (insight_me_character->get_character_type() == E_CHARACTER_TYPE::CT_ENEMY)
			{
				if (IsValid(insight_me_character))		//유효성 체크
				{
					if (false == _target_array.Contains(insight_me_character))
					{
						if (false == insight_me_character->OnDeadForTarget.IsBound())
							insight_me_character->OnDeadForTarget.AddDynamic(this, &ADNAIController::remove_target_from_array_handler);

						_target_array.Add(insight_me_character);

						//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("target name : %s"), *insight_me_character->GetName()));

					}
				}


			}
		}



		// 타겟이 저장될 때 벽근처에 있는지 아니라면 벽으로 이동할 필요가 있는지 체크
		if (false == character->_is_near_wall)
			get_blackboard()->SetValueAsBool(all_ai_bb_keys::need_move, true);
		else
			get_blackboard()->SetValueAsBool(all_ai_bb_keys::need_move, false);
		
	}
	else if (character->get_character_type() == E_CHARACTER_TYPE::CT_HELI)
	{
		if (nullptr == insight_me_character)
		{
			//혹시 공중보스?
			ADNRaptureResVolitansCharacter* other_character = Cast<ADNRaptureResVolitansCharacter>(actor);
			if (nullptr != other_character)
				get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, other_character);

			return;
		}
		else
		{
			if (insight_me_character->get_character_type() == E_CHARACTER_TYPE::CT_ENEMY)
				get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, insight_me_character);
		}
	}
	else if (character->get_character_type() == E_CHARACTER_TYPE::CT_ENEMY) // 적
	{

		if (nullptr == insight_me_character)
			return;

		if (insight_me_character->get_character_type() == E_CHARACTER_TYPE::CT_GRIFFIN ||
			insight_me_character->get_character_type() == E_CHARACTER_TYPE::CT_PLAYER)
		{
			get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, insight_me_character);

			//성공적으로 감지하면 블랙보드에 true값을 넣고 타겟 액터도 넣어준다.
			if (Stimulus.WasSuccessfullySensed())
			{
				
			}

		
		}
		else                                                                              
		{
		}
	}

}

void ADNAIController::add_event(ADNCommonCharacter* character_in)
{
	character_in->OnEmptyAmmo.AddDynamic(this, &ADNAIController::update_empty_ammo_handler);
	character_in->OnAtStartAmmo.AddDynamic(this, &ADNAIController::update_beginplay_ammo_handler);
	character_in->OnStopShotAmmo.AddDynamic(this, &ADNAIController::reset_target_handler);

	character_in->OnDead.AddDynamic(this, &ADNAIController::reset_target_handler);

	// 인형이라면
	if (character_in->_character_type == E_CHARACTER_TYPE::CT_GRIFFIN)
	{
		ADNUnEnemyCharacter* character = Cast<ADNUnEnemyCharacter>(character_in);
		if (nullptr != character)
		{
			character->OnOrdered.AddDynamic(this, &ADNAIController::update_ordered_handler);
			character->OnArmed.AddDynamic(this, &ADNAIController::update_armed_handler);
		}
		character_in->OnTargetDead.AddDynamic(this, &ADNAIController::check_need_move_handler);
	}
}


void ADNAIController::remove_event(ADNCommonCharacter* character_in)
{
	character_in->OnEmptyAmmo.RemoveDynamic(this, &ADNAIController::update_empty_ammo_handler);
	character_in->OnAtStartAmmo.RemoveDynamic(this, &ADNAIController::update_beginplay_ammo_handler);
	character_in->OnStopShotAmmo.RemoveDynamic(this, &ADNAIController::reset_target_handler);


	// 인형이라면
	if (character_in->_character_type == E_CHARACTER_TYPE::CT_GRIFFIN)
	{
		ADNUnEnemyCharacter* character = Cast<ADNUnEnemyCharacter>(character_in);
		if (nullptr != character)
		{
			character->OnOrdered.RemoveDynamic(this, &ADNAIController::update_ordered_handler);
			character->OnArmed.RemoveDynamic(this, &ADNAIController::update_armed_handler);
		}
		character_in->OnTargetDead.RemoveDynamic(this, &ADNAIController::check_need_move_handler);

	}
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
	if (IsValid(enemy_in))
	{
		if (false == _target_array.Contains(enemy_in))
		{
			if (false == enemy_in->OnDeadForTarget.IsBound())
				enemy_in->OnDeadForTarget.AddDynamic(this, &ADNAIController::remove_target_from_array_handler);

			_target_array.Add(enemy_in);
		}

		_blackboard->SetValueAsEnum(all_ai_bb_keys::order_type, static_cast<uint8>(E_ORDER_TYPE::OT_ATTACK));
		_blackboard->SetValueAsObject(all_ai_bb_keys::target_actor, enemy_in);
	}
	
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
	_target_array.Empty();
	get_blackboard()->SetValueAsBool(all_ai_bb_keys::is_find_target, false);
	get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, nullptr);

}



void ADNAIController::check_need_move_handler()	//사용안하는중
{
	ADNCommonCharacter* character = Cast<ADNCommonCharacter>(GetPawn());

	if (nullptr == character)
		return;

	if (false == character->_is_near_wall)	// 벽근처가 아니라면 움직임 가능하게 하고 리턴합니다.
	{
		get_blackboard()->SetValueAsBool(all_ai_bb_keys::need_move, true);
		return;
	}

	auto* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (nullptr != player && nullptr != character)
	{
		if (GetPawn()->GetDistanceTo(player) >= character->_need_move_distance)		// 벽근처에서 싸운 이후 플레이어와 멀어져있다면 움직임 가능하게합니다.
		{
			get_blackboard()->SetValueAsBool(all_ai_bb_keys::need_move, true);
		}
		else
			get_blackboard()->SetValueAsBool(all_ai_bb_keys::need_move, false);
	}
}

void ADNAIController::update_armed_handler(bool flag_in)
{
	ADNCommonCharacter* character = Cast<ADNCommonCharacter>(GetPawn());

	if (nullptr == character)
		return;

	ADNUnEnemyCharacter* doll = Cast<ADNUnEnemyCharacter>(character);

	if (nullptr != doll)
	{
		_blackboard->SetValueAsBool(all_ai_bb_keys::is_armed, doll->_is_armed_weapon);
	}
	if (false == flag_in)
	{
		character->_character_state = E_CHARACTER_STATE::CS_IDLE;
		character->_pre_upper_character_state = E_CHARACTER_STATE::CS_IDLE;
	}
}

void ADNAIController::update_ordered_handler(bool flag_in)
{
	ADNCommonCharacter* character = Cast<ADNCommonCharacter>(GetPawn());
	if (nullptr == character)
		return;

	ADNUnEnemyCharacter* doll = Cast<ADNUnEnemyCharacter>(character);
	if (nullptr != doll)
	{
		_blackboard->SetValueAsBool(all_ai_bb_keys::is_ordered, doll->_is_ordered);
	}
}

void ADNAIController::remove_target_from_array_handler(AActor* actor_in)
{

	// 파괴되는 액터가 원래 타겟이었다면 nullptr로 초기화
	if (actor_in == get_blackboard()->GetValueAsObject(all_ai_bb_keys::target_actor))
	{
		get_blackboard()->SetValueAsBool(all_ai_bb_keys::is_find_target, false);
		get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, nullptr);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("remove_target_from_array_handler!!!!!"));
	}


	TArray<AActor*> temp_array;
	temp_array.Empty();


	// 임시 배열에 유효한 타겟을 저장.
	for (auto& target : _target_array)
	{
		if (IsValid(target))
		{
			temp_array.Add(target);
		}
	}

	// 임시 배열에서 파괴된 액터 삭제
	for (int index = 0; index < temp_array.Num(); ++index)
	{
		if (temp_array[index] == actor_in)
		{
			temp_array.RemoveAt(index);
			break;
		}
	}

	// 원래 타겟 배열에 계산해놓은 임시 배열로 초기화
	_target_array = temp_array;




	//// 타겟이 캐릭터였을 경우만 애니메이션 초기화
	//ADNCommonCharacter* target = Cast<ADNCommonCharacter>(actor_in);
	//if(nullptr != target)
	//	_owner->set_idle_animation();

	
	GetAIPerceptionComponent()->UpdatePerceptionWhitelist(_sight_config->GetSenseID(), true);
}