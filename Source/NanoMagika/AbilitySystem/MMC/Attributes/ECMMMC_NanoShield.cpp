// Copyright Electronic CAD Monkey [ECM]

#include "ECMMMC_NanoShield.h"

#include "NanoMagika/AbilitySystem/Attributes/ECMAttributeSet.h"
#include "NanoMagika/AbilitySystem/Attributes/ECMAttributeSet.h"

UECMMMC_NanoShield::UECMMMC_NanoShield()
{
	PrepData({UECMAttributeSet::GetPhysiqueAttribute(), UECMAttributeSet::GetNanomancyAttribute()});
}

float UECMMMC_NanoShield::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Attributes to harness
	const float Physique = 0;
	const float Nanomancy = 0;
	TArray<float> Attributes {Physique,Nanomancy};

	// Additional variables
	FDataExt DataExt;

	// Gather data from spec
	GatherData(Spec, Attributes, DataExt);
	
	// Calculations
	return (Attributes[0] + Attributes[1]) / 2 ;
}
