// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ECMCharacterClassInfo.generated.h"

class UECMEnemySpecInfo;
class UGameplayAbility;
class UGameplayEffect;

UCLASS()
class NANOMAGIKA_API UECMCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="CharacterClassDefaults")
	TMap<FGameplayTag, UECMEnemySpecInfo*> CharacterClassInformation;

	UPROPERTY(EditDefaultsOnly, Category="CommonClassDefaults|Attributes")
	TSubclassOf<UGameplayEffect> VitalAttribute;
	
	UPROPERTY(EditDefaultsOnly, Category="CommonClassDefaults|Attributes")
	TSubclassOf<UGameplayEffect> SecondaryAttribute;

	UPROPERTY(EditDefaultsOnly, Category="CommonClassDefaults|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;

	UPROPERTY(EditDefaultsOnly, Category="CommonClassDefaults|Tags")
	TArray<FGameplayTag> CommonTags;

	UPROPERTY(EditDefaultsOnly, Category="CommonClassDefaults|Damage")
	TObjectPtr<UCurveTable> DamageCalculationCoefficients;

	TObjectPtr<UECMEnemySpecInfo> GetClassDefaultInfo(FGameplayTag EnemyTag);

};
