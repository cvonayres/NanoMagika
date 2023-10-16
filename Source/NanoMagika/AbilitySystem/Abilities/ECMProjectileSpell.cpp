// Copyright Electronic CAD Monkey [ECM]

#include "ECMProjectileSpell.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NanoMagika/Effect/ECMProjectile.h"
#include "NanoMagika/Interaction/ECMCombatInterface.h"

void UECMProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UECMProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if(!bIsServer) return;

	IECMCombatInterface* CombatInterface = Cast<IECMCombatInterface>(GetAvatarActorFromActorInfo());
	if(CombatInterface == nullptr) return;

	const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
//	if(bModifyPitch) Rotation.Pitch = Pitch;
		
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());
		
	AECMProjectile* Projectile = GetWorld()->SpawnActorDeferred<AECMProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	const UAbilitySystemComponent* SourceASC =UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());

	FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
	PopulateContextHandle(EffectContextHandle, Projectile, ProjectileTargetLocation);

	CreateAndApplySpecHandle(Projectile, SourceASC, EffectContextHandle);
	
	Projectile->FinishSpawning(SpawnTransform);
}

void UECMProjectileSpell::PopulateContextHandle(FGameplayEffectContextHandle& EffectContextHandle, AECMProjectile* Projectile, const FVector& ProjectileTargetLocation) const
{
	//Ability
	EffectContextHandle.SetAbility(this);

	// Source Object
	EffectContextHandle.AddSourceObject(Projectile);

	// Actors
	TArray<TWeakObjectPtr<AActor>> Actors;
	Actors.Add(Projectile);
	EffectContextHandle.AddActors(Actors);

	// Hit Result
	FHitResult HitResult;
	HitResult.Location = ProjectileTargetLocation;
	EffectContextHandle.AddHitResult(HitResult);
}

void UECMProjectileSpell::CreateAndApplySpecHandle(AECMProjectile* Projectile, const UAbilitySystemComponent* SourceASC, const FGameplayEffectContextHandle& EffectContextHandle)
{
	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);

	for(TTuple<FGameplayTag, FDamageRange>& Pair : DamageTypes)
	{
		const float ScaledMagnitudeMin = Pair.Value.DamageMin.GetValueAtLevel(GetAbilityLevel());
		const float ScaledMagnitudeMax = Pair.Value.DamageMax.GetValueAtLevel(GetAbilityLevel());
		const float Magnitude = FMath::RandRange(ScaledMagnitudeMin,ScaledMagnitudeMax);

		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, Magnitude);
	}
	
	Projectile->DamageEffectSpecHandle = SpecHandle;
}


