// Copyright Electronic CAD Monkey [ECM]

#include "ECMAbilitySystemComponent.h"
#include "NanoMagika/ECMGameplayTags.h"

// Bind Effect Applied to callback on ASC Effect Applied To Self.
void UECMAbilitySystemComponent::BindEffectApplied()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UECMAbilitySystemComponent::EffectApplied);
}

// Grant Ability
void UECMAbilitySystemComponent::AddGameplayAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{
	for(const TSubclassOf<UGameplayAbility> AbilityClass : Abilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		// GiveAbility(AbilitySpec);
		GiveAbilityAndActivateOnce(AbilitySpec);
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
void UECMAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,
											   FActiveGameplayEffectHandle ActiveEffectHandle) const
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}
