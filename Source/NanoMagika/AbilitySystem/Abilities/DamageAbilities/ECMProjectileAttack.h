// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "ECMDamageAbility.h"
#include "ECMProjectileAttack.generated.h"

class AECMProjectileEffect;

UCLASS()
class NANOMAGIKA_API UECMProjectileAttack : public UECMDamageAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	/** Projectile Functions */
	UFUNCTION(BlueprintCallable, Category="Default|Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation);
	/* Projectile Functions **/
	
	/** Projectile Properties */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default|Projectile")
	TSubclassOf<AECMProjectileEffect> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default|Projectile")
	bool bModifyPitch = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default|Projectile", meta=(EditCondition="bModifyPitch"))
	float Pitch = 0.f;;
	/* Projectile Properties **/

};
