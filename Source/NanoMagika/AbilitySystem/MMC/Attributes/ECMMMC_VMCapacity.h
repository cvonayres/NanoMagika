// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "ECMMMC_VMCapacity.generated.h"

UCLASS()
class NANOMAGIKA_API UECMMMC_VMCapacity : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UECMMMC_VMCapacity();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	// Variable to capture Physique attribute
	FGameplayEffectAttributeCaptureDefinition PhysiqueDef;

	// Valves to be used in calculation
	float BaseValve = 100.f;
	float AttributeMultiplier = 5.f;
	
};
