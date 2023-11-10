// Copyright Electronic CAD Monkey [ECM]

#include "ECMMeleeAttack.h"
#include "NanoMagika/ECMGameplayLibrary.h"
#include "NanoMagika/Interaction/ECMCombatInterface.h"
#include "NanoMagika/Interaction/ECMEnemyInterface.h"

void UECMMeleeAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UECMMeleeAttack::DamageActorsInRadius(const bool bDebug)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if(!bIsServer) return;
	
	if (OwningActor == nullptr || !OwningActor->Implements<UECMEnemyInterface>() || !OwningActor->Implements<UECMCombatInterface>() ) return;

	const int32 AttackRadius = IECMEnemyInterface::Execute_GetAttackRadius(OwningActor);
	const FVector AttackLocation = IECMCombatInterface::Execute_GetCombatSocketLocation(OwningActor, MontageTag);

	TArray<AActor*> ActorsInRadius;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.AddUnique(OwningActor);
	UECMGameplayLibrary::GetLivePlayersWithinRadius(OwningActor, ActorsInRadius, ActorsToIgnore, AttackRadius, AttackLocation);

	for (const AActor* ActorInRadius : ActorsInRadius)
	{
		CauseDamage();
		if(bDebug)
		{
			FString Name = ActorInRadius->GetName();
			UE_LOG(LogTemp, Warning, TEXT("Actor being damaged is: %s"), *Name);
		}
	}

	if (bDebug && ActorsInRadius.Num() > 0)
	{
		DrawDebugSphere(GetWorld(), AttackLocation, AttackRadius, 12, FColor::Red, false, 3);
	}
}
