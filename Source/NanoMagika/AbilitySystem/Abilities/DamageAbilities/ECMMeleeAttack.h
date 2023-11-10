// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "ECMDamageAbility.h"
#include "ECMMeleeAttack.generated.h"

UCLASS()
class NANOMAGIKA_API UECMMeleeAttack : public UECMDamageAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category="Melee Attack")
	void DamageActorsInRadius(bool bDebug);
	
};
