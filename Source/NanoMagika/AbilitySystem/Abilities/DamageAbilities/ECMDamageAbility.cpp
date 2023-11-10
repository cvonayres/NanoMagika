// Copyright Electronic CAD Monkey [ECM]

#include "ECMDamageAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NanoMagika/Interaction/ECMCombatInterface.h"
#include "NanoMagika/Interaction/ECMEnemyInterface.h"

void UECMDamageAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	
	OwningActor = GetAvatarActorFromActorInfo();
	if ( OwningActor == nullptr || !OwningActor->Implements<UECMCombatInterface>() ) return;

	// Function is only implemented on Emeny Characters
	TargetActor = IECMCombatInterface::Execute_GetCombatTarget(OwningActor);
	if ( TargetActor )
	{
		IECMCombatInterface::Execute_UpdateFacingTarget(OwningActor, TargetActor->GetActorLocation());
	
		GetRandomAttackMontages();
	} 
	
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UECMDamageAbility::GetRandomAttackMontages()
{
	if (OwningActor == nullptr || !OwningActor->Implements<UECMEnemyInterface>()) return;

	if (TArray<TTuple<FGameplayTag, UAnimMontage*>> AttackMontages = IECMEnemyInterface::Execute_GetAttackMontages(OwningActor).Array(); AttackMontages.Num() > 0)
	{
		const TPair<FGameplayTag, UAnimMontage*> AttackMontage = AttackMontages[FMath::RandRange(0, AttackMontages.Num() - 1)];
		MontageTag = AttackMontage.Key;
		Montage = AttackMontage.Value;
	}	
}

void UECMDamageAbility::CauseDamage()
{
	if (TargetActor == nullptr) return;
	
	const FGameplayEffectSpecHandle DamageSpecHandle  =MakeOutgoingGameplayEffectSpec(DamageEffectClass, GetAbilityLevel());
	SetDamageMagnitude( DamageSpecHandle );
	
	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle .Data.Get(), UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));

}

void UECMDamageAbility::SetDamageMagnitude(const FGameplayEffectSpecHandle& SpecHandle)
{
	if ( !SpecHandle.IsValid() || DamageTypes.IsEmpty()) return;
	
	for ( TTuple<FGameplayTag, FDamageRange>& Pair : DamageTypes )
	{
		const float ScaledMagnitudeMin = Pair.Value.DamageMin.GetValueAtLevel(GetAbilityLevel());
		const float ScaledMagnitudeMax = Pair.Value.DamageMax.GetValueAtLevel(GetAbilityLevel());
		const float Magnitude = FMath::RandRange(ScaledMagnitudeMin, ScaledMagnitudeMax);

		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, Magnitude);
	}
}

