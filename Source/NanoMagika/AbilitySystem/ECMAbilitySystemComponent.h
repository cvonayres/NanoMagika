// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ECMAbilitySystemComponent.generated.h"

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


	// Add Gameplay Abilities
	void AddGameplayAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities);

	// Add Gameplay Tags
	void  AddGameplayTags(const FGameplayTagContainer& Tags);
	
	void EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle) const;

protected:

private:

};
