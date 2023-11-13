// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ECMCharacterClassInfo.generated.h"

class UECMGameplayAbility;
class UECMEnemySpecInfo;
class UGameplayAbility;
class UGameplayEffect;

UCLASS()
class NANOMAGIKA_API UECMCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterClassDefaults")
	TMap<FGameplayTag, UECMEnemySpecInfo*> CharacterClassInformation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CommonClassDefaults|Attributes")
	TSubclassOf<UGameplayEffect> VitalAttribute;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CommonClassDefaults|Attributes")
	TSubclassOf<UGameplayEffect> SecondaryAttribute;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CommonClassDefaults|Abilities")
	TArray<TSubclassOf<UECMGameplayAbility>>  CommonAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CommonClassDefaults|Tags")
	TArray<FGameplayTag> CommonTags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CommonClassDefaults|Damage")
	TObjectPtr<UCurveTable> DamageCalculationCoefficients;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CommonClassDefaults|Lifetime")
	float LifeSpan = 5.f;
	
	TObjectPtr<UECMEnemySpecInfo> GetClassDefaultInfo(FGameplayTag EnemyTag) const;
	
};
