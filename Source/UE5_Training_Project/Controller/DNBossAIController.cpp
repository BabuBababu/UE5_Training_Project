


#include "UE5_Training_Project/Controller/DNBossAIController.h"


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
#include "UE5_Training_Project/Character/DNCommonBossCharacter.h"



void ADNBossAIController::OnPossess(APawn* pawn_in)
{
	ADNCommonBossCharacter* character = Cast<ADNCommonBossCharacter>(pawn_in);

	if (character->get_character_type() == E_CHARACTER_TYPE::CT_ENEMY)
	{
		UBehaviorTree* BTObject = LoadObject<UBehaviorTree>(NULL, TEXT("/Game/Blueprint/AI/BT_Combat_Boss.BT_Combat_Boss"), NULL, LOAD_None, NULL);
		if (nullptr != BTObject)
		{
			btree = BTObject;
			UE_LOG(LogTemp, Warning, TEXT("bt Boss succeeded!"));
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



void ADNBossAIController::OnTargetDetected(AActor* actor, FAIStimulus const Stimulus)
{
	// 본인
	ADNCommonBossCharacter* character = Cast<ADNCommonBossCharacter>(GetPawn());
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

	if (insight_me_character->get_character_type() == E_CHARACTER_TYPE::CT_GRIFFIN
		|| insight_me_character->get_character_type() == E_CHARACTER_TYPE::CT_PLAYER)		//그리핀,플레이어일 경우
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
