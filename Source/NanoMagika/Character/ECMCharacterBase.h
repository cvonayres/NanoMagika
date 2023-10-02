// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "NanoMagika/Interaction/ECMCombatInterface.h"
#include "NanoMagika/Interaction/ECMHightlightInterface.h"
#include "ECMCharacterBase.generated.h"

class UECMAbilitySystemComponent;
class UGameplayAbility;
struct FGameplayTag;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class NANOMAGIKA_API AECMCharacterBase : public ACharacter, public IECMHightlightInterface, public IAbilitySystemInterface, public IECMCombatInterface
{
	GENERATED_BODY()

public:
	AECMCharacterBase();
	
	/** Hightlight Interface */
	virtual void HighlightActor() override;
	virtual void UnHighlighActor() override;
	/** end Hightlight Interface */

	/** Ability System Interface */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent;}
	bool SetAbilitySystemComponent(TObjectPtr<UAbilitySystemComponent> ASCIn) { AbilitySystemComponent = ASCIn; return true; }

	UAttributeSet* GetAttributeSet() const {return AttributeSet;}
	bool SetAttributeSet(TObjectPtr<UAttributeSet> ASIn) { AttributeSet = ASIn; return true; }

	UECMAbilitySystemComponent* GetECMASC() const;
	/** end Ability System Interface */
	
	/** Combat Interface */
	
	/** end Combat Interface */
	
	protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	
	// Default Character Attributes
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="User|Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="User|Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="User|Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	// Default Character Abilities
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="User|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> DefaultCharacterAbilities;

	// Default Character Gameplay Tags
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="User|GameplayTags")
	FGameplayTagContainer DefaultCharacterTags;

	// Initiate Ability System [overridden in child classes]
	virtual void InitializeCharacter();
	
	// Sets ActorInfo for Ability System & binds applied effects
	void InitAbilityActorInfo();

	// Sets Default Attributes, Abilities and GameplayTags
	void InitDefaultAttributes() const;
	void InitDefaultAbilities() const;
	void InitDefaultGameplayTags() const;

	// Sets Gameplay Effect to Self
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect>  GameplayEffectClass, float Level) const;

private:
	// Ability System and Attribute Set Pointer
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UECMAbilitySystemComponent> ECMAbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
