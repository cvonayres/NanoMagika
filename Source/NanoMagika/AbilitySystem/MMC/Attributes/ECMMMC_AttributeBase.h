// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "ECMMMC_AttributeBase.generated.h"

UCLASS(Abstract)
class NANOMAGIKA_API UECMMMC_AttributeBase : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:

protected:
	// Variable to capture Physique attribute
	FGameplayEffectAttributeCaptureDefinition AttributeDef;
	
	void PrepData(const FGameplayAttribute& Attribute);
	void GatherData(const FGameplayEffectSpec& Spec, float &AttributeValveOut, int32 &PlayerLevelOut) const;

};
