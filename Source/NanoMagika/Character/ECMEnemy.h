// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "ECMCharacterBase.h"
#include "NanoMagika/AbilitySystem/Data/ECMCharacterClassInfo.h"
#include "NanoMagika/UI/WidgetController/ECMWidgetController.h"
#include "ECMEnemy.generated.h"

class FOnAttributeChangedSignature;
class UWidgetComponent;

UCLASS()
class NANOMAGIKA_API AECMEnemy : public AECMCharacterBase
{
	GENERATED_BODY()

public:
	AECMEnemy();

	/** Combat Interface */
	FORCEINLINE virtual int32 GetPlayerLevel() override { return Level; }

	// Hit React // TODO Move to base class, we shoudl all react
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);;
	UPROPERTY(BlueprintReadOnly, Category="User|Combat")
	bool bHitReacting = false;
	/** end Combat Interface */

	// Health Bar
	UPROPERTY(BlueprintAssignable, Category="User|Health")
	FOnAttributeChangedSignature OnHealthChange;
	UPROPERTY(BlueprintAssignable, Category="User|Health")
	FOnAttributeChangedSignature OnMaxHealthChange;
	
protected:
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
	
	// TODO move secondary attribute
	UPROPERTY(BlueprintReadOnly, Category="User|Character Class Defaults")
	float DefaultWalkingSpeed = 350.f;
	
	// TODO move to Character Class Info
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="User|UI")
	TObjectPtr<UWidgetComponent> HealthBar;
	
};
