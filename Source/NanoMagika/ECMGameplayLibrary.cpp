// Copyright Electronic CAD Monkey [ECM]

#include "ECMGameplayLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "ECMGameplayTags.h"
#include "Interaction/ECMCombatInterface.h"

void UECMGameplayLibrary::GetLivePlayersWithinRadius(const UObject* WorldContextObject,	TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius,	const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	// query scene to see what we hit
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		TArray<FOverlapResult> Overlaps;
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);

		for (FOverlapResult& Overlap : Overlaps)
		{
			if (AActor* Actor = Overlap.GetActor(); Actor->Implements<UECMCombatInterface>() && !IECMCombatInterface::Execute_IsDead(Actor) )
			{
				OutOverlappingActors.AddUnique(Actor);
			}
		}
	}
}

bool UECMGameplayLibrary::IsNotFriend(AActor* FirstActor, AActor* SecondActor)
{
	if (!FirstActor || !SecondActor) { return false; }

	const FGameplayTag PlayerTag = FECMGameplayTags::Get().Character_Type_Player;
	const FGameplayTag EnemyTag = FECMGameplayTags::Get().Character_Type_Enemy;

	const UAbilitySystemComponent* FirstASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(FirstActor);
	const UAbilitySystemComponent* SecondASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SecondActor);

	if (!FirstASC || !SecondASC) { return false; }

	const bool FirstActorIsFriendly = FirstASC->HasMatchingGameplayTag(PlayerTag);
	const bool FirstActorIsEnemy = FirstASC->HasMatchingGameplayTag(EnemyTag);
	const bool SecondActorIsFriendly = SecondASC->HasMatchingGameplayTag(PlayerTag);
	const bool SecondActorIsEnemy = SecondASC->HasMatchingGameplayTag(EnemyTag);

	// Actors are not friends if one is friendly and the other is an enemy
	return (FirstActorIsFriendly && SecondActorIsEnemy) || (FirstActorIsEnemy && SecondActorIsFriendly);
}
