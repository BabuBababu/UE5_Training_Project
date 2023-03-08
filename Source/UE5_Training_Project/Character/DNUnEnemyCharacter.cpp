// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5_Training_Project/Character/DNUnEnemyCharacter.h"

// Character
#include "UE5_Training_Project/Character/DNPlayerCharacter.h"

// AnimInstance
#include "UE5_Training_Project/Character/Animation/DNCharacterAnimInstance.h"

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// Component
#include "UE5_Training_Project/Character/Component/DNPlayerLineTrace.h"

// Manager
#include "UE5_Training_Project/Manager/DNObjectManager.h"
#include "UE5_Training_Project/UI/Manager/DNWidgetManager.h"
#include "UE5_Training_Project/Manager/DNUIManager.h"

// UI
#include "UE5_Training_Project/UI/Widget/Panel/DNCommentPanel.h"


#define MAX_SUQAD_POSITION_NUMBER 10


/// <summary>
///	하.. 죽거나 무슨 이벤트가 발생할 때 하나로 모아서 델리게이트로 다같이 쏴주면되는데
/// 여기서 호출하고 저기서 호출하고 저쪽에서도 호출하고 이러면 관리가 너무 안돼
/// </summary>



ADNUnEnemyCharacter::ADNUnEnemyCharacter()
{
	


	init_base();
	init_ai();

	

}


void ADNUnEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	_is_attacking = false;

	if (_squad_index >= 0)
	{
		if (_squad_index < MAX_SUQAD_POSITION_NUMBER)							//인덱스가 10을 넘는다면 오류
			OBJECT_MANAGER->_in_squad_doll_array[_squad_index] = this;			//시작시 스쿼드 인덱스 기준으로 오브젝트 매니저에 넣어줍니다.

	}

	OBJECT_MANAGER->_griffin_player_array.Add(this);
}

void ADNUnEnemyCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	remove_event();

	Super::EndPlay(EndPlayReason);
}

void ADNUnEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ADNUnEnemyCharacter::add_event()
{
	Super::add_event();

	ADNPlayerCharacter* player = dynamic_cast<ADNPlayerCharacter*>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (nullptr == player)
		return;

	player->on_armed.AddDynamic(this, &ADNUnEnemyCharacter::change_armed_state_handler);
	player->on_crouch.AddDynamic(this, &ADNUnEnemyCharacter::change_crouch_state_handler);
	player->on_sprint.AddDynamic(this, &ADNUnEnemyCharacter::change_sprint_state_handler);

	player->OnOrderMove.AddDynamic(this, &ADNUnEnemyCharacter::order_move_handler);
	player->OnOrderAttack.AddDynamic(this, &ADNUnEnemyCharacter::order_attack_handler);
}

void ADNUnEnemyCharacter::remove_event()
{
	Super::remove_event();
	//ADNPlayerCharacter* player = dynamic_cast<ADNPlayerCharacter*>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//player->on_armed.RemoveDynamic(this, &ADNUnEnemyCharacter::change_armed_state_handler);
	//player->on_crouch.RemoveDynamic(this, &ADNUnEnemyCharacter::change_crouch_state_handler);
	//player->on_sprint.RemoveDynamic(this, &ADNUnEnemyCharacter::change_sprint_state_handler);
	//player->OnOrderMove.RemoveDynamic(this, &ADNUnEnemyCharacter::order_move_handler);
	//player->OnOrderAttack.RemoveDynamic(this, &ADNUnEnemyCharacter::order_attack_handler);
}



void ADNUnEnemyCharacter::init_ai()
{
	AIControllerClass = ADNAIController::StaticClass();		//엔진 초기화 단계에서 생성해줘야하므로 StaticClass
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}


void ADNUnEnemyCharacter::init_base()
{
	_character_type = E_CHARACTER_TYPE::CT_GRIFFIN;
	_squad_index = -1;			//초기 인덱스는 -1로
	_is_in_squad = true;		//원래는 false로 하고 ui에서 스쿼드 배치가 되면 true바꿔줘야함! 일단은 테스트를 위해 true로!
	_is_ordered = false;

}


void ADNUnEnemyCharacter::fire()
{
	// 여기엔 다른 효과나 기능들을 넣으면 될듯
	Super::fire();
}

void ADNUnEnemyCharacter::set_attack_finish()
{

}


void ADNUnEnemyCharacter::change_armed_state_handler(bool armed_in)
{
	if (true == armed_in)
	{
		bUseControllerRotationYaw = true;
		_weapon_armed->SetVisibility(true);
		_weapon_un_armed->SetVisibility(false);
		_is_armed_weapon = true;
		_pre_upper_character_state = _character_state;
		_character_state = E_CHARACTER_STATE::CS_ARM;
	}
	else
	{
		bUseControllerRotationYaw = false;
		_weapon_armed->SetVisibility(false);
		_weapon_un_armed->SetVisibility(true);
		_is_armed_weapon = false;
		_character_state = _pre_upper_character_state;
	}
}


void ADNUnEnemyCharacter::change_crouch_state_handler(bool crouch_in)
{
	_is_crouch = crouch_in;
}

void ADNUnEnemyCharacter::change_sprint_state_handler(bool sprint_in)
{
	if (sprint_in)
		sprint();
	else
		stop_sprint();
}

void ADNUnEnemyCharacter::order_move_handler(FVector destination_in, ADNUnEnemyCharacter* doll_in)
{
	if (this != doll_in)
		return;

	ADNAIController* controller = Cast<ADNAIController>(GetController());
	if (nullptr != controller)
	{
		controller->ordered_move(destination_in, doll_in);
		_is_ordered = true;
		// 여기에 캐릭터 코멘트 UI 호출
		//WIDGET_MANAGER->
	}
}

void ADNUnEnemyCharacter::order_attack_handler(ADNEnemyCharacter* enemy_in, ADNUnEnemyCharacter* doll_in)
{
	if (this != doll_in)
		return;

	ADNAIController* controller = Cast<ADNAIController>(GetController());
	if (nullptr != controller)
	{
		controller->ordered_attack(enemy_in, doll_in);
		_is_ordered = true;
	}
}


void ADNUnEnemyCharacter::order_stop_handler()
{

	ADNAIController* controller = Cast<ADNAIController>(GetController());
	if (nullptr != controller)
	{
		controller->order_stop();
		_is_ordered = false;
	}
}