


#include "UE5_Training_Project/Actor/Wall/DNCommonWall.h"

// Engine
#include <Components/BoxComponent.h>
#include <BehaviorTree/BlackboardComponent.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"


ADNCommonWall::ADNCommonWall()
{
	_left_box_collision_f = CreateDefaultSubobject<UBoxComponent>(TEXT("frontleftCollision"));
	_left_box_collision_f->SetupAttachment(RootComponent);

	_right_box_collision_f = CreateDefaultSubobject<UBoxComponent>(TEXT("frontrightCollision"));
	_right_box_collision_f->SetupAttachment(RootComponent);

	_left_box_collision_b = CreateDefaultSubobject<UBoxComponent>(TEXT("backleftCollision"));
	_left_box_collision_b->SetupAttachment(RootComponent);

	_right_box_collision_b = CreateDefaultSubobject<UBoxComponent>(TEXT("backrightCollision"));
	_right_box_collision_b->SetupAttachment(RootComponent);
}

void ADNCommonWall::BeginPlay()
{
	Super::BeginPlay();

	add_event();
}


void ADNCommonWall::add_event()
{
	if (nullptr == _box_collision)
		return;

	if (nullptr == _left_box_collision_f)
		return;

	if (nullptr == _right_box_collision_f)
		return;

	_box_collision->OnComponentBeginOverlap.AddDynamic(this, &ADNCommonWall::overlap_wall_handler);
	_box_collision->OnComponentEndOverlap.AddDynamic(this, &ADNCommonWall::unoverlap_wall_handler);
	_left_box_collision_f->OnComponentBeginOverlap.AddDynamic(this, &ADNCommonWall::overlap_left_collision_handler);
	_left_box_collision_f->OnComponentEndOverlap.AddDynamic(this, &ADNCommonWall::unoverlap_left_collision_handler);
	_right_box_collision_f->OnComponentBeginOverlap.AddDynamic(this, &ADNCommonWall::overlap_right_collision_handler);
	_right_box_collision_f->OnComponentEndOverlap.AddDynamic(this, &ADNCommonWall::unoverlap_right_collision_handler);
	_left_box_collision_b->OnComponentBeginOverlap.AddDynamic(this, &ADNCommonWall::overlap_left_collision_handler);
	_left_box_collision_b->OnComponentEndOverlap.AddDynamic(this, &ADNCommonWall::unoverlap_left_collision_handler);
	_right_box_collision_b->OnComponentBeginOverlap.AddDynamic(this, &ADNCommonWall::overlap_right_collision_handler);
	_right_box_collision_b->OnComponentEndOverlap.AddDynamic(this, &ADNCommonWall::unoverlap_right_collision_handler);

}


void ADNCommonWall::remove_event()
{
	if (nullptr == _box_collision)
		return;

	if (nullptr == _left_box_collision_f)
		return;

	if (nullptr == _right_box_collision_f)
		return;

	_box_collision->OnComponentBeginOverlap.RemoveDynamic(this, &ADNCommonWall::overlap_wall_handler);
	_box_collision->OnComponentEndOverlap.RemoveDynamic(this, &ADNCommonWall::unoverlap_wall_handler);
	_left_box_collision_f->OnComponentBeginOverlap.RemoveDynamic(this, &ADNCommonWall::overlap_left_collision_handler);
	_left_box_collision_f->OnComponentEndOverlap.RemoveDynamic(this, &ADNCommonWall::unoverlap_left_collision_handler);
	_right_box_collision_f->OnComponentBeginOverlap.RemoveDynamic(this, &ADNCommonWall::overlap_right_collision_handler);
	_right_box_collision_f->OnComponentEndOverlap.RemoveDynamic(this, &ADNCommonWall::unoverlap_right_collision_handler);
	_left_box_collision_b->OnComponentBeginOverlap.AddDynamic(this, &ADNCommonWall::overlap_left_collision_handler);
	_left_box_collision_b->OnComponentEndOverlap.AddDynamic(this, &ADNCommonWall::unoverlap_left_collision_handler);
	_right_box_collision_b->OnComponentBeginOverlap.AddDynamic(this, &ADNCommonWall::overlap_right_collision_handler);
	_right_box_collision_b->OnComponentEndOverlap.AddDynamic(this, &ADNCommonWall::unoverlap_right_collision_handler);

}

void ADNCommonWall::Tick(float DeltaTime)
{

}


void ADNCommonWall::overlap_wall_handler(class UPrimitiveComponent* selfComp, class AActor* otherActor, UPrimitiveComponent* otherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADNCommonCharacter* character = Cast<ADNCommonCharacter>(otherActor);

	if (nullptr == character)
		return;


	character->_is_near_wall = true;

	ADNAIController* ai_controller = Cast<ADNAIController>(character->GetController());
	if(nullptr != ai_controller)
		ai_controller->get_blackboard()->SetValueAsBool("IsNearbyWall", true);

	//UE_LOG(LogTemp, Warning, TEXT("Wall Overlap actor is %s"), *otherActor->GetName());
}


void ADNCommonWall::unoverlap_wall_handler(UPrimitiveComponent* OverlappedComp, AActor* otherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	ADNCommonCharacter* character = Cast<ADNCommonCharacter>(otherActor);

	if (nullptr == character)
		return;

	character->_is_near_wall = false;
	character->_cover_now = false;

	character->set_default_all_speed(true);
	character->set_camera_transform_origin();

	if(character->_character_state == E_CHARACTER_STATE::CS_COVER)
		character->_character_state = E_CHARACTER_STATE::CS_ARM;

	ADNAIController* ai_controller = Cast<ADNAIController>(character->GetController());
	if (nullptr != ai_controller)
		ai_controller->get_blackboard()->SetValueAsBool("IsNearbyWall", false);

	//UE_LOG(LogTemp, Warning, TEXT("Wall Un Overlap actor is %s"), *otherActor->GetName());
}



void ADNCommonWall::overlap_left_collision_handler(class UPrimitiveComponent* selfComp, class AActor* otherActor, UPrimitiveComponent* otherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADNCommonCharacter* character = Cast<ADNCommonCharacter>(otherActor);

	if (nullptr == character)
		return;

	character->_cover_left = true;
}


void ADNCommonWall::unoverlap_left_collision_handler(UPrimitiveComponent* OverlappedComp, AActor* otherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ADNCommonCharacter* character = Cast<ADNCommonCharacter>(otherActor);

	if (nullptr == character)
		return;

	character->_cover_left = false;
}


void ADNCommonWall::overlap_right_collision_handler(class UPrimitiveComponent* selfComp, class AActor* otherActor, UPrimitiveComponent* otherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADNCommonCharacter* character = Cast<ADNCommonCharacter>(otherActor);

	if (nullptr == character)
		return;

	character->_cover_right = true;
}


void ADNCommonWall::unoverlap_right_collision_handler(UPrimitiveComponent* OverlappedComp, AActor* otherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ADNCommonCharacter* character = Cast<ADNCommonCharacter>(otherActor);

	if (nullptr == character)
		return;

	character->_cover_right = false;
}