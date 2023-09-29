// Copyright Electronic CAD Monkey [ECM]

#include "ECMMC_KineticAbsorption.h"
#include "NanoMagika/AbilitySystem/ECMAttributeSet.h"

UECMMC_KineticAbsorption::UECMMC_KineticAbsorption()
{
	PrepData({UECMAttributeSet::GetPhysiqueAttribute(), UECMAttributeSet::GetEssenceControlAttribute()});
}

float UECMMC_KineticAbsorption::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Attributes to harness
	const float Physique = 0;
	const float EssenceControl = 0;
	TArray<float> Attributes {Physique,EssenceControl};

	// Additional variables
	FDataExt DataExt;

	// Gather data from spec
	GatherData(Spec, Attributes, DataExt);
	
	// Calculations
	return (Attributes[0] + Attributes[1]) / 2 ;
}
