// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "ECMAbilitySystemGlobals.generated.h"


UCLASS()
class NANOMAGIKA_API UECMAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

public:
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
	
};
