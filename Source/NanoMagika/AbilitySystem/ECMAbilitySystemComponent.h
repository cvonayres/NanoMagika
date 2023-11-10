// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ECMAbilitySystemComponent.generated.h"

class UECMGameplayAbility;
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssestTags, const FGameplayTagContainer& /*AssetTags*/)

UCLASS()
class NANOMAGIKA_API UECMAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	FEffectAssestTags GetTagContainer() { return EffectAssetTags; }
	FEffectAssestTags EffectAssetTags;
	
	// Bind on EffectsApplied
	void BindEffectApplied();

	// Add Gameplay Effect
	void AddGameplayEffect(const TSubclassOf<UGameplayEffect>& Effect, float Level);
	
	// Add Gameplay Abilities
	void AddGameplayAbilities(const TArray<TSubclassOf<UECMGameplayAbility>>&  Abilities);

	// Add Gameplay Tags
	void  AddGameplayTags(const TArray<FGameplayTag>& Tags);

	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle) const;

	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
};
