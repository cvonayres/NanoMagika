// Copyright Electronic CAD Monkey [ECM]

#include "ECMAbilitySystemGlobals.h"
#include "NanoMagika/ECMAbilityTypes.h"

FGameplayEffectContext* UECMAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FECMGameplayEffectContext();
}
