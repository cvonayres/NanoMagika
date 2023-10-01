// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "ECMWidgetController.h"
#include "GameplayTagContainer.h"
#include "ECMOverlayWidgetController.generated.h"

class UECMUserWidget;

// To define table structure
USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UECMUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);

UCLASS(BlueprintType, Blueprintable)
class NANOMAGIKA_API UECMOverlayWidgetController : public UECMWidgetController
{
	GENERATED_BODY()

public:
	// Overridden Functions
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;
	
	// Delegates for binding
	UPROPERTY(BlueprintAssignable, Category="GAS|Vital Attributes")
	FOnAttributeChangedSignature OnVitalityMatrixChangedDelegate;
	UPROPERTY(BlueprintAssignable, Category="GAS|Vital Attributes")
	FOnAttributeChangedSignature OnVMCapacityChangedDelegate;
	UPROPERTY(BlueprintAssignable, Category="GAS|Vital Attributes")
	FOnAttributeChangedSignature OnArcaneReservoirChangeDelegate;
	UPROPERTY(BlueprintAssignable, Category="GAS|Vital Attributes")
	FOnAttributeChangedSignature OnARCapacityChangedDelegate;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Messages")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WidgetData")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
	
	template<typename T>
	static T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
};

template <typename T>
T* UECMOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
