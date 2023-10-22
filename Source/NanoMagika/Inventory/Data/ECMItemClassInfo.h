// Copyright Electronic CAD Monkey [ECM]

#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ECMItemClassInfo.generated.h"

class UECMItemSpecInfo;

UCLASS()
class NANOMAGIKA_API UECMItemClassInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintGetter, Category="Tags")
	UECMItemSpecInfo* GetItemDefaultInfo(FGameplayTag ItemTag);

	UFUNCTION(BlueprintGetter, Category="Description")
	FText GetItemName(FGameplayTag ItemTag);

	UFUNCTION(BlueprintGetter, Category="Description")
	FText GetItemDescription(FGameplayTag ItemTag);

	UFUNCTION(BlueprintGetter, Category="Icon")
	UTexture2D* GetItemIcon(FGameplayTag ItemTag);

private:
	UPROPERTY(EditDefaultsOnly, Category="ItemClassDefaults")
	TMap<FGameplayTag, UECMItemSpecInfo*> ItemClassInformation;

};
