

#pragma once

// Engine
#include <CoreMinimal.h>
#include <CameraAnimationSequence.h>
#include <CameraAnimationCameraModifier.h>

// Data
#include "UE5_Training_Project/Data/DNCharacterSkillData.h"
#include "UE5_Training_Project/Data/DNCharacterData.h"

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"

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
	static void active_skill_burst(ADNCommonCharacter* player_in,ADNCommonCharacter* owner_in,UAnimMontage* animation_in, UCameraAnimationSequence* camera_animation_in)
	{
		play_skill_animation(player_in,owner_in, animation_in);
		play_camera_sequence(player_in,owner_in, camera_animation_in);

		//몽타주 재생이 끝나면 

	}

	static void play_skill_animation(ADNCommonCharacter* player_in,ADNCommonCharacter* owner_in, UAnimMontage* animation_in)
	{
		auto* anim = owner_in->_character_skeletal_mesh->GetAnimInstance();
		
		if (nullptr != anim)
		{
			anim->Montage_Play(animation_in);
			ADNPlayerController* controller = Cast<ADNPlayerController>(player_in->GetController());

			if (nullptr != controller)
			{
				// 해당 스킬 몽타주 종료시에만 카메라 리셋을 해야하기 때문에 이렇게 넣어줍니다.
				controller->_now_skill_animation = animation_in;

				if (false == anim->OnMontageEnded.IsBound())
					anim->OnMontageEnded.AddDynamic(controller, &ADNPlayerController::reset_camera_handler);

			}
		}

	}
	static void play_camera_sequence(ADNCommonCharacter* player_in,ADNCommonCharacter* owner_in, UCameraAnimationSequence* camera_animation_in)
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
