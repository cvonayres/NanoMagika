// Copyright Electronic CAD Monkey [ECM]

#include "ECMMMC_ReactionSpeed.h"
#include "NanoMagika/AbilitySystem/ECMAttributeSet.h"

UECMMMC_ReactionSpeed::UECMMMC_ReactionSpeed()
{
	PrepData({UECMAttributeSet::GetAdaptivityAttribute(), UECMAttributeSet::GetNeuralAgilityAttribute()});
}

float UECMMMC_ReactionSpeed::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Attributes to harness
	const float Adaptivity = 0;
	const float NeuralAgility = 0;
	TArray<float> Attributes {Adaptivity,NeuralAgility};

	// Additional variables
	FDataExt DataExt;

	// Gather data from spec
	GatherData(Spec, Attributes, DataExt);
	
	// Calculations
	return (Attributes[0] + Attributes[1]) / 2 ;
}
