// Copyright Electronic CAD Monkey [ECM]

#include "ECMMMC_PocketCapacity.h"
#include "NanoMagika/AbilitySystem/ECMAttributeSet.h"

UECMMMC_PocketCapacity::UECMMMC_PocketCapacity()
{
	PrepData({UECMAttributeSet::GetNeuralAgilityAttribute(), UECMAttributeSet::GetEssenceControlAttribute(),UECMAttributeSet::GetNanomancyAttribute()});
}

float UECMMMC_PocketCapacity::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Attributes to harness
	const float NeuralAgility = 0;
	const float EssenceControl = 0;
	const float Nanomancy = 0;
	TArray<float> Attributes {NeuralAgility,EssenceControl,Nanomancy};

	// Additional variables
	FDataExt DataExt;

	// Gather data from spec
	GatherData(Spec, Attributes, DataExt);
	
	// Calculations
	return (Attributes[0] + Attributes[1] + Attributes[2]) / 3 ;
}
