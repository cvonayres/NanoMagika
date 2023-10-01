// Copyright Electronic CAD Monkey [ECM]

#include "ECMAttributeInformation.h"

FECMAttributeInfo UECMAttributeInformation::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{

	for(const FECMAttributeInfo& Info : VitalAttributeInformation)
	{
		if (Info.AttributeTag == AttributeTag) { return Info; }
	}

	for(const FECMAttributeInfo& Info : PrimaryAttributeInformation)
	{
		if (Info.AttributeTag == AttributeTag) { return Info; }
	}
	
	for(const FECMAttributeInfo& Info : SecondaryAttributeInformation)
	{
		if (Info.AttributeTag == AttributeTag) { return Info; }
	}
	
	for(const FECMAttributeInfo& Info : TertiaryAttributeInformation)
	{
		if (Info.AttributeTag == AttributeTag) { return Info; }
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can;t find Infor for AttributeTag [%s] on AttributeInfo [%s]"), *AttributeTag.ToString(), *GetNameSafe(this))
	}
	
	return FECMAttributeInfo();
}
