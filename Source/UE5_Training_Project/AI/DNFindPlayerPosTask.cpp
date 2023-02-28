
#include "UE5_Training_Project/AI/DNFindPlayerPosTask.h"

// Engine
#include <NavigationSystem.h>
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Vector.h>
#include <BehaviorTree/BlackboardComponent.h>

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"


// Character
#include "UE5_Training_Project/Character/DNPlayerCharacter.h"
#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"

// Component
#include <UE5_Training_Project/Component/DNStatusComponent.h>

// BlackBaord
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"




//
// 인형의 포지션에 따라 약간씩 위치가 다릅니다.
// 위치는 플레이어가 바라보는 기준으로 회전합니다. 
//

UDNFindPlayerPosTask::UDNFindPlayerPosTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("FindPlayerPosTask");

	// 캐릭터 포지션 데이터 테이블 초기화
	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterPositionDataObject(TEXT("/Game/Blueprint/Data/DT_DNCharacterPositionData"));
	if (CharacterPositionDataObject.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable Succeed!"));
		_position_datatable = CharacterPositionDataObject.Object;

		TArray<FDNCharacterPositionData*> data_array;	//사실 Num은 1개임
		_position_datatable->GetAllRows<FDNCharacterPositionData>("", data_array);

		for (auto& data : data_array)
		{
			_chartacter_position_data = data;
		}

	}
}


EBTNodeResult::Type UDNFindPlayerPosTask::ExecuteTask(UBehaviorTreeComponent& owner_comp_in, uint8* NodeMemory_in)
{
	Super::ExecuteTask(owner_comp_in, NodeMemory_in);

	auto Controller = Cast<ADNAIController>(owner_comp_in.GetAIOwner());
	auto self = Controller->GetPawn();

	ADNUnEnemyCharacter* self_actor = Cast<ADNUnEnemyCharacter>(self);
	ADNPlayerCharacter* player = dynamic_cast<ADNPlayerCharacter*>(GetWorld()->GetFirstPlayerController()->GetPawn());


	//현재 에디터에 설정된 navi mesh로 초기화
	UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (nullptr == NavSystem) {
		//navi mesh가 없다면 실패를 반환
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Enemy in Navi"));
		return EBTNodeResult::Failed;
	}



	FVector player_location = player->GetActorLocation();
	FNavLocation NextPatrol;
	FVector target_location;

	if (nullptr == self_actor)
		return EBTNodeResult::Failed;

	if(self_actor->get_status_component().Get()->_dead)
		return EBTNodeResult::Failed;



	if (self_actor->_squad_index == 1)
	{
		target_location = _chartacter_position_data->support_1;
	}
	else if (self_actor->_squad_index == 2)
	{
		target_location = _chartacter_position_data->support_2;
	}
	else if (self_actor->_squad_index == 3)
	{
		target_location = _chartacter_position_data->support_3;
	}
	else if (self_actor->_squad_index == 4)
	{
		target_location = _chartacter_position_data->guard_4;
	}
	else if (self_actor->_squad_index == 6)
	{
		target_location = _chartacter_position_data->guard_6;
	}
	else if (self_actor->_squad_index == 7)
	{
		target_location = _chartacter_position_data->rush_7;
	}
	else if (self_actor->_squad_index == 8)
	{
		target_location = _chartacter_position_data->rush_8;
	}
	else if (self_actor->_squad_index == 9)
	{
		target_location = _chartacter_position_data->rush_9;
	}



	//NextPatrol변수에 임의의 location 데이터를 넣고 다시 TargetLocation키의 value에 값을 넣어준다.
	if (NavSystem->GetRandomPointInNavigableRadius(player_location + target_location, _search_radius, NextPatrol, nullptr))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Next Patrol position :%s"), *NextPatrol.Location.ToString()));


		FVector new_vector = (NextPatrol.Location - player_location);
		FVector final_location = new_vector.RotateAngleAxis(player->GetControlRotation().Yaw, FVector::UpVector);
		Controller->get_blackboard()->SetValueAsVector(all_ai_bb_keys::target_location, final_location + player_location);

		//그 다음 이동할 곳을 확인하기 위한 디버그메시지
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("player rotation : %f"), player->GetControlRotation().Yaw));

	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("doll position : %s"), *(final_location + player_location).ToString()));
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("player position :%s"), *player_location.ToString()));


	}








	self_actor->set_idle_animation();

	return EBTNodeResult::Succeeded;
	
}