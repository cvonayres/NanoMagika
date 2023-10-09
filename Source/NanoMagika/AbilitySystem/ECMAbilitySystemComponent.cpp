// Copyright Electronic CAD Monkey [ECM]

#include "ECMAbilitySystemComponent.h"

#include "Abilities/ECMGameplayAbility.h"
#include "NanoMagika/ECMGameplayTags.h"

// Bind Effect Applied to callback on ASC Effect Applied To Self.
void UECMAbilitySystemComponent::BindEffectApplied()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UECMAbilitySystemComponent::ClientEffectApplied);
}

// Grant Ability
void UECMAbilitySystemComponent::AddGameplayAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartUpAbilities)
{
	for(const TSubclassOf<UGameplayAbility> AbilityClass : StartUpAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if(const UECMGameplayAbility* ECMAbility = Cast<UECMGameplayAbility>(AbilitySpec.Ability)) 
		{
			AbilitySpec.DynamicAbilityTags.AddTag(ECMAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}	
}

// Adds Gameplay Tags loosely
void UECMAbilitySystemComponent::AddGameplayTags(const FGameplayTagContainer& Tags)
{
	if(Tags.IsEmpty()) return;

	for (TArray<FGameplayTag> ArrayOfTags = Tags.GetGameplayTagArray(); FGameplayTag Tag : ArrayOfTags)
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
