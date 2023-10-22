// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayCueInterface.h"
#include "GameplayTagAssetInterface.h"
#include "NanoMagika/Interaction/ECMCombatInterface.h"
#include "ECMCharacterBase.generated.h"

class UECMAttributeSet;
struct FGameplayTag;
class UECMAbilitySystemComponent;
class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;

// TODO reorganise character with three init, init_all [health bar on enemy, register asset, init_Server [ability system, etc], init_LocalControlled [HMI, Camera]

UCLASS(Abstract)
class NANOMAGIKA_API AECMCharacterBase : public ACharacter, public IAbilitySystemInterface, public IECMCombatInterface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	AECMCharacterBase();
	
	/** Ability System Interface */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	bool SetAbilitySystemComponent(TObjectPtr<UAbilitySystemComponent> ASCIn) { AbilitySystemComponent = ASCIn; return true; }

	UAttributeSet* GetAttributeSet() const {return AttributeSet;}
	bool SetAttributeSet(TObjectPtr<UAttributeSet> ASIn) { AttributeSet = ASIn; return true; }

	UECMAbilitySystemComponent* GetECMASC() const;
	/** end Ability System Interface */
	
	/** Combat Interface */
	virtual  FVector GetCombatSocketLocation() override;
	virtual UAnimMontage* GetHitReactMontage_Implementation() override { return HitReactMontage; }

	virtual void Die() override;
	
	/** end Combat Interface */

	/** Gameplay Tag Interface */
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;
	virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
	virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
	/** end Gameplay Tag Interface */

	
	virtual void PreInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath();
	
protected:

	TObjectPtr<USkeletalMeshComponent> GetCharacterMesh() const { return GetMesh(); }
	TObjectPtr<USkeletalMeshComponent> GetWeapon() const { return Weapon; }
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketName;
	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage* HitReactMontage;

	// Initiate Ability System [overridden in child classes]
	void InitializeAbilityActorInfo();
	virtual void InitializeCharacter();
	virtual void InitDefaultAttributes() { };
	virtual void InitDefaultAbilities() { };
	virtual void InitDefaultGameplayTags() { };

	// Sets Gameplay Effect to Self
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect>  GameplayEffectClass, float Level) const;

	// Ability System and Attribute Set Pointer
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UECMAbilitySystemComponent> ECMAbilitySystemComponent;
	UPROPERTY()
	UAttributeSet* AttributeSet;

	/* Dissolve Effects */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;

	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance, UMaterialInstanceDynamic* WeaponDynamicMaterialInstance);

};
