// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "NanoMagika/AbilitySystem/MMC/ECMMMC_AttributeBase.h"
#include "ECMMMC_NanoShield.generated.h"

UCLASS()
class NANOMAGIKA_API UECMMMC_NanoShield : public UECMMMC_AttributeBase
{
	GENERATED_BODY()
	
public:
	UECMMMC_NanoShield();
	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
