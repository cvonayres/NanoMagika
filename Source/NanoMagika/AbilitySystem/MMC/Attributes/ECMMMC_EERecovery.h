// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "NanoMagika/AbilitySystem/MMC/ECMMMC_AttributeBase.h"
#include "ECMMMC_EERecovery.generated.h"

UCLASS()
class NANOMAGIKA_API UECMMMC_EERecovery : public UECMMMC_AttributeBase
{
	GENERATED_BODY()
	
public:
	UECMMMC_EERecovery();
	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
