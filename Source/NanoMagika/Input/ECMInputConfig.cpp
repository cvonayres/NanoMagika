// Copyright Electronic CAD Monkey [ECM]

#include "ECMInputConfig.h"

const UInputAction* UECMInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{

	for(const FECMInputAction& Action : AbilityInputActions)
	{
		if(Action.InputAction && Action.InputTag == InputTag) {	return Action.InputAction; }
	}

	if(bLogNotFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}
