


#include "UE5_Training_Project/Character/Component/DNPlayerLineTrace.h"


// Engine

#include <Engine/Engine.h>
#include <particles/ParticleSystem.h>
#include <DrawDebugHelpers.h>
#include <GameFramework/SpringArmComponent.h>
#include <Engine/Classes/Kismet/GameplayStatics.h>
#include <Engine/Classes/Kismet/KismetMathLibrary.h>
#include <BehaviorTree/BlackboardComponent.h>

// Component
#include "UE5_Training_Project/Component/DNStatusComponent.h"

// Controller
#include "UE5_Training_Project/Controller/DNAIController.h"

// BlackBoard
#include "UE5_Training_Project/AI/DNAllAIBlackBoardKeys.h"

// Character
#include "UE5_Training_Project/Character/DNCommonCharacter.h"
#include "UE5_Training_Project/Character/DNPlayerCharacter.h"
#include "UE5_Training_Project/Character/DNEnemyCharacter.h"
#include "UE5_Training_Project/Character/DNDogEnemyCharacter.h"
#include "UE5_Training_Project/Character/DNCommonBossCharacter.h"

// Actor
#include "UE5_Training_Project/Actor/DNCommonShield.h"
#include "UE5_Training_Project/Actor/DNBossMissile.h"

// Item
#include "UE5_Training_Project/Actor/DNCommonActor.h"
#include "UE5_Training_Project/Actor/Item/DNCommonItem.h"

// Manager
#include "UE5_Training_Project/Manager/DNUIManager.h"
#include "UE5_Training_Project/UI/Manager/DNWidgetManager.h"

// UI
#include "UE5_Training_Project/UI/Widget/Panel/DNInteractionPanel.h"
#include "UE5_Training_Project/UI/Widget/Panel/DNTargetCirclePanel.h"

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

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Order_move_ParticleAdd(TEXT("/Game/Assets/Particle/P_Targeting_Player_Movement"));
	order_move_particle = Order_move_ParticleAdd.Object;



	_item = nullptr;
	_temp_character = nullptr;
}



void UDNPlayerLineTrace::OnFire(ADNCommonCharacter* player_in)
{
	FQuat rotate = FQuat(player_in->GetControlRotation());		// 임시로 -15.f 로 카메라 각도만큼 해놧는데 확인예정

	// 유저인지 확인
	ADNPlayerCharacter* user = Cast<ADNPlayerCharacter>(player_in);

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
	player_in->GetWorld()->LineTraceSingleByChannel(hit_result, start_location, end_location, ECollisionChannel::ECC_Visibility, params);
	//DrawDebugLine(player_in->GetWorld(), start_location, end_location, FColor::Red, false, 5.f, 0, 5.f);


	// 런처 병과
	if (player_in->get_status_component()->_character_mos == E_CHARACTER_MOS::CM_LC)
	{

		ADNAIController* controller = Cast<ADNAIController>(player_in->GetController());
		if (nullptr == controller)
			return;

		auto* object = controller->get_blackboard()->GetValueAsObject(all_ai_bb_keys::target_actor);
		AActor* target = Cast<AActor>(object);
		player_in->fire_missile(end_location, target);

		return;
	}
		
		if (hit_result.GetActor() != nullptr)
		{	
			FVector hit_location = hit_result.ImpactNormal * 20.f + hit_result.ImpactPoint;
			auto _enemy = Cast<ADNEnemyCharacter>(hit_result.GetActor());

			// 플레이어라면 히트 사운드 재생
			ADNPlayerCharacter* player = Cast<ADNPlayerCharacter>(player_in);
			if (nullptr != player)
			{
				player->play_hit_sound();
			}

				 // 런처 병과
			if (player_in->get_status_component()->_character_mos == E_CHARACTER_MOS::CM_LC)
			{
				
			}
			else // 나머지 병과
			{
				// 스킬로 쐈는지 확인할 경우 해당 bool값을 체크하는걸로 추가한다.
				if (_enemy)
				{
					// 기본 누적 버스트 게이지 1.f
					OBJECT_MANAGER->_player->set_burst_gauge(1.f);

					// 무기 데이터 테이블을 이용해서 대미지 적용하는 방식을 쓸 예정이므로 아래 코드는 결국 수정할 것.
					//DrawDebugBox(player_in->GetWorld(), hit_result.ImpactPoint, FVector(5, 5, 5), FColor::Blue, false, 2.f);
					if (_enemy->_enemy_type == E_ENEMY_TYPE::ET_BOSS || _enemy->_enemy_type == E_ENEMY_TYPE::ET_BOSS_RESVOLITAN)
					{
						OBJECT_MANAGER->_player->set_burst_gauge(0.5f);
						UGameplayStatics::SpawnEmitterAtLocation(player_in->GetWorld(), block_particle, hit_location, FRotator(0.f, 0.f, 0.f), FVector(2), true, EPSCPoolMethod::None, true);			//보스
						DNDamageOperation::gun_damage_to_gun_spider_boss(damage, hit_result.BoneName, _enemy, player_in);
						OnTargetHit.Broadcast();

						// 플레이어일 경우
						if (nullptr != user)
						{
							// 타겟 서클 패널 끄기
							close_target_panel();
						}
					}
					else if (_enemy->_enemy_type == E_ENEMY_TYPE::ET_MELEE)
					{
						OBJECT_MANAGER->_player->set_burst_gauge(2.f);
						UGameplayStatics::SpawnEmitterAtLocation(player_in->GetWorld(), block_particle, hit_location, FRotator(0.f, 0.f, 0.f), FVector(1), true, EPSCPoolMethod::None, true);			//댕댕이
						DNDamageOperation::gun_damage(damage, hit_result.BoneName, _enemy, player_in);
						OnTargetHit.Broadcast();

						// 플레이어일 경우
						if (nullptr != user)
						{
							// 타겟 서클 패널 끄기
							close_target_panel();
						}
					}
					else if (_enemy->_enemy_type == E_ENEMY_TYPE::ET_RANGER_LC || _enemy->_enemy_type == E_ENEMY_TYPE::ET_RANGER_AR)
					{
						UGameplayStatics::SpawnEmitterAtLocation(player_in->GetWorld(), block_particle, hit_location, FRotator(0.f, 0.f, 0.f), FVector(1), true, EPSCPoolMethod::None, true);			//랩쳐AR,LC
						DNDamageOperation::gun_damage(damage, hit_result.BoneName, _enemy, player_in);
						OnTargetHit.Broadcast();

						// 플레이어일 경우
						if (nullptr != user)
						{
							// 타겟 서클 패널 끄기
							close_target_panel();
						}
					}
					else if (_enemy->_enemy_type == E_ENEMY_TYPE::ET_MELEE_SHIELD)
					{
						UGameplayStatics::SpawnEmitterAtLocation(player_in->GetWorld(), blood_particle, hit_location, FRotator(0.f, 0.f, 0.f), FVector(1), true, EPSCPoolMethod::None, true);			//쉴더
						DNDamageOperation::gun_damage(damage, hit_result.BoneName, _enemy, player_in);
						OnTargetHit.Broadcast();

						// 플레이어일 경우
						if (nullptr != user)
						{
							// 타겟 서클 패널 끄기
							close_target_panel();
						}
					}
					else if (_enemy->_enemy_type ==  E_ENEMY_TYPE::ET_TARGET_CIRCLE)
					{
						ADNPatternTargetActor* _target_circle_actor = Cast<ADNPatternTargetActor>(_enemy);

						if (nullptr == _target_circle_actor)
							return;

						// 대미지 적용
						DNDamageOperation::gun_damage_to_target_circle(damage, _target_circle_actor, player_in);
						UGameplayStatics::SpawnEmitterAtLocation(player_in->GetWorld(), block_particle, hit_location, FRotator(0.f, 0.f, 0.f), FVector(1), true, EPSCPoolMethod::None, true);
						OnTargetHit.Broadcast();


						// 플레이어일 경우
						if (nullptr != user)
						{
							//타겟서클 패널 켜주기
							UDNBasePanel* base_panel = WIDGET_MANAGER->get_panel(E_UI_PANEL_TYPE::UPT_TARGET_CIRCLE);
							if (nullptr == base_panel)
								return;

							UDNTargetCirclePanel* panel = Cast<UDNTargetCirclePanel>(base_panel);
							if (nullptr == panel)
								return;

							panel->set_widget(_target_circle_actor);
							panel->play_hit_animation();
						}
						
					}
					else
					{
						UGameplayStatics::SpawnEmitterAtLocation(player_in->GetWorld(), block_particle, hit_location, FRotator(0.f, 0.f, 0.f), FVector(1), true, EPSCPoolMethod::None, true);			//나머지 적
						DNDamageOperation::gun_damage(damage, hit_result.BoneName, _enemy, player_in);
						OnTargetHit.Broadcast();

						// 플레이어일 경우
						if (nullptr != user)
						{
							// 타겟 서클 패널 끄기
							close_target_panel();
						}
					}
				}
				else
				{
					// 플레이어일 경우
					if (nullptr != user)
					{
						// 타겟 서클 패널 끄기
						close_target_panel();
					}

					// _enemy가 nullptr이라면 쉴드를 가격했는지 확인
					auto _shield = Cast<ADNCommonShield>(hit_result.GetActor());
					if (nullptr != _shield)
					{
						// 대미지 적용
						DNDamageOperation::gun_damage_to_shield(damage, _shield, player_in);
						_shield->play_damaged_sound();
						UGameplayStatics::SpawnEmitterAtLocation(player_in->GetWorld(), block_particle, hit_location, FRotator(0.f, 0.f, 0.f), FVector(1), true, EPSCPoolMethod::None, true);

					}
					else
					{
						//_shield가 nullptr이라면 미사일을 가격했는지 확인
						auto _missile = Cast<ADNBossMissile>(hit_result.GetActor());
						if (nullptr != _missile)
						{
							// 대미지 적용
							DNDamageOperation::gun_damage_to_missile(damage, _missile, player_in);
							_missile->play_damaged_sound();
							UGameplayStatics::SpawnEmitterAtLocation(player_in->GetWorld(), block_particle, hit_location, FRotator(0.f, 0.f, 0.f), FVector(1), true, EPSCPoolMethod::None, true);
						}
						else
						{
							// 어떤 액터도 아니라면
							UGameplayStatics::SpawnEmitterAtLocation(player_in->GetWorld(), block_particle, hit_location, FRotator(0.f, 0.f, 0.f), FVector(1), true, EPSCPoolMethod::None, true);
						}

					}

					//UE_LOG(LogTemp, Warning, TEXT("FailedCast"));
					//GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("LOCATION: %s"),*HitLoc.ToString()));
					//DrawDebugBox(player_in->GetWorld(), hit_result.ImpactPoint, FVector(5, 5, 5), FColor::Purple, false, 2.f);


				}

				// 총알 궤적 스폰
				int result = FMath::FRandRange(1.0, 5.0);

				if (result == 1.0)		//일단 확률 20%로 설정
				{
					player_in->spawn_bullet_light(hit_location);
				}
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
	player_in->GetWorld()->LineTraceSingleByChannel(hit_result, start_location, end_location, ECollisionChannel::ECC_Visibility, params);
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
			ADNCommonItem* item = Cast<ADNCommonItem>(actor);
			if (nullptr == item)
				return;

			_item = item;
			_item->_is_selected = true;

			//DrawDebugBox(player_in->GetWorld(), hit_result.ImpactPoint, FVector(5, 5, 5), FColor::Blue, false, 2.f);
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
	player_in->GetWorld()->LineTraceSingleByChannel(hit_result, start_location, end_location, ECollisionChannel::ECC_Visibility, params);
	//DrawDebugLine(player_in->GetWorld(), start_location, end_location, FColor::Red, false, 5.f, 0, 5.f);

	if (nullptr == hit_result.GetActor())
	{
		if (nullptr != _temp_character)
		{
			if (nullptr == _temp_character->_character_skeletal_mesh)				//바로 아래 주석을 이유로 메쉬 널체크
				return;

			//_temp_character->_character_skeletal_mesh->SetRenderCustomDepth(false);	//여기에 왜 파티클시스템컴포넌트가 잡히는거지 이해가 안되넼ㅋㅋㅋㅋㅋㅋ
			//_temp_character = nullptr;	// 텅텅빈곳이므로 null값을 넣는다
		}
	}
	else
	{
		ADNEnemyCharacter* _enemy = Cast<ADNEnemyCharacter>(hit_result.GetActor());

		if (nullptr == _enemy)
			return;

		// 아웃라인 보여주기
		if (nullptr == _enemy->_character_skeletal_mesh)				//바로 아래 주석을 이유로 메쉬 널체크
			return;

		//_enemy->_character_skeletal_mesh->SetRenderCustomDepth(true);					SRS 머티리얼 적용으로 해당 코드는 주석 처리함 23.6.1
		//DrawDebugBox(player_in->GetWorld(), hit_result.ImpactPoint, FVector(5, 5, 5), FColor::Blue, false, 2.f);


		// 만약에 타겟 서클이라면 바로 리턴합니다.
		ADNPatternTargetActor* target_circle = Cast<ADNPatternTargetActor>(_enemy);
		if (nullptr != target_circle)
			return;

		//타겟 액터 패널을 끕니다.
		close_target_panel();

		if (_temp_character != _enemy)	// 적중한 캐릭터가 이전 캐릭터와 다르다면
		{
			if (nullptr == _temp_character)
			{
				//DrawDebugBox(player_in->GetWorld(), hit_result.ImpactPoint, FVector(5, 5, 5), FColor::Red, false, 2.f);

				_temp_character = _enemy;	// 현재 적중된 캐릭터를 넣어준다.
			}
			else
			{
				if (nullptr == _temp_character->_character_skeletal_mesh)				//바로 아래 주석을 이유로 메쉬 널체크
					return;
				//DrawDebugBox(player_in->GetWorld(), hit_result.ImpactPoint, FVector(5, 5, 5), FColor::Yellow, false, 2.f);

				//_temp_character->_character_skeletal_mesh->SetRenderCustomDepth(false);  SRS 머티리얼 적용으로 해당 코드는 주석 처리함  23.6.1
				_temp_character = _enemy;	// 현재 적중된 캐릭터를 다시 바꿔준다.
			}
		}

		

		

		OnTargetAiming.Broadcast(_enemy);
	}
}





void UDNPlayerLineTrace::OnOrder(ADNCommonCharacter* player_in, ADNUnEnemyCharacter* doll_in)
{
	if (player_in->_character_type != E_CHARACTER_TYPE::CT_PLAYER)	//플레이어가 아니라면 리턴
		return;

	if (nullptr == doll_in)											//스쿼드에 없는 니케라면 리턴
		return;


	FQuat rotate = FQuat(player_in->GetControlRotation());		// 임시로 -15.f 로 카메라 각도만큼 해놧는데 확인예정

	auto status = player_in->get_status_component().Get();

	FVector camera_location = player_in->_camera_boom->GetComponentLocation();
	FVector start_location = camera_location;

	// 카메라 회전값 * 카메라의 포워드 벡터 = 사격 방향
	FVector temp_forward = rotate.GetForwardVector();
	// 명령 끝 지점
	FVector end_location = camera_location + (temp_forward * 20000.f); // 사거리 2KM
	FHitResult hit_result;

	// 무시할 오브젝트
	FCollisionQueryParams params;
	params.AddIgnoredActor(player_in);		//플레이어와 자기 자신 인형은 무시합니다.
	params.AddIgnoredActor(doll_in);

	// 채널 결합, 열거형을 활용해서
	ECollisionChannel TraceChannel = static_cast<ECollisionChannel>(ECC_PhysicsBody | ECC_WorldStatic);

	//라인 트레이스 시작 (지형, 액터 전부 체크)
	player_in->GetWorld()->LineTraceSingleByChannel(hit_result, start_location, end_location, TraceChannel, params);
	
	if (hit_result.GetActor() != nullptr)
	{
		// 캐릭터 액터인지 체크
		ADNCommonCharacter* actor = Cast<ADNCommonCharacter>(hit_result.GetActor());
		// 플레이어 유효한지 체크
		ADNPlayerCharacter* player = Cast<ADNPlayerCharacter>(player_in);
		// 타겟 서클 액터인지 체크
		ADNPatternTargetActor* target_circle = Cast<ADNPatternTargetActor>(hit_result.GetActor());

		GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString::Printf(TEXT("hit Actor name is : %s"), *hit_result.GetActor()->GetName()));

		if (nullptr == player)
			return;

		
		if (nullptr == actor)			//캐릭터 액터가 아니라면 타겟서클? 그것도 아니라면 지형
		{
			if (nullptr != target_circle)
			{
				player->order_attack(target_circle, doll_in);
			}
			else
			{
				UGameplayStatics::SpawnEmitterAtLocation(player_in->GetWorld(), order_move_particle, hit_result.ImpactPoint, FRotator(0.f, 0.f, 0.f), FVector(1), true, EPSCPoolMethod::None, true);
				player->order_move(hit_result.ImpactPoint, doll_in);
			}
			
		}
		else if (actor->_character_type == E_CHARACTER_TYPE::CT_ENEMY)   // 적군
		{
			ADNEnemyCharacter* enemy = Cast<ADNEnemyCharacter>(actor);

			if (nullptr != enemy)
				player->order_attack(enemy, doll_in);
		}

		// 명령 실행 보이스
		if(IsValid(doll_in->_order_on_soundcue))
			UGameplayStatics::PlaySoundAtLocation(this, doll_in->_order_on_soundcue, doll_in->GetActorLocation());
		

	}


}

void UDNPlayerLineTrace::close_target_panel()
{
	UDNBasePanel* base_panel = WIDGET_MANAGER->get_panel(E_UI_PANEL_TYPE::UPT_TARGET_CIRCLE);
	if (nullptr == base_panel)
		return;

	UDNTargetCirclePanel* panel = Cast<UDNTargetCirclePanel>(base_panel);
	if (nullptr == panel)
		return;

	panel->close_widget();
}