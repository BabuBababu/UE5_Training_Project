

#pragma once

// Engine
#include <CoreMinimal.h>
#include <CameraAnimationSequence.h>
#include <CameraAnimationCameraModifier.h>
#include <GameFramework/CharacterMovementComponent.h>

// Data
#include "UE5_Training_Project/Data/DNCharacterSkillData.h"
#include "UE5_Training_Project/Data/DNCharacterData.h"

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"
#include "UE5_Training_Project/Character/DNPlayerCharacter.h"

// Controller
#include "UE5_Training_Project/Controller/DNPlayerController.h"

// Component
#include "UE5_Training_Project/Component/DNStatusComponent.h"

/**
 * 
 */
class UE5_TRAINING_PROJECT_API DNSkillSystem
{
public:
	static void active_skill_1()
	{
		
	}
	static void active_skill_2()
	{

	}
	static void active_skill_burst(ADNPlayerCharacter* player_in,ADNCommonCharacter* owner_in,UAnimMontage* animation_in, FString camera_path)
	{
		player_in->set_burst_gauge(-300.f); // 일단 버스트는 300으로 고정
		UCameraAnimationSequence* CameraSequenceBPClass = LoadObject<UCameraAnimationSequence>(NULL, *camera_path);

		if (CameraSequenceBPClass)
		{
			play_skill_animation(player_in, owner_in, animation_in);
			play_camera_sequence(player_in, owner_in, CameraSequenceBPClass);
		}

		owner_in->GetMovementComponent()->SetActive(false);
	}

	static void play_skill_animation(ADNPlayerCharacter* player_in,ADNCommonCharacter* owner_in, UAnimMontage* animation_in)
	{
		auto* anim = owner_in->_character_skeletal_mesh->GetAnimInstance();
		
		if (nullptr != anim)
		{
			anim->Montage_Play(animation_in);
			ADNPlayerController* controller = Cast<ADNPlayerController>(player_in->GetController());
			owner_in->_on_burst_skill = true;
			if (nullptr != controller)
			{
				// 해당 스킬 몽타주 종료시에만 카메라 리셋을 해야하기 때문에 이렇게 넣어줍니다.
				controller->_now_skill_animation = animation_in;

				if (false == anim->OnMontageEnded.IsBound())
				{
					anim->OnMontageEnded.AddDynamic(controller, &ADNPlayerController::reset_camera_handler);
					anim->OnMontageEnded.AddDynamic(owner_in, &ADNCommonCharacter::set_movement_for_bust_handler);
				}
					
			}
		}

	}
	static void play_camera_sequence(ADNPlayerCharacter* player_in,ADNCommonCharacter* owner_in, UCameraAnimationSequence* camera_animation_in)
	{
		
		ADNPlayerController* controller = Cast<ADNPlayerController>(player_in->GetController());
		if (nullptr != controller)
		{
			// 카메라 렌더 타겟 변경
			controller->SetViewTargetWithBlend(owner_in);

			// 카메라 애니메이션 실행
			auto* camera_manager = Cast<UCameraAnimationCameraModifier>(controller->PlayerCameraManager->FindCameraModifierByClass(UCameraAnimationCameraModifier::StaticClass()));

			if (nullptr != camera_manager)
			{
				FCameraAnimationParams params;
				camera_manager->PlayCameraAnimation(camera_animation_in, params);
			}
				
			
		}

	}
	
};
