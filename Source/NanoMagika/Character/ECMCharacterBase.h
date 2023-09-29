// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "NanoMagika/Interaction/ECMCombatInterface.h"
#include "NanoMagika/Interaction/ECMHightlightInterface.h"
#include "ECMCharacterBase.generated.h"

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
	virtual void UnHightlighActor() override;
	/** end Hightlight Interface */

	/** Ability System Interface */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}
	/** end Ability System Interface */
	
	/** Combat Interface */
	
	/** end Combat Interface */

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	
	// Points for Attribute System
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	// Optional BP function called on highlighed
	UFUNCTION(BlueprintImplementableEvent)
	void Highlighted(bool State);

	virtual void InitAbilityActorInfo();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	void InitDefaultAttributes() const;
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect>  GameplayEffectClass, float Level) const;

private:
	
};
