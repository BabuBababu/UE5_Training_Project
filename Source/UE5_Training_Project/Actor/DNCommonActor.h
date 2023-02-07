

#pragma once

// Engine
#include <CoreMinimal.h>
#include <GameFramework/Actor.h>

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"


// Generated
#include "DNCommonActor.generated.h"





class UBoxComponent;

UCLASS()
class UE5_TRAINING_PROJECT_API ADNCommonActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADNCommonActor();



protected:
	virtual void BeginPlay() override;

	virtual void add_event();
	virtual void remove_event();

public:	
	virtual void Tick(float DeltaTime) override;


private:
	void init();

public:
	// 메쉬
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<USkeletalMeshComponent> _actor_skeletal_mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> _actor_static_mesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* _box_collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	E_ACTOR_TYPE _actor_type = E_ACTOR_TYPE::AT_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	int64		 _actor_id;										//액터 구분용



};
