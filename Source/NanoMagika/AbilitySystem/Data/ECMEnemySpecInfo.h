// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ECMEnemySpecInfo.generated.h"

class UGameplayAbility;
class UGameplayEffect;

UCLASS()
class NANOMAGIKA_API UECMEnemySpecInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="ClassDefaults")
	TSubclassOf<UGameplayEffect> PrimaryAttribute;
	
	UPROPERTY(EditDefaultsOnly, Category="ClassDefaults")
	TArray<TSubclassOf<UGameplayAbility>> Abilities;

	UPROPERTY(EditDefaultsOnly, Category="ClassDefaults")
	TArray<FGameplayTag> Tags;
};
