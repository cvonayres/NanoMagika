// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "ECMPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32 /* Stat Valve */)

class UAttributeSet;
class UAbilitySystemComponent;
class UECMLevelUpInformation;

UCLASS()
class NANOMAGIKA_API AECMPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AECMPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	/** Getters for Attribute System */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}

	/** Stat Getters */
	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	FORCEINLINE int32 GetPlayerXP() const { return XP; }
	FORCEINLINE int32 GetPlayerAttributePoints() const { return AttributePoints; }
	FORCEINLINE int32 GetPlayerAbilityPoints() const { return AbilityPoints; }

	/** Stat Add To */
	void AddToLevel(int32 InLevel);
	void AddToXP(int32 InXP);
	void AddToAttributePoints(int32 InAttributePoints);
	void AddToAbilityPoints(int32 InAbilityPoints);

	/** Stat Set To */
	void SetLevel(int32 InLevel);
	void SetXP(int32 InXP);
	void SetAttributePoints(int32 InAttributePoints);
	void SetAbilityPoints(int32 InAbilityPoints);

	/** Stat Delegates */
	FOnPlayerStatChanged OnLevelChangedDelegate;
	FOnPlayerStatChanged OnXPChangedDelegate;
	FOnPlayerStatChanged OnAttributePointsChangedDelegate;
	FOnPlayerStatChanged OnAbilityPointsChangedDelegate;

	/** Player Level Up Info */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UECMLevelUpInformation> LevelUpInfo;
	
protected: 
	/** Pointer for Ability System Component & Attribute Set */
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	UAttributeSet* AttributeSet;

private:
	/** Stat Parameters */
	UPROPERTY(VisibleAnywhere, Category="Character Class Defaults", ReplicatedUsing=OnRep_Level)
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, Category="Character Class Defaults", ReplicatedUsing=OnRep_XP)
	int32 XP = 0;

	UPROPERTY(VisibleAnywhere, Category="Character Class Defaults", ReplicatedUsing=OnRep_AttributePoints)
	int32 AttributePoints = 0;

	UPROPERTY(VisibleAnywhere, Category="Character Class Defaults", ReplicatedUsing=OnRep_AbilityPoints)
	int32 AbilityPoints = 0;
	/* Stat Parameters **/

	/** Stat OnRep Notifiers */
	UFUNCTION()
	void OnRep_Level(int32 oldLevel);
	
	UFUNCTION()
	void OnRep_XP(int32 oldXP);

	UFUNCTION()
	void OnRep_AttributePoints(int32 oldAttPoints);
	
	UFUNCTION()
	void OnRep_AbilityPoints(int32 oldAbilityPoints);
	/* Stat OnRep Notifiers **/
};
