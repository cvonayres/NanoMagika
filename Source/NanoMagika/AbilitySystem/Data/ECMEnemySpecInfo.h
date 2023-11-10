// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ECMEnemySpecInfo.generated.h"

class UECMGameplayAbility;
class UGameplayAbility;
class UGameplayEffect;

UCLASS()
class NANOMAGIKA_API UECMEnemySpecInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="")
	FGameplayTag ClassTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GAS")
	TSubclassOf<UGameplayEffect> PrimaryAttribute;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GAS")
	TArray<TSubclassOf<UECMGameplayAbility>>  Abilities;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GAS")
	TArray<FGameplayTag> Tags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attack")
	FIntPoint AttackRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attack")
	float AttackRadius = 25.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attack")
	TMap<FGameplayTag, UAnimMontage*> AttackMontages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attack")
	UAnimMontage* HitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Misc.")
	float DefaultWalkingSpeed = 200.f;
	
};
