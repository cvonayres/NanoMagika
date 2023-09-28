// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "ECMWidgetController.h"
#include "GameplayTagContainer.h"
#include "ECMOverlayWidgetController.generated.h"

class UECMUserWidget;

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

struct FOnAttributeChangeData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValve);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);

#define DECLARE_ATTRIBUTE_BINDING(CATEGORY, ATTRIBUTE) \
UPROPERTY(BlueprintAssignable, Category = CATEGORY) \
FOnAttributeChangedSignature On##ATTRIBUTE##Changed;


UCLASS(BlueprintType, Blueprintable)
class NANOMAGIKA_API UECMOverlayWidgetController : public UECMWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	// Bindings
	UPROPERTY(BlueprintAssignable, Category="GAS|Vital Attributes")
	FOnAttributeChangedSignature OnVitalityMatrixChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Vital Attributes")
	FOnAttributeChangedSignature OnEnergeticEnduranceChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Vital Attributes")
	FOnAttributeChangedSignature OnArcaneReservoirChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Vital Attributes")
	FOnAttributeChangedSignature OnDefensiveSynchronyChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Vital Attributes")
	FOnAttributeChangedSignature OnBarrierMatrixChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Primary Attributes")
	FOnAttributeChangedSignature OnPhysiqueChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Primary Attributes")
	FOnAttributeChangedSignature OnAdaptivityChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Primary Attributes")
	FOnAttributeChangedSignature OnNeuralAgilityChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Primary Attributes")
	FOnAttributeChangedSignature OnEmpathicResonanceChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Primary Attributes")
	FOnAttributeChangedSignature OnEssenceControlChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Primary Attributes")
	FOnAttributeChangedSignature OnNanomancyChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnVMCapacityChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnVMRecoveryChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnEECapacityChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnEERecoveryChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnARCapacityChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnARRecoveryChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnKineticAbsorptionChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnNanoshieldThresholdChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnResonanceSyncQualityChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnResonanceAmplificationChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnEmpathicInfluenceChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnTechnologicalInterfaceChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnSignalStealthChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnReactionSpeedChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnDimensionalPocketCapacityChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|TertiaryAttributes")
	FOnAttributeChangedSignature OnLevelChanged;
	
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
