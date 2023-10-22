// Copyright Electronic CAD Monkey [ECM]

#include "ECMItemClassInfo.h"
#include "ECMItemSpecInfo.h"

UECMItemSpecInfo* UECMItemClassInfo::GetItemDefaultInfo(FGameplayTag ItemTag)
{
	return ItemClassInformation.FindChecked(ItemTag);
}

FText UECMItemClassInfo::GetItemName(FGameplayTag ItemTag)
{
	return GetItemDefaultInfo(ItemTag)->GetItemName();
}

FText UECMItemClassInfo::GetItemDescription(FGameplayTag ItemTag)
{
	return GetItemDefaultInfo(ItemTag)->GetItemDescription();
}

UTexture2D* UECMItemClassInfo::GetItemIcon(FGameplayTag ItemTag)
{
	return GetItemDefaultInfo(ItemTag)->GetItemIcon();
}
