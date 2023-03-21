#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

// Engine
#include <CoreMinimal.h>
#include <Engine/DataTable.h>

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// generated
#include "DNUIData.generated.h"





USTRUCT(Atomic, BlueprintType)
struct FDNUICommonButtonTextColor : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
		FLinearColor		normal_text_color = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
		FLinearColor		hovered_text_color = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
		FLinearColor		pressed_text_color = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
		FLinearColor		disabled_text_color = FLinearColor(0.2f, 0.2f, 0.2f, 1.0f);

};

