// Copyright Electronic CAD Monkey [ECM]

#include "ECMMMC_StealthSignal.h"
#include "NanoMagika/AbilitySystem/ECMAttributeSet.h"

UECMMMC_StealthSignal::UECMMMC_StealthSignal()
{
	PrepData({UECMAttributeSet::GetAdaptivityAttribute(), UECMAttributeSet::GetNanomancyAttribute()});
}

float UECMMMC_StealthSignal::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Attributes to harness
	const float Adaptivity = 0;
	const float Nanomancy = 0;
	TArray<float> Attributes {Adaptivity,Nanomancy};

	// Additional variables
	FDataExt DataExt;

	// Gather data from spec
	GatherData(Spec, Attributes, DataExt);
	
	// Calculations
	return (Attributes[0] + Attributes[1]) / 2 ;
}

