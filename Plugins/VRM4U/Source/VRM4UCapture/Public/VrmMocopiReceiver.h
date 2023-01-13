// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/CoreDelegates.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "Common/UdpSocketReceiver.h"
#include "Sockets.h"
#include "Common/UdpSocketBuilder.h"

#include "VrmMocopiReceiver.generated.h"

/**
 * 
 */

enum MocopiData{
	BoneNum = 27,
};


USTRUCT(BlueprintType)
struct FStructMocopiData{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int FrameNo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, EditFixedSize)
	TArray<FTransform> MocopiTransformWorld;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, EditFixedSize)
	TArray<FTransform> MocopiTransformLocal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, EditFixedSize)
	TArray<FTransform> VrmTransformLocal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FTransform> VrmTransformBoneList;

	FStructMocopiData() {
		MocopiTransformWorld.SetNum(MocopiData::BoneNum);
		MocopiTransformLocal.SetNum(MocopiData::BoneNum);
		VrmTransformLocal.SetNum(MocopiData::BoneNum);
	}
};

class VRM4UCAPTURE_API FMocopiReceiverProxy : public FTickableGameObject
{
	UVrmMocopiReceiver* Receiver;
	FSocket* Socket = nullptr;
	FUdpSocketReceiver* SocketReceiver = nullptr;

	FIPv4Address ReceiveIPAddress;
	int32 Port = 8888;

	TArray<uint8> RecvDataSet;

public:
	FMocopiReceiverProxy(UVrmMocopiReceiver *InReceiver);
	//FMocopiReceiverProxy(UVrmMocopiReceiver& InServer);
	virtual ~FMocopiReceiverProxy();

#if WITH_EDITOR
	virtual bool IsTickableInEditor() const override {
		return true;
	}
#endif // WITH_EDITOR

	void Listen();

	void Stop();

	bool SetAddress(const FString& ReceiveIPAddress, int32 Port);

	virtual void Tick(float InDeltaTime) override;
	virtual TStatId GetStatId() const override;

	void OnPacketReceived(const FArrayReaderPtr& InData, const FIPv4Endpoint& InEndpoint);
};


UCLASS(BlueprintType)
class VRM4UCAPTURE_API UVrmMocopiReceiver : public UObject
{
	TUniquePtr<FMocopiReceiverProxy> ReceiverProxy;

	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "VRM4U")
	void Listen();

	UFUNCTION(BlueprintCallable, Category = "VRM4U")
	void Stop();

	void OnPacketReceived(const FArrayReaderPtr& InData, const FIPv4Endpoint& InEndpoint);

	UFUNCTION(BlueprintCallable, Category = "VRM4U")
	bool SetAddress(const FString& ReceiveIPAddress, int32 Port);


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skeleton, meta = (PinHiddenByDefault))
	//TMap<int, FStructRevData> mapdata;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVrmMocopiReceiverDelegate, FStructMocopiData, data);

	UPROPERTY(BlueprintAssignable, Category = "VRM4U")
	FVrmMocopiReceiverDelegate OnReceived;

protected:
	virtual void BeginDestroy() override;


};
