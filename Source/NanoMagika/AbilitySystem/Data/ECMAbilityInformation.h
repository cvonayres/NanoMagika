// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ECMAbilityInformation.generated.h"

struct FGameplayTag;

USTRUCT(BlueprintType)
struct FECMAbilityInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AbilityName;

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag CooldownTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UMaterialInterface> BackgroundMaterial;
	
	FECMAbilityInfo()
	{
		AbilityName = FText();
		InputTag = FGameplayTag();
		Icon = nullptr;
		BackgroundMaterial = nullptr;
	}
};

UCLASS()
class NANOMAGIKA_API UECMAbilityInformation : public UDataAsset
{
	GENERATED_BODY()

public:
	FECMAbilityInfo FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound = false) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	TMap<FGameplayTag, FECMAbilityInfo> AbilityInfo;
	
};
