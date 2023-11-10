// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "ECMCharacterBase.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemLibrary.h"
#include "NanoMagika/AbilitySystem/Data/ECMCharacterClassInfo.h"
#include "NanoMagika/AbilitySystem/Data/ECMEnemySpecInfo.h"
#include "NanoMagika/Interaction/ECMEnemyInterface.h"
#include "NanoMagika/UI/WidgetController/ECMWidgetController.h"
#include "ECMEnemy.generated.h"

class FOnAttributeChangedSignature;

UCLASS()
class NANOMAGIKA_API AECMEnemy : public AECMCharacterBase, public IECMEnemyInterface
{
	GENERATED_BODY()

public:
	AECMEnemy();

	virtual void PossessedBy(AController* NewController) override;
	
	/** Combat Interface */
	FORCEINLINE virtual int32 GetPlayerLevel() override { return Level; }

	// Hit React // TODO Move to base class, we should all react
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);;
	UPROPERTY(BlueprintReadOnly, Category="User|Combat")
	bool bHitReacting = false;

	virtual void Die() override;

	virtual AActor* GetCombatTarget_Implementation() override { return CombatTarget; }
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override { CombatTarget = InCombatTarget; }
	/** end Combat Interface */

	/** Enemy Interface */
	virtual FGameplayTag GetEnemyTag_Implementation() override {  return EnemyTag; }

	virtual UECMCharacterClassInfo* GetClassInfo_Implementation() override {  return ClassInfo ; }
	virtual UECMEnemySpecInfo* GetClassSpec_Implementation() override {  return ClassSpec ; }
	
	virtual float GetAttackRadius_Implementation() override { return ClassSpec ? ClassSpec->AttackRadius : 0.f; }

	virtual TMap<FGameplayTag, UAnimMontage*> GetAttackMontages_Implementation() override { return ClassSpec ? ClassSpec->AttackMontages : TMap<FGameplayTag, UAnimMontage*>(); }

	virtual UAnimMontage* GetHitReactMontage_Implementation() override { return ClassSpec ? ClassSpec->HitMontage : nullptr; }
	/** end Enemy Interface */

	// Health Bar
	UPROPERTY(BlueprintAssignable, Category="User|Health")
	FOnAttributeChangedSignature OnHealthChange;
	UPROPERTY(BlueprintAssignable, Category="User|Health")
	FOnAttributeChangedSignature OnMaxHealthChange;

	UPROPERTY(BlueprintReadWrite, Category="Combat")
	TObjectPtr<AActor> CombatTarget;
	
protected:
	// This is the default Tag that is used to get the Data asset from the global library, not part of GAS
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="User|Character Class Defaults")
	FGameplayTag EnemyTag = FGameplayTag();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="User|Character Class Defaults")
	int32 Level = 1;

	virtual void BeginPlay() override;
	
	virtual void InitializeCharacter() override;
	virtual void InitDefaultAttributes() override;
	virtual void InitDefaultAbilities() override;
	virtual void InitDefaultGameplayTags() override;

	void InitHealthBar();

	UPROPERTY()
	UECMCharacterClassInfo* ClassInfo = nullptr;

	UPROPERTY()
	UECMEnemySpecInfo* ClassSpec = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CommonClassDefaults|Healthbar")
	TObjectPtr<class UWidgetComponent> HealthBar;
	
	UPROPERTY()
	class UBlackboardComponent* BlackboardComponentRef;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="User|AI")
	TObjectPtr<class UBehaviorTree> BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="User|AI")
	TObjectPtr<class AECMAIController> AIController;
};
