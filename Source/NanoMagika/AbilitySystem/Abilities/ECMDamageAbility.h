// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "ECMGameplayAbility.h"
#include "ECMDamageAbility.generated.h"

USTRUCT(BlueprintType)
struct FDamageRange
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="User|Damage")
	FScalableFloat DamageMin = FScalableFloat();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="User|Damage")
	FScalableFloat DamageMax = FScalableFloat();
};


UCLASS()
class NANOMAGIKA_API UECMDamageAbility : public UECMGameplayAbility
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="User|Damage")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="User|Damage")
	TMap<FGameplayTag, FDamageRange> DamageTypes;

};
