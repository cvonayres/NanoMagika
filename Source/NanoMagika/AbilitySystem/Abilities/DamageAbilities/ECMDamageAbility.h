// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "NanoMagika/AbilitySystem/Abilities/ECMGameplayAbility.h"
#include "ECMDamageAbility.generated.h"

USTRUCT(BlueprintType)
struct FDamageRange
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat DamageMin = FScalableFloat();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat DamageMax = FScalableFloat();
};


UCLASS()
class NANOMAGIKA_API UECMDamageAbility : public UECMGameplayAbility
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category="Default|Damage")
	void CauseDamage();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default|Damage")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default|Damage")
	TMap<FGameplayTag, FDamageRange> DamageTypes;
	
	void SetDamageMagnitude(const FGameplayEffectSpecHandle& SpecHandle);

protected:
	UPROPERTY(BlueprintReadOnly, Category="Melee Attack")
	AActor* OwningActor = nullptr;
	UPROPERTY(BlueprintReadOnly, Category="Melee Attack")
	AActor* TargetActor = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Melee Attack")
	UAnimMontage* Montage = nullptr;
	UPROPERTY(BlueprintReadOnly, Category="Melee Attack")
	FGameplayTag MontageTag = FGameplayTag();
	
	void GetRandomAttackMontages();
};
