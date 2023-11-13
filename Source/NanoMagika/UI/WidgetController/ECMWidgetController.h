// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "ECMWidgetController.generated.h"

class UECMAbilityInformation;
struct FGameplayAttribute;
struct FGameplayTag;
class UECMAttributeInformation;
class UAttributeSet;
class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSigniture, const FECMAttributeInfo&, Info);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValve);

#define DECLARE_ATTRIBUTE_BINDING(CATEGORY, ATTRIBUTE) \
UPROPERTY(BlueprintAssignable, Category = CATEGORY) \
FOnAttributeChangedSignature On##ATTRIBUTE##Changed;

// Param strut
USTRUCT(BlueprintType)
struct FWidgetControllerParam
{
	GENERATED_BODY()
	FWidgetControllerParam() {}
	FWidgetControllerParam(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, TObjectPtr<UAttributeSet> AS)
	: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet;
};

UCLASS()
class NANOMAGIKA_API UECMWidgetController : public UObject
{
	GENERATED_BODY()

public:
	UECMWidgetController();

	// Overridden Functions
	UFUNCTION(BlueprintCallable)
	virtual void BindCallbacksToDependencies();
	virtual void BroadcastInitialValues();

	// Delegates for binding
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FAttributeInfoSigniture AttributeInfoDelegate;

	// Called from ECM Character Player
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParam(const FWidgetControllerParam WCParams);

protected:
	// Widget controller pointer to key handlers
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WidgetData")
	TObjectPtr<UECMAttributeInformation> AttributeInfo;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WidgetData")
	TObjectPtr<UECMAbilityInformation> AbilityInfo;
	
	void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;
};
