﻿


#include "UE5_Training_Project/Character/Component/DNPlayerLineTrace.h"


// Engine

#include "Engine/Engine.h"
#include "particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Classes/Kismet/KismetMathLibrary.h"

// Component
#include <UE5_Training_Project/Component/DNStatusComponent.h>

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"
#include "UE5_Training_Project/Character/DNEnemyCharacter.h"

// Item
#include "UE5_Training_Project/Actor/DNCommonActor.h"
#include "UE5_Training_Project/Actor/Item/DNCommonItem.h"

// Manager
#include "UE5_Training_Project/Manager/DNUIManager.h"
#include "UE5_Training_Project/UI/Manager/DNWidgetManager.h"

// UI
#include "UE5_Training_Project/UI/Widget/Panel/DNInteractionPanel.h"

// Util
#include "UE5_Training_Project/Util/DNDamageOperation.h"


UDNPlayerLineTrace::UDNPlayerLineTrace()
{
	//파티클 시스템 
	static ConstructorHelpers::FObjectFinder<UParticleSystem>Blood_ParticleAdd(TEXT("/Game/Assets/Weapon/Griffin/WeaponEffects/P_body_bullet_impact.P_body_bullet_impact"));
	blood_particle = Blood_ParticleAdd.Object;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Block_ParticleAdd(TEXT("/Game/Assets/Weapon/Griffin/WeaponEffects/P_AssaultRifle_IH"));
	block_particle = Block_ParticleAdd.Object;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Fire_ParticleAdd(TEXT("/Game/Assets/Weapon/Griffin/WeaponEffects/P_AssaultRifle_MF"));
	fire_particle = Fire_ParticleAdd.Object;


	_item = nullptr;
	_temp_character = nullptr;
}



void UDNPlayerLineTrace::OnFire(ADNCommonCharacter* player_in)
{
	FQuat rotate = FQuat(player_in->GetControlRotation());		// 임시로 -15.f 로 카메라 각도만큼 해놧는데 확인예정

	auto status = player_in->get_status_component().Get();

	// 대미지량
	float damage = status->_chartacter_data->character_status_data.damage;


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


	//총구 화염 연출
	UGameplayStatics::SpawnEmitterAttached(fire_particle, player_in->_weapon_armed, FName("Muzzle"), FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f), FVector(1), EAttachLocation::SnapToTarget, true, EPSCPoolMethod::None, true);


	//라인 트레이스 시작
	player_in->GetWorld()->LineTraceSingleByChannel(hit_result, start_location, end_location, ECollisionChannel::ECC_PhysicsBody, params);
	//DrawDebugLine(player_in->GetWorld(), start_location, end_location, FColor::Red, false, 5.f, 0, 5.f);

	if (hit_result.GetActor() != nullptr)
	{
		FVector hit_location = hit_result.ImpactNormal * 20.f + hit_result.ImpactPoint;
		auto _enemy = Cast<ADNEnemyCharacter>(hit_result.GetActor());
		// 스킬로 쐈는지 확인할 경우 해당 bool값을 체크하는걸로 추가한다.
		if (_enemy)
		{
			// 무기 데이터 테이블을 이용해서 대미지 적용하는 방식을 쓸 예정이므로 아래 코드는 결국 수정할 것.
			DrawDebugBox(player_in->GetWorld(), hit_result.ImpactPoint, FVector(5, 5, 5), FColor::Blue, false, 2.f);
			UGameplayStatics::SpawnEmitterAtLocation(player_in->GetWorld(), blood_particle, hit_location, FRotator(0.f, 0.f, 0.f), FVector(2), true, EPSCPoolMethod::None, true);
			
			

			// 대미지 적용
			DNDamageOperation::ReceiveDamage(damage, hit_result.BoneName, _enemy, player_in);
			DNDamageOperation::DamageShowUI(damage, _enemy,E_DAMAGE_TYPE::DT_NORMAL);//헤드일 경우 약점 대미지로 판단, ReceiveDamage에서 약점부위를 판단하고 넣어야할듯.. 순서가.. 일단은 노멀로 통일
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


void UDNPlayerLineTrace::OnInteraction(ADNCommonCharacter* player_in)
{
	FQuat rotate = FQuat(player_in->GetControlRotation());		// 임시로 -15.f 로 카메라 각도만큼 해놧는데 확인예정

	auto status = player_in->get_status_component().Get();

	FVector camera_location = player_in->_camera_boom->GetComponentLocation();
	FVector start_location = camera_location;

	// 카메라 회전값 * 카메라의 포워드 벡터 = 사격 방향
	FVector temp_forward = rotate.GetForwardVector();
	// 사격 끝 지점
	FVector end_location = camera_location + (temp_forward * 600.f); // 사거리 3M
	FHitResult hit_result;

	// 무시할 오브젝트
	FCollisionQueryParams params;
	params.AddIgnoredActor(player_in);

	//라인 트레이스 시작
	player_in->GetWorld()->LineTraceSingleByChannel(hit_result, start_location, end_location, ECollisionChannel::ECC_PhysicsBody, params);
	//DrawDebugLine(player_in->GetWorld(), start_location, end_location, FColor::Red, false, 5.f, 0, 5.f);


	

	// 히트 액터가 없다면 위젯 숨기기
	OnInteractionLinetrace.Broadcast(E_UI_INTERACTION_TYPE::UIT_NONE);
	if (nullptr != _item)
	{
		_item->_is_selected = false;
		_item = nullptr;
		_is_targeted = false;
	}


	if (hit_result.GetActor() != nullptr)
	{
		auto actor = Cast<ADNCommonActor>(hit_result.GetActor());
		//GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString::Printf(TEXT("hit Actor name is : %s"), *hit_result.GetActor()->GetName()));

		if (nullptr == actor)
		{
			OnInteractionLinetrace.Broadcast(E_UI_INTERACTION_TYPE::UIT_NONE);
			if (nullptr != _item)
			{
				_item->_is_selected = false;
				_item = nullptr;
				_is_targeted = false;
			}
		}
		else if (actor->_actor_type == E_ACTOR_TYPE::AT_ITEM)
		{
			// 획득 위젯 보이기
			UDNBasePanel* base_panel = WIDGET_MANAGER->get_panel(E_UI_PANEL_TYPE::UPT_INTERACTION);
			if (nullptr == base_panel)
				return;

			UDNInteractionPanel* panel = dynamic_cast<UDNInteractionPanel*>(base_panel);		
			if (nullptr == panel)
				return;

			_is_targeted = true;

			OnInteractionLinetrace.Broadcast(E_UI_INTERACTION_TYPE::UIT_ITEM);
			auto* item = dynamic_cast<ADNCommonItem*>(actor);
			_item = item;
			_item->_is_selected = true;

			DrawDebugBox(player_in->GetWorld(), hit_result.ImpactPoint, FVector(5, 5, 5), FColor::Blue, false, 2.f);
		}
		else if (actor->_actor_type == E_ACTOR_TYPE::AT_VEHICLE)
		{
			// 탑승 위젯 보이기
			UDNBasePanel* base_panel = WIDGET_MANAGER->get_panel(E_UI_PANEL_TYPE::UPT_INTERACTION);
			if (nullptr == base_panel)
				return;

			UDNInteractionPanel* panel = dynamic_cast<UDNInteractionPanel*>(base_panel);
			if (nullptr == panel)
				return;

			_is_targeted = true;

			OnInteractionLinetrace.Broadcast(E_UI_INTERACTION_TYPE::UIT_VEHICLE);
		}
		else if (actor->_actor_type == E_ACTOR_TYPE::AT_NPC)
		{
			// NPC 위젯 보이기
			UDNBasePanel* base_panel = WIDGET_MANAGER->get_panel(E_UI_PANEL_TYPE::UPT_INTERACTION);
			if (nullptr == base_panel)
				return;

			UDNInteractionPanel* panel = dynamic_cast<UDNInteractionPanel*>(base_panel);
			if (nullptr == panel)
				return;

			_is_targeted = true;

			OnInteractionLinetrace.Broadcast(E_UI_INTERACTION_TYPE::UIT_NPC);
		}
	}
}




void UDNPlayerLineTrace::OnAiming(ADNCommonCharacter* player_in)
{
	if (player_in->_character_type != E_CHARACTER_TYPE::CT_PLAYER)	//플레이어가 아니라면 리턴
		return;


	FQuat rotate = FQuat(player_in->GetControlRotation());		// 임시로 -15.f 로 카메라 각도만큼 해놧는데 확인예정

	auto status = player_in->get_status_component().Get();

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
	//DrawDebugLine(player_in->GetWorld(), start_location, end_location, FColor::Red, false, 5.f, 0, 5.f);

	if (nullptr == hit_result.GetActor())
	{
		if (nullptr != _temp_character)
		{
			if (nullptr == _temp_character->_character_skeletal_mesh)				//바로 아래 주석을 이유로 메쉬 널체크
				return;

			_temp_character->_character_skeletal_mesh->SetRenderCustomDepth(false);	//여기에 왜 파티클시스템컴포넌트가 잡히는거지 이해가 안되넼ㅋㅋㅋㅋㅋㅋ
			_temp_character = nullptr;	// 텅텅빈곳이므로 null값을 넣는다
		}
	}
	else
	{
		auto _enemy = Cast<ADNEnemyCharacter>(hit_result.GetActor());
	
		if (nullptr == _enemy)
			return;

		// 아웃라인 보여주기
		_enemy->_character_skeletal_mesh->SetRenderCustomDepth(true);
		//DrawDebugBox(player_in->GetWorld(), hit_result.ImpactPoint, FVector(5, 5, 5), FColor::Blue, false, 2.f);


		if (_temp_character != _enemy)	// 적중한 캐릭터가 이전 캐릭터와 다르다면
		{
			if (nullptr == _temp_character)
			{
				//DrawDebugBox(player_in->GetWorld(), hit_result.ImpactPoint, FVector(5, 5, 5), FColor::Red, false, 2.f);

				_temp_character = _enemy;	// 현재 적중된 캐릭터를 넣어준다.
			}
			else
			{
				//DrawDebugBox(player_in->GetWorld(), hit_result.ImpactPoint, FVector(5, 5, 5), FColor::Yellow, false, 2.f);

				_temp_character->_character_skeletal_mesh->SetRenderCustomDepth(false);
				_temp_character = _enemy;	// 현재 적중된 캐릭터를 다시 바꿔준다.
			}
		}


	}
}