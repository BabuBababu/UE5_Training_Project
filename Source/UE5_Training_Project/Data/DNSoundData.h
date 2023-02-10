#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

// Engine
#include <CoreMinimal.h>
#include <Engine/DataTable.h>
#include <Sound/SoundMix.h>
#include <Sound/SoundWave.h>
#include <MetasoundSource.h>

// Defs
#include "UE5_Training_Project/Defs/DNDefs.h"

// generated
#include "DNSoundData.generated.h"





USTRUCT(Atomic, BlueprintType)
struct FDNMetaSoundSourceData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		int64				id = 0;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")	//트리거할 입력 값
		FName				input_name = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")	//메타 사용 여부
		bool				use_meta;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		UMetaSoundSource* meta_sound_source_asset = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")	//메타에 사용할 사운드 믹스 ID
		int32				sound_mix_id = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")	//사운드믹스 지속 시간
		float				sound_mix_duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")	//설명
		FString				description = TEXT("");



};


USTRUCT(Atomic, BlueprintType)
struct FDNMetaSoundMIxData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaSound")
		int64				id = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaSound")
		USoundMix* meta_sound_mix_asset = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaSound")
		FString				description = TEXT("");
};