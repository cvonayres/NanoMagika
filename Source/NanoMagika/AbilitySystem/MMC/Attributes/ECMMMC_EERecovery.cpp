// Copyright Electronic CAD Monkey [ECM]

#include "ECMMMC_EERecovery.h"
#include "NanoMagika/AbilitySystem/ECMAttributeSet.h"

UECMMMC_EERecovery::UECMMMC_EERecovery()
{
	PrepData({UECMAttributeSet::GetPhysiqueAttribute()});
}

float UECMMMC_EERecovery::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Attributes to harness
	const float Physique = 0;
	TArray<float> Attributes {Physique};

	// Additional variables
	FDataExt DataExt;
	DataExt.Base = 50.f;
	DataExt.Multipler = 5;

	// Gather data from spec
	GatherData(Spec, Attributes, DataExt);
	
	// Calculations
	return (DataExt.Base + (Attributes[0] * DataExt.Multipler)) * DataExt.PlayerLevel * 0.1;
}
