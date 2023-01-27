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



const FName ADNAIController::HomePosKey(TEXT("HomePos"));
const FName ADNAIController::TargetLocation(TEXT("TargetLocation"));

ADNAIController::ADNAIController(FObjectInitializer const& object_initializer)
{
	//ConstructorHelpers로 에디터에 미리 만들어둔 비헤이비어트리를 지정
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Blueprint/AI/BT_Combat.BT_Combat"));

	//static ConstructorHelpers::FClassFinder<UBehaviorTree> BTObject(TEXT("/Game/Blueprint/AI/BT_Combat.BT_Combat_C"));
	if (BTObject.Succeeded())
	{
		btree = BTObject.Object;
		UE_LOG(LogTemp, Warning, TEXT("bt succeeded!"));
	}
	behavior_tree_component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	_blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	//Perception초기화
	SetPerceptionSystem();

}

void ADNAIController::OnPossess(APawn* pawn_in)
{
	Super::OnPossess(pawn_in);

	if (_blackboard)
	{
		//비헤이비어트리에 있는 블랙보드로 초기화
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

	if (character->get_character_type() == E_CHARACTER_TYPE::CT_GRIFFIN)
	{
		ADNCommonCharacter* insight_me_character = dynamic_cast<ADNCommonCharacter*>(actor);

		if (insight_me_character->get_character_type() == E_CHARACTER_TYPE::CT_ENEMY)
		{
			//성공적으로 감지하면 블랙보드에 true값을 넣어준다.
			get_blackboard()->SetValueAsBool(all_ai_bb_keys::can_see_enemy, Stimulus.WasSuccessfullySensed());
		}
	}
	else if (character->get_character_type() == E_CHARACTER_TYPE::CT_ENEMY)
	{
		ADNCommonCharacter* insight_me_character = dynamic_cast<ADNCommonCharacter*>(actor);
		if (insight_me_character->get_character_type() == E_CHARACTER_TYPE::CT_GRIFFIN ||
			insight_me_character->get_character_type() == E_CHARACTER_TYPE::CT_PLAYER)
		{
			//성공적으로 감지하면 블랙보드에 true값을 넣어준다.
			get_blackboard()->SetValueAsBool(all_ai_bb_keys::can_see_enemy, Stimulus.WasSuccessfullySensed());
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
