// Copyright Electronic CAD Monkey [ECM]

#include "ECMMMC_EmpathicInfluence.h"
#include "NanoMagika/AbilitySystem/ECMAttributeSet.h"

UECMMMC_EmpathicInfluence::UECMMMC_EmpathicInfluence()
{
	PrepData({UECMAttributeSet::GetNeuralAgilityAttribute(), UECMAttributeSet::GetEmpathicResonanceAttribute()});
}

float UECMMMC_EmpathicInfluence::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Attributes to harness
	const float NeuralAgility = 0;
	const float EmpathicResonance = 0;
	TArray<float> Attributes {NeuralAgility,EmpathicResonance};

	// Additional variables
	FDataExt DataExt;

	// Gather data from spec
	GatherData(Spec, Attributes, DataExt);
	
	// Calculations
	return (Attributes[0] + Attributes[1]) / 2 ;
}
