// Copyright Electronic CAD Monkey [ECM]

#include "ECMMMC_VMRecovery.h"
#include "NanoMagika/AbilitySystem/Attributes/ECMAttributeSet.h"

UECMMMC_VMRecovery::UECMMMC_VMRecovery()
{
	PrepData({UECMAttributeSet::GetPhysiqueAttribute()});
}

float UECMMMC_VMRecovery::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Attributes to harness
	const float Physique = 0;
	TArray<float> Attributes {Physique};

	// Additional variables
	FDataExt DataExt;
	DataExt.Base = 100.f;
	DataExt.Multipler = 5;

	// Gather data from spec
	GatherData(Spec, Attributes, DataExt);
	
	// Calculations
	return (DataExt.Base + (Attributes[0] * DataExt.Multipler)) * DataExt.PlayerLevel * 0.1;
}
