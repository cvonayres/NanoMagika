// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "ECMCharacterBase.h"
#include "NanoMagika/AbilitySystem/Data/ECMCharacterClassInfo.h"
#include "NanoMagika/UI/WidgetController/ECMWidgetController.h"
#include "ECMEnemy.generated.h"

class FOnAttributeChangedSignature;

UCLASS()
class NANOMAGIKA_API AECMEnemy : public AECMCharacterBase
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
	/** end Combat Interface */

	// Health Bar
	UPROPERTY(BlueprintAssignable, Category="User|Health")
	FOnAttributeChangedSignature OnHealthChange;
	UPROPERTY(BlueprintAssignable, Category="User|Health")
	FOnAttributeChangedSignature OnMaxHealthChange;
	
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

	// Health Bar
	void InitHealthBar();
	
	// TODO move secondary attribute make speed dependant of stats
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="User|Character Class Defaults")
	float DefaultWalkingSpeed = 200.f;
	
	// TODO move to Character Class Info
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="User|Character Class Defaults")
	float LifeSpan = 5.f;
	
	// TODO move to Character Class Info
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="User|UI")
	TObjectPtr<class UWidgetComponent> HealthBar;

	UPROPERTY()
	class UBlackboardComponent* BlackboardComponentRef;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="User|AI")
	TObjectPtr<class UBehaviorTree> BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="User|AI")
	TObjectPtr<class AECMAIController> AIController;

	// void SetBBKey_HitReacting(bool Valve) const;
};
