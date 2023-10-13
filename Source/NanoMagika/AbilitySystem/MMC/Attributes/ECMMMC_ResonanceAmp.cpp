// Copyright Electronic CAD Monkey [ECM]

#include "ECMMMC_ResonanceAmp.h"
#include "NanoMagika/AbilitySystem/Attributes/ECMAttributeSet.h"

UECMMMC_ResonanceAmp::UECMMMC_ResonanceAmp()
{
	PrepData({UECMAttributeSet::GetAdaptivityAttribute(), UECMAttributeSet::GetEssenceControlAttribute(),UECMAttributeSet::GetNanomancyAttribute()});
}

float UECMMMC_ResonanceAmp::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Attributes to harness
	const float Adaptivity = 0;
	const float EssenceControl = 0;
	const float Nanomancy = 0;
	TArray<float> Attributes {Adaptivity,EssenceControl,Nanomancy};

	// Additional variables
	FDataExt DataExt;

	// Gather data from spec
	GatherData(Spec, Attributes, DataExt);
	
	// Calculations
	return (Attributes[0] + Attributes[1] + Attributes[2]) / 3 ;
}
