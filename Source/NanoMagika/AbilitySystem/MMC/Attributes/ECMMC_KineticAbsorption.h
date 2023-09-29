// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "NanoMagika/AbilitySystem/MMC/ECMMMC_AttributeBase.h"
#include "ECMMC_KineticAbsorption.generated.h"

UCLASS()
class NANOMAGIKA_API UECMMC_KineticAbsorption : public UECMMMC_AttributeBase
{
	GENERATED_BODY()
	
public:
	UECMMC_KineticAbsorption();
	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
