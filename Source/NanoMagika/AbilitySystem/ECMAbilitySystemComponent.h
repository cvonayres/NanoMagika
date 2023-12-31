// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ECMAbilitySystemComponent.generated.h"

class UECMGameplayAbility;
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssestTags, const FGameplayTagContainer& /*AssetTags*/)
DECLARE_MULTICAST_DELEGATE_OneParam(FAbiltiesGiven, UECMAbilitySystemComponent* /*AbilitySystemComponent*/)
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec)


UCLASS()
class NANOMAGIKA_API UECMAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Multicase Delegates
	FEffectAssestTags EffectAssetTagsDelegate;
	FAbiltiesGiven AbilitiesGivenDelegate;
	
	// Bind on EffectsApplied
	void BindEffectApplied();

	// Add Gameplay Effect
	void AddGameplayEffect(const TSubclassOf<UGameplayEffect>& Effect, float Level);
	
	// Add Gameplay Abilities
	void AddGameplayAbilities(const TArray<TSubclassOf<UECMGameplayAbility>>&  Abilities);
	bool bStartupAbiltiesGiven = false;
	
	// Add Gameplay Tags
	void  AddGameplayTags(const TArray<FGameplayTag>& Tags);
	
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void ForEachAbilitiy(const FForEachAbility& Delegate);

	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);

protected:

	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle) const;

	virtual void OnRep_ActivateAbilities() override;


};
