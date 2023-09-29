// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "NanoMagika/AbilitySystem/MMC/ECMMMC_AttributeBase.h"
#include "MyECMMMC_ResonanceAmp.generated.h"

UCLASS()
class NANOMAGIKA_API UMyECMMMC_ResonanceAmp : public UECMMMC_AttributeBase
{
	GENERATED_BODY()
						
public:
	UMyECMMMC_ResonanceAmp();
	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
