// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "ECMCharacterBase.h"
#include "Abilities/GameplayAbility.h"
#include "ECMCharacter.generated.h"

class UECMGameplayAbility;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class NANOMAGIKA_API AECMCharacter : public AECMCharacterBase
{
	GENERATED_BODY()

public:
	AECMCharacter();
	
	// Server / Client Ready
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;

	virtual UAnimMontage* GetHitReactMontage_Implementation() override { return HitReactMontage; }

	/** end Combat Interface */

	void SetbUseControllerRotationPitch(bool Valve) { bUseControllerRotationPitch = Valve ; }
	void SetbUseControllerRotationRoll(bool Valve) { bUseControllerRotationRoll = Valve ; }
	void SetbUseControllerRotationYaw(bool Valve) { bUseControllerRotationYaw = Valve ; }
	
protected:
	// Init Ability System
	virtual void InitializeCharacter();
	virtual void InitDefaultAttributes() override;
	virtual void InitDefaultAbilities() override;
	virtual void InitDefaultGameplayTags() override;

	// Default Character Attributes
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="User|Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="User|Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="User|Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	// Default Character Abilities
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="User|Abilities")
	TArray<TSubclassOf<UECMGameplayAbility>> DefaultCharacterAbilities;
	
	// Default Character Gameplay Tags
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="User|GameplayTags")
	TArray<FGameplayTag> DefaultCharacterTags;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	UAnimMontage* HitReactMontage;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;
	
	// Controller and Player State Ref
	UPROPERTY()
	class AECMPlayerController* ControllerRef;
	UPROPERTY()
	class AECMPlayerState* PlayerStateRef;
	
	// Called when we have a valid player controller
	void InitPCM() const;
	void InitHUD() const;
};
