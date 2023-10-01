// Copyright Electronic CAD Monkey [ECM]

#include "ECMEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NanoMagika/Character/ECMCharacter.h"

// Sets default values
AECMEffectActor::AECMEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot =CreateDefaultSubobject<USceneComponent>("SceneRoot"); 
	SetRootComponent(SceneRoot);
}

// Applies gameplay effect on Overlap Begin - Called by BP
void AECMEffectActor::OnOverlap(AActor* TargetActor)
{
	// Apply Gameplay effect on BeginOverlap
	if(InstanceEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		if(InstantGameplayEffectClass)
		{
			ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
		}
		else
		{
			ErrorMessage();
		}
	}
	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		if(DurationGameplayEffectClass)
		{
			ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
		}
		else
		{
			ErrorMessage();
		}
	}
	if(InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		if(InfiniteGameplayEffectClass)
		{
			ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
		}
		else
		{
			ErrorMessage();
		}
	}
	if(PeriodicEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		if(PeriodicGameplayEffectClass)
		{
			ApplyEffectToTarget(TargetActor, PeriodicGameplayEffectClass);
		}
		else
		{
			ErrorMessage();
		}
	}

	// Destroy Actor if policy is set on BeginOverlap
	if(DestroyPolicy == EDestroyPolicy::ApplyOnOverlap)
	{
		Destroy();
	}
}

// Applies gameplay effect on Overlap End - Called by BP
void AECMEffectActor::OnEndOverlap(AActor* TargetActor)
{
	// Apply Gameplay effect on EndOverlap
	if(InstanceEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		if(InstantGameplayEffectClass)
		{
			ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
		}
		else
		{
			ErrorMessage();
		}
	}
	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		if(DurationGameplayEffectClass)
		{
			ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
		}
		else
		{
			ErrorMessage();
		}
	}
	if(InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		if(InfiniteGameplayEffectClass)
		{
			ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
		}
		else
		{
			ErrorMessage();
		}
	}
	if(PeriodicEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		if(PeriodicGameplayEffectClass)
		{
			ApplyEffectToTarget(TargetActor, PeriodicGameplayEffectClass);
		}
		else
		{
			ErrorMessage();
		}
	}

	// Remove Active Gameplay effect for infinite effects with a remove policy of on EndOverlap
	if(InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		//Get Target Ability System Component
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if(!IsValid(TargetASC)) return;

		// Remove Active Ability and add to map for cleanup 
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair  : ActiveEffectHandles)
		{
			if (TargetASC == HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				HandlesToRemove.Add(HandlePair.Key);
			} 
		}

		// Remove handle of removed active gameplay effect
		for(FActiveGameplayEffectHandle& Handle : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);	
		}
	}

	// Destroy Actor if policy is set on EndOverlap
	if(DestroyPolicy == EDestroyPolicy::ApplyOnEndOverlap)
	{
		Destroy();
	}
}

// Applies gameplay effect to target
void AECMEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	// Gets ability system component
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if(!TargetASC) return;
	
	// Check if gameplay is valid and calls apply effect function.
	checkf(GameplayEffectClass, TEXT("Gameplay Effect not set"));
	ApplyEffect(TargetASC, GameplayEffectClass);
}
void AECMEffectActor::ApplyEffect(UAbilitySystemComponent* TargetASC, TSubclassOf<UGameplayEffect> GameplayEffectClass) 
{
	// Create Effect Spec Handle
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);

	// Apply gameplay effect to Self
	const FActiveGameplayEffectHandle ActiveEffectHandle =  TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	// Adds a reference to map if gameplay effect is infinite and has RemoveOnEndOverlap set.
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if(bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}	
}

void AECMEffectActor::ErrorMessage() const
{
	const FString Name = this->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Gameplay Effect Not Set in target: %s"), *Name);
}
