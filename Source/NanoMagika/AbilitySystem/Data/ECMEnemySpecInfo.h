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
	UPROPERTY(EditDefaultsOnly, Category="ClassDefaults|Tags")
	FGameplayTag ClassTag;

	UPROPERTY(EditDefaultsOnly, Category="ClassDefaults|Attributes")
	TSubclassOf<UGameplayEffect> PrimaryAttribute;
	
	UPROPERTY(EditDefaultsOnly, Category="ClassDefaults|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> Abilities;

	UPROPERTY(EditDefaultsOnly, Category="ClassDefaults|Tags")
	TArray<FGameplayTag> Tags;
};
