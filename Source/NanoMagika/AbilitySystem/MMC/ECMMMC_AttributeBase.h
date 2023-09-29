// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "ECMMMC_AttributeBase.generated.h"

USTRUCT()
struct FDataExt
{
	GENERATED_BODY()

	int32 PlayerLevel = 0;
	float Base = 0.f;
	float Multipler = 0.f;
};

// Base class for MMCs for secondary attributes that depend upon primary attributes or player level.
UCLASS(Abstract)
class NANOMAGIKA_API UECMMMC_AttributeBase : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

protected:
	// Place holder for attribute definitions
	FGameplayEffectAttributeCaptureDefinition AttributeDef1;
	FGameplayEffectAttributeCaptureDefinition AttributeDef2;
	FGameplayEffectAttributeCaptureDefinition AttributeDef3;
	FGameplayEffectAttributeCaptureDefinition AttributeDef4;
	FGameplayEffectAttributeCaptureDefinition AttributeDef5;
    FGameplayEffectAttributeCaptureDefinition AttributeDef6;
	TArray<FGameplayEffectAttributeCaptureDefinition> AttributeDefs = {AttributeDef1, AttributeDef2, AttributeDef3, AttributeDef4, AttributeDef5, AttributeDef6};

	// Place holder for extra harnessed info, i.e. player level
	//FDataExt DataExt;
	
	// Set Attribute definitions at child constructor
	void PrepData(const TArray<FGameplayAttribute> &AttributesOut);

	// Retreive Attribute valves as a TArray along with Player Level 
	void GatherData(const FGameplayEffectSpec Spec, TArray<float> &AttributeValuesOut, FDataExt &DataExtOut) const;

};
