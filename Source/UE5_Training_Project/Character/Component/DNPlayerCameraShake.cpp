


#include "UE5_Training_Project/Character/Component/DNPlayerCameraShake.h"


UDNPlayerCameraShake::UDNPlayerCameraShake()
{
	OscillationDuration = 0.1f;
	OscillationBlendInTime = 0.05f;
	OscillationBlendOutTime = 0.05f;

	RotOscillation.Pitch.Amplitude = 15.0f;
	RotOscillation.Pitch.Frequency = 1.0f;
	RotOscillation.Pitch.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
}