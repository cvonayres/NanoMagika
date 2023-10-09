// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "ECMGameplayAbility.h"
#include "ECMProjectileSpell.generated.h"

class AECMProjectile;

UCLASS()
class NANOMAGIKA_API UECMProjectileSpell : public UECMGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	TSubclassOf<AECMProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	bool bModifyPitch = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	float Pitch = 0.f;;
	
	UFUNCTION(BlueprintCallable, Category="Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
};
