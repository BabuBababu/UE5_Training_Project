

#pragma once

// Engine
#include <CoreMinimal.h>
#include <Animation/AnimInstance.h>

// Animation
#include "UE5_Training_Project/Character/Animation/DNCharacterAnimInstance.h"

// Generated
#include "DNLobbyCharacterAnimInstance.generated.h"

/**
 * 
 */



class UAnimMontage;
class ADNPlayerCharacter;

UCLASS()
class UE5_TRAINING_PROJECT_API UDNLobbyCharacterAnimInstance : public UDNCharacterAnimInstance
{
	GENERATED_BODY()

public:
	UDNLobbyCharacterAnimInstance();

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void add_event() override;
	void remove_event() override;

public:
	void on_walking_montage_ended();

public:
	UFUNCTION(BlueprintCallable)
	void play_walking_montage();

public:

	FOnMontageEndDelegate OnWalkingEnd;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)					// 로비에서는 모든 인형들도 사용할 듯 일단은 이정도로만
		TObjectPtr<UAnimMontage> sitting_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TObjectPtr<UAnimMontage> sit_to_standing_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TObjectPtr<UAnimMontage> standing_to_sit_montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)					// 로비에서 지휘관 선택시 앞으로 이동하는 애니메이션
		TObjectPtr<UAnimMontage> lobby_walking_montage;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
		bool _select_character_lobby;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
		bool _lobby_finished;


	ADNPlayerCharacter* _owner = nullptr;


private:
	bool	_playing_walking_montage;
};
