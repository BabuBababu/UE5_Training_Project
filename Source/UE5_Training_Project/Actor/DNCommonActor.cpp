


#include "UE5_Training_Project/Actor/DNCommonActor.h"

// Engine
#include <Components/BoxComponent.h>



ADNCommonActor::ADNCommonActor()
{
	PrimaryActorTick.bCanEverTick = true;
	init();
}

void ADNCommonActor::BeginPlay()
{
	Super::BeginPlay();
}

void ADNCommonActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADNCommonActor::add_event()
{

}

void ADNCommonActor::remove_event()
{

}


void ADNCommonActor::init()
{

	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));

	_actor_skeletal_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	_actor_static_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	_box_collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));

	_actor_skeletal_mesh->SetupAttachment(RootComponent);
	_actor_static_mesh->SetupAttachment(RootComponent);
	_box_collision->SetupAttachment(RootComponent);

	_actor_id = -1;
	_actor_static_mesh->SetRenderCustomDepth(true);
}


