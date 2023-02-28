﻿


#include "UE5_Training_Project/AI/DNHeliMoveToTask.h"


// Engine
#include <NavigationSystem.h>
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Vector.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <GameFramework/FloatingPawnMovement.h>

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// Character
#include "UE5_Training_Project/Character/DNHeliCommonCharacter.h"

// BlackBaord
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"






UDNHeliMoveToTask::UDNHeliMoveToTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("HeliMoveToTask");
	self_actor = nullptr;
	controller = nullptr;
}



EBTNodeResult::Type UDNHeliMoveToTask::ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in)
{
	Super::ExecuteTask(owner_comp_in, NodeMemory_in);

	bNotifyTick = true; //틱 태스크 활성화

	controller = Cast<ADNAIController>(owner_comp_in.GetAIOwner());
	auto self = controller->GetPawn();
	self_actor = Cast<ADNHeliCommonCharacter>(self);

	FVector location = controller->get_blackboard()->GetValueAsVector(all_ai_bb_keys::target_location);
	target_location = FVector(location.X, location.Y, 0.f);

	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Tick using now!!!"));

	return EBTNodeResult::InProgress;

}


void UDNHeliMoveToTask::TickTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in, float DeltaSeconds)
{
	Super::TickTask(owner_comp_in, NodeMemory_in, DeltaSeconds);



	if (is_moving_complete(owner_comp_in))
	{
		// 다음 노드로 이동합니다.
		FinishLatentTask(owner_comp_in, EBTNodeResult::Succeeded);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Tick Succeed"));
	}
	else
	{
		// 이동이 완료되지 않았으면 계속 실행합니다.
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Tick is Fail"));
		Super::TickTask(owner_comp_in,NodeMemory_in,DeltaSeconds);
	}

	


	auto self = controller->GetPawn();
	FVector origin = self->GetActorLocation();
	FVector origin_location = FVector(origin.X, origin.Y, 0.f);

	self_actor->_floting_movement->AddInputVector(target_location - origin_location);
}

bool UDNHeliMoveToTask::is_moving_complete(UBehaviorTreeComponent& owner_comp_in)
{

	auto self = controller->GetPawn();
	FVector origin = self->GetActorLocation();
	FVector origin_location = FVector(origin.X, origin.Y, 0.f);


	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Tick is moving complete??"));

	// 이동이 완료되었으면 true를 반환합니다.
	return FVector::Distance(origin_location, target_location) < 100.f;
}
