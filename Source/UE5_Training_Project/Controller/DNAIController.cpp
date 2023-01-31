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

// BlackBoard
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"



ADNAIController::ADNAIController(FObjectInitializer const& object_initializer)
{

	behavior_tree_component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	_blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	//Perception초기화
	SetPerceptionSystem();

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
			btree = BTObject;
			UE_LOG(LogTemp, Warning, TEXT("bt Griffin succeeded!"));
		}
	}
	else if (character->get_character_type() == E_CHARACTER_TYPE::CT_ENEMY)
	{
		UBehaviorTree* BTObject = LoadObject<UBehaviorTree>(NULL, TEXT("/Game/Blueprint/AI/BT_Combat_Enemy.BT_Combat_Enemy"), NULL, LOAD_None, NULL);
		if (nullptr != BTObject)
		{
			btree = BTObject;
			UE_LOG(LogTemp, Warning, TEXT("bt Enemy succeeded!"));
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
}

void ADNAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ADNAIController::OnUpdated(TArray<AActor*> const& updated_actors)
{

}

void ADNAIController::OnTargetDetected(AActor* actor, FAIStimulus const Stimulus)
{
	ADNCommonCharacter* character = dynamic_cast<ADNCommonCharacter*>(GetPawn());

	if (nullptr == actor)
	{
		get_blackboard()->SetValueAsBool(all_ai_bb_keys::can_see_enemy, false);
		get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, nullptr); 
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I lost sight")));

	}

		if (character->get_character_type() == E_CHARACTER_TYPE::CT_GRIFFIN)
		{
			ADNCommonCharacter* insight_me_character = dynamic_cast<ADNCommonCharacter*>(actor);

			if (insight_me_character->get_character_type() == E_CHARACTER_TYPE::CT_ENEMY)
			{
				//성공적으로 감지하면 블랙보드에 true값을 넣고 타겟 액터도 넣어준다.
				if (Stimulus.WasSuccessfullySensed())
				{
					get_blackboard()->SetValueAsBool(all_ai_bb_keys::can_see_enemy, true);
					get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, insight_me_character);
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I See %s"), insight_me_character));
				}

			}
		}
		else if (character->get_character_type() == E_CHARACTER_TYPE::CT_ENEMY)
		{
			ADNCommonCharacter* insight_me_character = dynamic_cast<ADNCommonCharacter*>(actor);
			if (insight_me_character->get_character_type() == E_CHARACTER_TYPE::CT_GRIFFIN ||
				insight_me_character->get_character_type() == E_CHARACTER_TYPE::CT_PLAYER)
			{
				//성공적으로 감지하면 블랙보드에 true값을 넣고 타겟 액터도 넣어준다.
				if (Stimulus.WasSuccessfullySensed())
				{
					get_blackboard()->SetValueAsBool(all_ai_bb_keys::can_see_enemy, true);
					get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, insight_me_character);
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("I See %s"), insight_me_character));
				}
			
			}
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
