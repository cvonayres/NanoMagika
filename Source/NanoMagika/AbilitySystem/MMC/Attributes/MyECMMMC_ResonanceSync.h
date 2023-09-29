// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "NanoMagika/AbilitySystem/MMC/ECMMMC_AttributeBase.h"
#include "MyECMMMC_ResonanceSync.generated.h"

UCLASS()
class NANOMAGIKA_API UMyECMMMC_ResonanceSync : public UECMMMC_AttributeBase
{
	GENERATED_BODY()
							
public:
	UMyECMMMC_ResonanceSync();
	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
