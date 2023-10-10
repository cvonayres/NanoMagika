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
	/** end Combat Interface */

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChange;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChange;
	
protected:
	virtual void BeginPlay() override;
	
	virtual void InitializeCharacter() override;

	void InitHealthBar();
	virtual void InitDefaultAttributes() const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Melee;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
	int32 Level = 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	TObjectPtr<UWidgetComponent> HealthBar;
	
};
