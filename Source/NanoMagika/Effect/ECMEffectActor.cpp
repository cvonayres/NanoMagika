// Copyright Electronic CAD Monkey [ECM]

#include "ECMEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemLibrary.h"

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
	const ACharacter* TestCharacter = Cast<ACharacter>(TargetActor);
	if ( TestCharacter == nullptr) return ;
	
	// Check if any required tag is present on the target actor
	for (const FGameplayTag& Tag : RequiredTagOnActor)
	{
		if (UECMAbilitySystemLibrary::ActorASCContainsTag(TargetActor, Tag))
		{
			auto HandleEffectApplication = [this, &TargetActor](EEffectApplicationPolicy Policy, TSubclassOf<UGameplayEffect> EffectClass)
			{
				if (Policy == EEffectApplicationPolicy::ApplyOnOverlap)
				{
					if (EffectClass) ApplyEffectToTarget(TargetActor, EffectClass);
					else ErrorMessage();
				}
			};

			// Apply Gameplay effect on BeginOverlap
			HandleEffectApplication(InstanceEffectApplicationPolicy, InstantGameplayEffectClass);
			HandleEffectApplication(DurationEffectApplicationPolicy, DurationGameplayEffectClass);
			HandleEffectApplication(InfiniteEffectApplicationPolicy, InfiniteGameplayEffectClass);
			HandleEffectApplication(PeriodicEffectApplicationPolicy, PeriodicGameplayEffectClass);

			if (DestroyPolicy == EDestroyPolicy::ApplyOnOverlap) Destroy();
			
			return; // Since we found a tag and processed it, exit function early
		}
	}
}

// Applies gameplay effect on Overlap End - Called by BP
void AECMEffectActor::OnEndOverlap(AActor* TargetActor)
{
	// Check if any required tag is present on the target actor
	for (const FGameplayTag& Tag : RequiredTagOnActor)
	{
		if (UECMAbilitySystemLibrary::ActorASCContainsTag(TargetActor, Tag))
		{
			auto HandleEffectApplication = [this, &TargetActor](EEffectApplicationPolicy Policy, TSubclassOf<UGameplayEffect> EffectClass)
			{
				if (Policy == EEffectApplicationPolicy::ApplyOnEndOverlap)
				{
					if (EffectClass) ApplyEffectToTarget(TargetActor, EffectClass);
					else ErrorMessage();
				}
			};

			// Apply Gameplay effect on EndOverlap
			HandleEffectApplication(InstanceEffectApplicationPolicy, InstantGameplayEffectClass);
			HandleEffectApplication(DurationEffectApplicationPolicy, DurationGameplayEffectClass);
			HandleEffectApplication(InfiniteEffectApplicationPolicy, InfiniteGameplayEffectClass);
			HandleEffectApplication(PeriodicEffectApplicationPolicy, PeriodicGameplayEffectClass);

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
			if(DestroyPolicy == EDestroyPolicy::ApplyOnEndOverlap) Destroy();
			
			return; // Since we found a tag and processed it, exit function early
		}
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
