﻿


#include "UE5_Training_Project/Character/Component/DNPlayerLineTrace.h"


// Engine

#include "Engine/Engine.h"
#include "particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Classes/Kismet/KismetMathLibrary.h"

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"
#include "UE5_Training_Project/Character/DNEnemyCharacter.h"


UDNPlayerLineTrace::UDNPlayerLineTrace()
{
	//파티클 시스템 
	static ConstructorHelpers::FObjectFinder<UParticleSystem>Blood_ParticleAdd(TEXT("/Game/Assets/Weapon/Griffin/WeaponEffects/P_body_bullet_impact.P_body_bullet_impact"));
	blood_particle = Blood_ParticleAdd.Object;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Block_ParticleAdd(TEXT("/Game/Assets/Weapon/Griffin/WeaponEffects/P_AssaultRifle_IH"));
	block_particle = Block_ParticleAdd.Object;
}

void UDNPlayerLineTrace::OnFire(ADNCommonCharacter* player_in)
{
	FQuat rotate = FQuat(player_in->GetControlRotation());		// 임시로 -15.f 로 카메라 각도만큼 해놧는데 확인예정

	//사격 시작 지점
	//FVector muzzle_location = player_in->weapon_hands->GetSocketLocation("Muzzle");
	//FVector start_location = muzzle_location;
	FVector camera_location = player_in->_camera_boom->GetComponentLocation();
	FVector start_location = camera_location;

	// 카메라 회전값 * 카메라의 포워드 벡터 = 사격 방향
	FVector temp_forward = rotate.GetForwardVector();
	// 사격 끝 지점
	FVector end_location = camera_location + (temp_forward * 20000.f); // 사거리 2KM
	FHitResult hit_result;

	// 무시할 오브젝트
	FCollisionQueryParams params;
	params.AddIgnoredActor(player_in);

	//라인 트레이스 시작
	player_in->GetWorld()->LineTraceSingleByChannel(hit_result, start_location, end_location, ECollisionChannel::ECC_PhysicsBody, params);
	DrawDebugLine(player_in->GetWorld(), start_location, end_location, FColor::Red, false, 5.f, 0, 5.f);

	if (hit_result.GetActor() != nullptr)
	{
		FVector hit_location = hit_result.ImpactNormal * 20.f + hit_result.ImpactPoint;
		auto _enemy = Cast<ADNEnemyCharacter>(hit_result.GetActor());
		// 스킬로 쐈는지 확인할 경우 해당 bool값을 체크하는걸로 추가한다.
		if (_enemy)
		{
			// 무기 데이터 테이블을 이용해서 대미지 적용하는 방식을 쓸 예정이므로 아래 코드는 결국 수정할 것.
			//UE_LOG(LogTemp, Warning, TEXT("SucceedCastDouble"));
			DrawDebugBox(player_in->GetWorld(), hit_result.ImpactPoint, FVector(5, 5, 5), FColor::Blue, false, 2.f);
			UGameplayStatics::SpawnEmitterAtLocation(player_in->GetWorld(), blood_particle, hit_location, FRotator(0.f, 0.f, 0.f), FVector(2), true, EPSCPoolMethod::None, true);

		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("FailedCast"));
			//GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("LOCATION: %s"),*HitLoc.ToString()));
			DrawDebugBox(player_in->GetWorld(), hit_result.ImpactPoint, FVector(5, 5, 5), FColor::Purple, false, 2.f);
			UGameplayStatics::SpawnEmitterAtLocation(player_in->GetWorld(), block_particle, hit_location, FRotator(0.f, 0.f, 0.f), FVector(2), true, EPSCPoolMethod::None, true);
		}
	}

}