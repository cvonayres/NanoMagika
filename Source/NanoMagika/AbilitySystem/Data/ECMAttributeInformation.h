// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "NanoMagika/AbilitySystem/Attributes/ECMAttributeSet.h"
#include "ECMAttributeInformation.generated.h"

struct FGameplayTag;

USTRUCT(BlueprintType)
struct FECMAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValve = 0;
};

UCLASS()
class NANOMAGIKA_API UECMAttributeInformation : public UDataAsset
{
	GENERATED_BODY()

public:
	FECMAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	TArray<FECMAttributeInfo> VitalAttributeInformation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	TArray<FECMAttributeInfo> PrimaryAttributeInformation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	TArray<FECMAttributeInfo> SecondaryAttributeInformation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	TArray<FECMAttributeInfo> TertiaryAttributeInformation;
};
