// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine
#include <CoreMinimal.h>
#include <UObject/NoExportTypes.h>

// generated
#include "DNObjectManager.generated.h"

/**
 *	 아직은 확실히 정해두진 않았지만 
 *	 그리폰 인형 클래스와 스테이지에 생성하게 될 많은 적군 객체들을 관리하기 위해 만들었습니다.
 *	 총알 생성 및 파괴할 때 상당한 연산을 필요로 한다고 생각했어요. 
 *   파괴하지않고 사라지게 한다음 모아놨다가 재활용하면 어떨까 라는 생각을 했습니당!
 *	 그래서 오브젝트풀로서 관리를 할 수도 있겠다 싶어서 만든 매니저 클래스입니다!
 */

UCLASS()
class UE5_TRAINING_PROJECT_API UDNObjectManager : public UObject
{
	GENERATED_BODY()
	
};
