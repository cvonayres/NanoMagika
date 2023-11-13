// Copyright Electronic CAD Monkey [ECM]

#include "ECMAbilityInformation.h"
#include "NanoMagika/ECMLogChannels.h"

FECMAbilityInfo UECMAbilityInformation::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
	if( !AbilityTag.IsValid() ) return FECMAbilityInfo();

	if ( AbilityInfo.Contains(AbilityTag) )
	{
		return AbilityInfo.FindRef(AbilityTag);
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogECM, Error, TEXT("Can't find Info. for AttributeTag [%s] on AttributeInfo [%s]"), *AbilityTag.ToString(), *GetNameSafe(this))
	}
	
	return FECMAbilityInfo();
}
