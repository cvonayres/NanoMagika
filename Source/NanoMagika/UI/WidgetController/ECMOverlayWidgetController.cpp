// Copyright Electronic CAD Monkey [ECM]

#include "ECMOverlayWidgetController.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemComponent.h"
#include "NanoMagika/AbilitySystem/Attributes/ECMAttributeSet.h"

// Broadcast when Attribute change
void UECMOverlayWidgetController::BroadcastInitialValues()
{
	const UECMAttributeSet* ECMAttributeSet = CastChecked<UECMAttributeSet>(AttributeSet);

	OnVitalityMatrixChangedDelegate.Broadcast(ECMAttributeSet->GetVitalityMatrix());
	OnVMCapacityChangedDelegate.Broadcast(ECMAttributeSet->GetVMCapacity());
	OnArcaneReservoirChangeDelegate.Broadcast(ECMAttributeSet->GetArcaneReservoir());
	OnARCapacityChangedDelegate.Broadcast(ECMAttributeSet->GetARCapacity());
}

// Bind Listeners for Attribute change
void UECMOverlayWidgetController::BindCallbacksToDependencies()
{
	const UECMAttributeSet* ECMAttributeSet = CastChecked<UECMAttributeSet>(AttributeSet);
	
	// Bind vital attributes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetVitalityMatrixAttribute()).AddLambda(
		[this](const FOnAttributeChangeData &Data)	{ OnVitalityMatrixChangedDelegate.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetVMCapacityAttribute()).AddLambda(
		[this](const FOnAttributeChangeData &Data)	{ OnVMCapacityChangedDelegate.Broadcast(Data.NewValue);});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetArcaneReservoirAttribute()).AddLambda(
	[this](const FOnAttributeChangeData &Data)	{ OnArcaneReservoirChangeDelegate.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetARCapacityAttribute()).AddLambda(
[this](const FOnAttributeChangeData &Data)	{ OnARCapacityChangedDelegate.Broadcast(Data.NewValue);});
	
	// Bind Message Widget Row
	Cast<UECMAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
	[this](const FGameplayTagContainer& AssetTags)
		{
			for(const FGameplayTag& Tag : AssetTags)
			{
				// Only look for row from data table if tag has message
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message.UI"));
				if(Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		}
		);
}
