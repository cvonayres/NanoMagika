// Copyright Electronic CAD Monkey [ECM]

#include "ECMAbilitySystemComponent.h"

#include "Abilities/ECMGameplayAbility.h"
#include "NanoMagika/ECMGameplayTags.h"
#include "NanoMagika/Character/ECMCharacter.h"

// Bind Effect Applied to callback on ASC Effect Applied To Self.
void UECMAbilitySystemComponent::BindEffectApplied()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UECMAbilitySystemComponent::ClientEffectApplied);
}

// Adds GameplayEffect Tags loosely
void UECMAbilitySystemComponent::AddGameplayEffect(const TSubclassOf<UGameplayEffect>& Effect, const float Level)
{
	FGameplayEffectContextHandle ContextHandle = MakeEffectContext();
	ContextHandle.AddSourceObject(GetAvatarActor());
	const FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(Effect, Level, ContextHandle) ;
	ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void UECMAbilitySystemComponent::AddGameplayAbilities(const TArray<TSubclassOf<UECMGameplayAbility>>& Abilities)
{
	if (Abilities.IsEmpty()) return;

	for (const TSubclassOf<UECMGameplayAbility>& AbilityClass : Abilities)
	{
		// Create an instance of the ability to access its properties
		const UECMGameplayAbility* AbilityInstance = AbilityClass.GetDefaultObject();
		const int32 Level = AbilityInstance->AbilityLevel; // Get the Ability level
		const bool bBindToInput = AbilityInstance->BindToInputTag; // Check if we should bind the ability to an input

		// Create a new FGameplayAbilitySpec with the AbilityClass and Level
		FGameplayAbilitySpec AbilitySpec(AbilityClass, Level);

		// If bBindToInput is true, we want to react to enhanced input
		if (bBindToInput)
		{
			FGameplayTag BoundInputTag = AbilityInstance->InputTag; // Get the input tag

			// Check if the input tag is valid and matches the desired input tag
			if (BoundInputTag.IsValid() && BoundInputTag.MatchesTag(FGameplayTag::RequestGameplayTag("Input")))
			{
				// Add the input tag to the DynamicAbilityTags of the AbilitySpec
				AbilitySpec.DynamicAbilityTags.AddTag(BoundInputTag);
			}
		}

		// Give the ability to the component
		GiveAbility(AbilitySpec);
	}
}

// Adds Gameplay Tags loosely
void UECMAbilitySystemComponent::AddGameplayTags(const TArray<FGameplayTag>& Tags)
{
	if(Tags.IsEmpty()) return;

	for (FGameplayTag Tag : Tags)
	{
		AddLooseGameplayTag(Tag);
	}
}

// Broadcast on EffectApplied
void UECMAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,
											   FActiveGameplayEffectHandle ActiveEffectHandle) const
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}

// Check if valid, then get all activatable abilities, for each check against tag and if match and not active try to activate.
void UECMAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec AbilitySpec : GetActivatableAbilities())
	{
		if(AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

// Check if valid, then get all activatable abilities, for each check against tag and if match tell its being released.
void UECMAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec AbilitySpec : GetActivatableAbilities())
	{
		if(AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}
