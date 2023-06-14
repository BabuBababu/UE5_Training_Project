

#pragma once

#include "CoreMinimal.h"


// Engine
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>

/**
 * 
 */
class UE5_TRAINING_PROJECT_API DNCameraMovingOperation
{
public:
	///////////////////////// 플레이어 카메라 제어 함수 ///////////////////////////
	static FTransform set_player_camera_transform(USpringArmComponent* camera_in, bool flag_in)
	{
		// 카메라와 뷰포트 거리 , 좌우, 높이
		const FVector OriginLocation(50.f, 90.f, 25.f);
		const FRotator OriginCameraRotation(0.f, 0.f, 0.f);
		const FVector OriginCameraScale(1.f, 1.f, 1.f);

		// 카메라가 바라보는 방향 기준
		FRotator rotate = camera_in->GetComponentRotation();
		FVector roatate_vector = FRotator(rotate.Pitch, 0.f, 0.f).Vector();

		FVector AimCameraLocation = OriginLocation + roatate_vector * 100.f + FVector(0.f, 0.f, 0.f);



		const FTransform AimCameraTransform(OriginCameraRotation, AimCameraLocation, OriginCameraScale);
		const FTransform OriginCameraTransform(OriginCameraRotation, OriginLocation, OriginCameraScale);

		if (true != flag_in)
			return OriginCameraTransform;

		return AimCameraTransform;
	}

	static FTransform set_player_camera_center_cover_transform(USpringArmComponent* camera_in, bool flag_in)
	{

		// 카메라와 뷰포트 거리 , 좌우, 높이
		const FVector OriginLocation(100.f, 90.f, 0.f);
		const FRotator OriginCameraRotation(0.f, 0.f, 0.f);
		const FVector OriginCameraScale(1.f, 1.f, 1.f);

		// 카메라가 바라보는 방향 기준
		FRotator rotate = camera_in->GetComponentRotation();
		FVector roatate_vector = FRotator(rotate.Pitch, 0.f, 0.f).Vector();
		//200 30 -15
		FVector AimCameraLocation = OriginLocation + roatate_vector * 100.f + FVector(0.f, -45.f, 0.f);



		const FTransform AimCameraTransform(OriginCameraRotation, AimCameraLocation, OriginCameraScale);
		const FTransform OriginCameraTransform(OriginCameraRotation, OriginLocation, OriginCameraScale);

		if (true != flag_in)
			return OriginCameraTransform;

		return AimCameraTransform;
	}


	static FTransform set_player_camera_left_cover_transform(USpringArmComponent* camera_in, bool flag_in)
	{

		// 카메라와 뷰포트 거리 , 좌우, 높이
		const FVector OriginLocation(100.f, 90.f, 0.f);
		const FRotator OriginCameraRotation(0.f, 0.f, 0.f);
		const FVector OriginCameraScale(1.f, 1.f, 1.f);

		// 카메라가 바라보는 방향 기준
		FRotator rotate = camera_in->GetComponentRotation();
		FVector roatate_vector = FRotator(rotate.Pitch, 0.f, 0.f).Vector();

		FVector AimCameraLocation = OriginLocation + roatate_vector * 100.f + FVector(0.f, -135.f, 0.f); //z값 -55.f였음



		const FTransform AimCameraTransform(OriginCameraRotation, AimCameraLocation, OriginCameraScale);
		const FTransform OriginCameraTransform(OriginCameraRotation, OriginLocation, OriginCameraScale);

		if (true != flag_in)
			return OriginCameraTransform;

		return AimCameraTransform;
	}



	static FTransform set_player_camera_right_cover_transform(USpringArmComponent* camera_in, bool flag_in)
	{

		// 카메라와 뷰포트 거리 , 좌우, 높이
		const FVector OriginLocation(100.f, 90.f, 0.f);
		const FRotator OriginCameraRotation(0.f, 0.f, 0.f);
		const FVector OriginCameraScale(1.f, 1.f, 1.f);

		// 카메라가 바라보는 방향 기준
		FRotator rotate = camera_in->GetComponentRotation();
		FVector roatate_vector = FRotator(rotate.Pitch, 0.f, 0.f).Vector();
		//200 30 -15
		FVector AimCameraLocation = OriginLocation + roatate_vector * 100.f + FVector(0.f, -45.f, 0.f);



		const FTransform AimCameraTransform(OriginCameraRotation, AimCameraLocation, OriginCameraScale);
		const FTransform OriginCameraTransform(OriginCameraRotation, OriginLocation, OriginCameraScale);

		if (true != flag_in)
			return OriginCameraTransform;

		return AimCameraTransform;
	}

};
