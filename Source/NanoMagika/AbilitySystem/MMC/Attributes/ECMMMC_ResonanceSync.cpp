// Copyright Electronic CAD Monkey [ECM]

#include "ECMMMC_ResonanceSync.h"
#include "NanoMagika/AbilitySystem/ECMAttributeSet.h"

UECMMMC_ResonanceSync::UECMMMC_ResonanceSync()
{
		PrepData({UECMAttributeSet::GetNeuralAgilityAttribute(), UECMAttributeSet::GetEmpathicResonanceAttribute(),UECMAttributeSet::GetEssenceControlAttribute(), UECMAttributeSet::GetNanomancyAttribute()});
}

float UECMMMC_ResonanceSync::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Attributes to harness
	const float NeuralAgility = 0;
	const float EmpathicResonance = 0;
	const float EssenceControl = 0;
	const float Nanomancy = 0;
	TArray<float> Attributes {NeuralAgility,EmpathicResonance,EssenceControl,Nanomancy};

	// Additional variables
	FDataExt DataExt;

	// Gather data from spec
	GatherData(Spec, Attributes, DataExt);
	
	// Calculations
	return (Attributes[0] + Attributes[1] + Attributes[2] + Attributes[3]) / 4 ;
}
