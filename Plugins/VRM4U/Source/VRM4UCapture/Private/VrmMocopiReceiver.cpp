// Fill out your copyright notice in the Description page of Project Settings.


#include "VrmMocopiReceiver.h"

#include "VRM4UCaptureLog.h"

#include "CoreGlobals.h"
#include "Stats/Stats.h"
#include "Tickable.h"
#include "Common/UdpSocketReceiver.h"
//
// 

FMocopiReceiverProxy::FMocopiReceiverProxy(UVrmMocopiReceiver * InReceiver):
	Receiver(InReceiver){
	FIPv4Address::Parse("127.0.0.1", ReceiveIPAddress);
}

FMocopiReceiverProxy::~FMocopiReceiverProxy() {
	Stop();
}

void FMocopiReceiverProxy::Stop() {
	if (SocketReceiver) {
		delete SocketReceiver;
		SocketReceiver = nullptr;
	}
	if (Socket) {
		Socket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
		Socket = nullptr;
	}
}

void FMocopiReceiverProxy::Listen() {
	FString InServerName = "udp_serv";
	//int32 Port = 12351;
	bool bMulticastLoopback = true;

	FUdpSocketBuilder Builder(*InServerName);
	Builder.BoundToPort(Port);
	if (ReceiveIPAddress.IsMulticastAddress())
	{
		Builder.JoinedToGroup(ReceiveIPAddress);
		if (bMulticastLoopback)
		{
			Builder.WithMulticastLoopback();
		}
	}
	else
	{
		if (bMulticastLoopback)
		{
			//UE_LOG(LogOSC, Warning, TEXT("OSCServer '%s' ReceiveIPAddress provided is not a multicast address.  Not respecting MulticastLoopback boolean."),
			//	*InServerName);
		}
		Builder.BoundToAddress(ReceiveIPAddress);
	}

	Socket = Builder.Build();
	if (Socket)
	{
		SocketReceiver = new FUdpSocketReceiver(Socket, FTimespan::FromMilliseconds(100), *(InServerName + TEXT("_ListenerThread")));
		SocketReceiver->OnDataReceived().BindRaw(this, &FMocopiReceiverProxy::OnPacketReceived);
		SocketReceiver->Start();

		//UE_LOG(LogOSC, Display, TEXT("OSCServer '%s' Listening: %s:%d."), *InServerName, *ReceiveIPAddress.ToString(), Port);
	}
	else
	{
		// This is expected when the server isn't available, so it's not a Warning
		//UE_LOG(LogOSC, Display, TEXT("OSCServer '%s' failed to bind to socket on %s:%d. Check that the server is available on the specified address."), *InServerName, *ReceiveIPAddress.ToString(), Port);
	}
}

bool FMocopiReceiverProxy::SetAddress(const FString& InReceiveIPAddress, int32 InPort) {
	if (!FIPv4Address::Parse(InReceiveIPAddress, ReceiveIPAddress))
	{
		//UE_LOG(LogOSC, Error, TEXT("Invalid ReceiveIPAddress '%s'. OSCServer ReceiveIP Address not updated."), *InReceiveIPAddress);
		return false;
	}

	Port = InPort;
	return true;
}
void FMocopiReceiverProxy::Tick(float InDeltaTime) {

}

TStatId FMocopiReceiverProxy::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(FMocopiReceiverProxy, STATGROUP_Tickables);
}

void FMocopiReceiverProxy::OnPacketReceived(const FArrayReaderPtr& InData, const FIPv4Endpoint& InEndpoint) {

	RecvDataSet.Append(InData->GetData(), InData->Num());

	// data size limit
	if (RecvDataSet.Num() >= 1024 * 64) {
		decltype(RecvDataSet) a;
		a.Append(RecvDataSet.GetData() + 1024*48, RecvDataSet.Num() - 1024*48);
		RecvDataSet = a;
	}


	//UE_LOG(LogVRM4UCapture, Verbose, TEXT("recv '%d' "), InData->Num());

	struct LocalStructRawData {
		TArray<float> f;
		FQuat rot;
		FVector pos;

		LocalStructRawData() {
			f.SetNum(7);
		}
	};

	struct LocalStructTransData {
		//TArray<LocalStructRawData> data;

		TArray<FTransform> transformLocal;
		TArray <FTransform> transform;
		TArray <FTransform> transformVrmLocal;


		LocalStructTransData() {
			transform.SetNum(MocopiData::BoneNum);
			transformLocal.SetNum(MocopiData::BoneNum);
			transformVrmLocal.SetNum(MocopiData::BoneNum);
			//data.SetNum(MocopiData::BoneNum);
		}
	};

	LocalStructTransData d;

	const char FIELD_HEAD[] = {
		'h', 'e', 'a', 'd',
	};

	const char FIELD_SKDF[] = {
		's', 'k', 'd', 'f',
	};

	const char FIELD_TRAN[] = {
		't', 'r', 'a', 'n',
	};

	const char FIELD_BNID[] = {
		'b', 'n', 'i', 'd',
	};

	const char FIELD_FRAM[] = {
		'f', 'r', 'a', 'm',
	};

	const int BoneChain[] = {
		0,	// 0
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		7,	// 11
		11, 12, 13,
		7,	// 15
		15, 16, 17,
		0,	//19
		19, 20, 21,
		0,	//23
		23, 24, 25,
	};

	auto GetValue = [&](int cur, const char field[4]) {
		{
			int t = 0;
			for (t = 0; t < 4; ++t) {
				if (field[t] != RecvDataSet.GetData()[cur + t]) {
					break;
				}
			}
			if (t == 4) {
				return (RecvDataSet.GetData() + cur + 4);
			}
		}
		return (uint8*)nullptr;
	};


	int32* frame = nullptr;
	float* TransformData = nullptr;
	uint16* boneid = nullptr;
	float ff[7] = {};


	for (int i = RecvDataSet.Num() - 4; i >= 8; --i) {
		if (isalpha(RecvDataSet.GetData()[i]) == false) {
			continue;
		}

		uint8* p = nullptr;
		p = GetValue(i, FIELD_FRAM);
		if (p) {

			// p == value
			// p-4 == field
			// p-8 == packetsize
			// 
			// i == field
			// i-4 == packetsize

			uint16* packetSize = reinterpret_cast<uint16*>(p - 8);

			//UE_LOG(LogVRM4UCapture, Verbose, TEXT("packetSize '%d'"), (*packetSize));

			if ((*packetSize) + 8 <= RecvDataSet.Num()) {
				//UE_LOG(LogVRM4UCapture, Verbose, TEXT("shrink '%d' -> %d "), RecvDataSet.Num(), (*packetSize) + 8);

				decltype(RecvDataSet) a;
				a.Append(RecvDataSet.GetData() + i - 4, (*packetSize) + 8);
				RecvDataSet = a;

			}
		}
	}


	for (int i = 0; i < RecvDataSet.Num() - 4; ++i) {
		if (isalpha(RecvDataSet.GetData()[i]) == false) {
			continue;
		}
		uint8* p = nullptr;

		p = GetValue(i, FIELD_BNID);
		if (p) {
			boneid = reinterpret_cast<uint16*>(p);
		}

		p = GetValue(i, FIELD_TRAN);
		if (p) {
			TransformData = reinterpret_cast<float*>(p);
		}

		p = GetValue(i, FIELD_FRAM);
		if (p) {
			frame = reinterpret_cast<int32*>(p);
		}

		/*
		{
			int t = 0;
			for (t = 0; t < 4; ++t) {
				if (isalpha((RecvDataSet.GetData()[i + t])) == false) {
					break;
				}
			}
			if (t == 4) {
				UE_LOG(LogVRM4UCapture, Verbose, TEXT("recv '%c%c%c%c' "),
					*((char*)(RecvDataSet.GetData()) + i),
					*((char*)(RecvDataSet.GetData()) + i+1),
					*((char*)(RecvDataSet.GetData()) + i+2),
					*((char*)(RecvDataSet.GetData()) + i+3)
					);
			}
		}
		*/

		if (boneid && TransformData) {
			// mocopi
			{
				LocalStructRawData st;

				st.rot = FQuat(-TransformData[0], -TransformData[1], TransformData[2], TransformData[3]);
				if (*boneid == 0) {
					st.rot = FRotator(0, 0, -90).Quaternion() * st.rot;
				}

				st.pos.Set(TransformData[4], TransformData[5], -TransformData[6]);
				st.pos *= 100.f;

				d.transformLocal[*boneid] = FTransform(st.rot, st.pos);
			}

			// vrm
			{
				LocalStructRawData st;

				d.transformVrmLocal[*boneid] = FTransform(st.rot, st.pos);
				st.rot = FQuat(-TransformData[0], -TransformData[1], TransformData[2], TransformData[3]);
				st.rot = FRotator(0, 0, -90).Quaternion() * st.rot * FRotator(0, 0, -90).Quaternion().Inverse();

				st.pos.Set(TransformData[4], TransformData[6], TransformData[5]);
				st.pos *= 100.f;

				d.transformVrmLocal[*boneid] = FTransform(st.rot, st.pos);
			}

			boneid = nullptr;
			TransformData = nullptr;
		}
	}
	if (d.transformLocal.Num() != MocopiData::BoneNum) return;

	d.transform = d.transformLocal;


	for (int i = 1; i < MocopiData::BoneNum; ++i) {
		int parent = BoneChain[i];

		auto r1 = d.transform[parent].GetRotation();
		auto p1 = d.transform[parent].GetLocation();

		FTransform::Multiply(&d.transform[i], &d.transformLocal[i], &d.transform[parent]);
	}
	FStructMocopiData md;
	if (frame) {
		md.FrameNo = *frame;
	}
	md.MocopiTransformWorld = d.transform;
	md.MocopiTransformLocal = d.transformLocal;

	{
		TMap<FString, int> BoneIdList = {
		{"hips",				0},
		{"leftUpperLeg",		19},
		{"rightUpperLeg",		23},
		{"leftLowerLeg",		20},
		{"rightLowerLeg",		24},
		{"leftFoot",			21},
		{"rightFoot",			25},
		{"spine",				3},	//
		{"chest",				6},	//
		{"upperChest",			7},	//
		{"neck",				8}, //
		{"head",				9},
		{"leftShoulder",		11},
		{"rightShoulder",		15},
		{"leftUpperArm",		12},
		{"rightUpperArm",		16},
		{"leftLowerArm",		13},
		{"rightLowerArm",		17},
		{"leftHand",			14},
		{"rightHand",			18},
		{"leftToes",			22},
		{"rightToes",			26},
		};

		for (auto& b : BoneIdList) {
			md.VrmTransformBoneList.Add(b.Key, d.transformVrmLocal[b.Value]);
		}
	}



	if (Receiver) {
		Receiver->OnReceived.Broadcast(md);
	}
#ifdef PLATFORM_LITTLE_ENDIAN
#endif


}



//


UVrmMocopiReceiver::UVrmMocopiReceiver(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), ReceiverProxy(MakeUnique<FMocopiReceiverProxy>(this))
{
}

void UVrmMocopiReceiver::BeginDestroy() {
	Stop();
	Super::BeginDestroy();
}

bool UVrmMocopiReceiver::SetAddress(const FString& InReceiveIPAddress, int32 InPort) {
	return ReceiverProxy->SetAddress(InReceiveIPAddress, InPort);
}


void UVrmMocopiReceiver::Stop() {
	if (ReceiverProxy) {
		ReceiverProxy->Stop();
	}
}


void UVrmMocopiReceiver::Listen() {
	ReceiverProxy->Listen();
}


