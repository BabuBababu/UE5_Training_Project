


#include "UE5_Training_Project/Controller/DNHeliAIController.h"

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
#include "UE5_Training_Project/Character/DNHeliCommonCharacter.h"



void ADNHeliAIController::OnPossess(APawn* pawn_in)
{
	ADNCommonCharacter* character = Cast<ADNCommonCharacter>(pawn_in);

	if (character->get_character_type() == E_CHARACTER_TYPE::CT_GRIFFIN)
	{
		UBehaviorTree* BTObject = LoadObject<UBehaviorTree>(NULL, TEXT("/Game/Blueprint/AI/BT_Combat_Heli.BT_Combat_Heli"), NULL, LOAD_None, NULL);
		if (nullptr != BTObject)
		{
			btree = BTObject;
			UE_LOG(LogTemp, Warning, TEXT("bt Heli succeeded!"));
		}


	}

	if (_blackboard)
	{
		//비헤이비어트리에 있는 블랙보드로 초기화
		if (nullptr != btree)
			_blackboard->InitializeBlackboard(*btree->BlackboardAsset);
	}


	RunBehaviorTree(btree);			//beginplay되면서 폰에 빙의될때 실행
	behavior_tree_component->StartTree(*btree);

	get_blackboard()->SetValueAsObject(all_ai_bb_keys::self_actor, pawn_in);

}



void ADNHeliAIController::OnTargetDetected(AActor* actor, FAIStimulus const Stimulus)
{
	// 본인
	ADNHeliCommonCharacter* character = Cast<ADNHeliCommonCharacter>(GetPawn());
	// 타겟
	ADNCommonCharacter* insight_me_character = dynamic_cast<ADNCommonCharacter*>(actor);

	if (nullptr == actor)
	{
		//get_blackboard()->SetValueAsBool(all_ai_bb_keys::can_see_enemy, false);
		get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, nullptr);

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I lost sight")));

	}

	if (nullptr == insight_me_character)
	{
		//get_blackboard()->SetValueAsBool(all_ai_bb_keys::can_see_enemy, false);
		get_blackboard()->SetValueAsObject(all_ai_bb_keys::target_actor, nullptr);
		return;
	}

	if (nullptr == character)
		return;

	if (character->get_character_type() == E_CHARACTER_TYPE::CT_GRIFFIN)					// 그리핀 헬기일 경우
	{
		if (insight_me_character->get_character_type() == E_CHARACTER_TYPE::CT_ENEMY)		//적일 경우
		{
			//get_blackboard()->SetValueAsBool(all_ai_bb_keys::can_see_enemy, true);
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
	else if (character->get_character_type() == E_CHARACTER_TYPE::CT_ENEMY)					//적군 헬기일 경우
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
