// Copyright Electronic CAD Monkey [ECM]

#include "ECMMMC_ARRecovery.h"
#include "NanoMagika/AbilitySystem/ECMAttributeSet.h"

UECMMMC_ARRecovery::UECMMMC_ARRecovery()
{
	PrepData({UECMAttributeSet::GetEssenceControlAttribute()});
}

float UECMMMC_ARRecovery::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Attributes to harness
	const float EssenceControl = 0;
	TArray<float> Attributes {EssenceControl};

	// Additional variables
	FDataExt DataExt;
	DataExt.Base = 50.f;
	DataExt.Multipler = 2.5;

	// Gather data from spec
	GatherData(Spec, Attributes, DataExt);
	
	// Calculations
	return (DataExt.Base + (Attributes[0] * DataExt.Multipler)) * DataExt.PlayerLevel * 0.1 ;
}
