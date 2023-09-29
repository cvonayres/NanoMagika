// Copyright Electronic CAD Monkey [ECM]

#include "ECMMMC_TechnologicalInfluence.h"
#include "NanoMagika/AbilitySystem/ECMAttributeSet.h"

UECMMMC_TechnologicalInfluence::UECMMMC_TechnologicalInfluence()
{
	PrepData({UECMAttributeSet::GetAdaptivityAttribute(), UECMAttributeSet::GetNanomancyAttribute()});
}

float UECMMMC_TechnologicalInfluence::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
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
