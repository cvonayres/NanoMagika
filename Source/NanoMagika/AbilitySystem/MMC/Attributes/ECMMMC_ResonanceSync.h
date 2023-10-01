// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "NanoMagika/AbilitySystem/MMC/ECMMMC_AttributeBase.h"
#include "ECMMMC_ResonanceSync.generated.h"

UCLASS()
class NANOMAGIKA_API UECMMMC_ResonanceSync : public UECMMMC_AttributeBase
{
	GENERATED_BODY()
							
public:
	UECMMMC_ResonanceSync();
	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
