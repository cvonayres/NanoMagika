// Copyright Electronic CAD Monkey [ECM]

#include "ECMOverlayWidgetController.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemComponent.h"
#include "NanoMagika/AbilitySystem/ECMAttributeSet.h"

// Broadcast when Attribute change
void UECMOverlayWidgetController::BroadcastInitialValues()
{
	const UECMAttributeSet* ECMAttributeSet = CastChecked<UECMAttributeSet>(AttributeSet);

	OnVitalityMatrixChanged.Broadcast(ECMAttributeSet->GetVitalityMatrix());
	OnEnergeticEnduranceChanged.Broadcast(ECMAttributeSet->GetEnergeticEndurance());
	OnArcaneReservoirChanged.Broadcast(ECMAttributeSet->GetArcaneReservoir());
	OnDefensiveSynchronyChanged.Broadcast(ECMAttributeSet->GetDefensiveSynchrony());
	OnBarrierMatrixChanged.Broadcast(ECMAttributeSet->GetBarrierMatrix());

	OnPhysiqueChanged.Broadcast(ECMAttributeSet->GetPhysique());
	OnAdaptivityChanged.Broadcast(ECMAttributeSet->GetAdaptivity());
	OnNeuralAgilityChanged.Broadcast(ECMAttributeSet->GetNeuralAgility());
	OnEmpathicResonanceChanged.Broadcast(ECMAttributeSet->GetEmpathicResonance());
	OnEssenceControlChanged.Broadcast(ECMAttributeSet->GetEssenceControl());
	OnNanomancyChanged.Broadcast(ECMAttributeSet->GetNanomancy());

	OnVMCapacityChanged.Broadcast(ECMAttributeSet->GetVMCapacity());
	OnVMRecoveryChanged.Broadcast(ECMAttributeSet->GetVMRecovery());
	OnEECapacityChanged.Broadcast(ECMAttributeSet->GetEECapacity());
	OnEERecoveryChanged.Broadcast(ECMAttributeSet->GetEERecovery());
	OnARCapacityChanged.Broadcast(ECMAttributeSet->GetARCapacity());
	OnARRecoveryChanged.Broadcast(ECMAttributeSet->GetARRecovery());
	OnKineticAbsorptionChanged.Broadcast(ECMAttributeSet->GetKineticAbsorption());
	OnNanoshieldThresholdChanged.Broadcast(ECMAttributeSet->GetNanoshieldThreshold());
	OnResonanceSyncQualityChanged.Broadcast(ECMAttributeSet->GetResonanceSyncQuality());
	OnResonanceAmplificationChanged.Broadcast(ECMAttributeSet->GetResonanceAmplification());
	OnEmpathicInfluenceChanged.Broadcast(ECMAttributeSet->GetEmpathicInfluence());
	OnTechnologicalInterfaceChanged.Broadcast(ECMAttributeSet->GetTechnologicalInterface());
	OnSignalStealthChanged.Broadcast(ECMAttributeSet->GetSignalStealth());
	OnDimensionalPocketCapacityChanged.Broadcast(ECMAttributeSet->GetDimensionalPocketCapacity());
}

// Bind Listeners for Attribute change
void UECMOverlayWidgetController::BindCallbacksToDependencies()
{
	const UECMAttributeSet* ECMAttributeSet = CastChecked<UECMAttributeSet>(AttributeSet);
	
	// Bind vital attributes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetVitalityMatrixAttribute()).AddLambda(
		[this](const FOnAttributeChangeData &Data)	{ OnVitalityMatrixChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetEnergeticEnduranceAttribute()).AddLambda(
		[this](const FOnAttributeChangeData &Data)	{ OnEnergeticEnduranceChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetArcaneReservoirAttribute()).AddLambda(
	[this](const FOnAttributeChangeData &Data)	{ OnArcaneReservoirChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetDefensiveSynchronyAttribute()).AddLambda(
	[this](const FOnAttributeChangeData &Data)	{ OnDefensiveSynchronyChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetBarrierMatrixAttribute()).AddLambda(
	[this](const FOnAttributeChangeData &Data)	{ OnBarrierMatrixChanged.Broadcast(Data.NewValue);});

	// Bind primary attributes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetPhysiqueAttribute()).AddLambda(
		[this](const FOnAttributeChangeData &Data)	{ OnPhysiqueChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetAdaptivityAttribute()).AddLambda(
		[this](const FOnAttributeChangeData &Data)	{ OnAdaptivityChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetNeuralAgilityAttribute()).AddLambda(
	[this](const FOnAttributeChangeData &Data)	{ OnNeuralAgilityChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetEmpathicResonanceAttribute()).AddLambda(
	[this](const FOnAttributeChangeData &Data)	{ OnEmpathicResonanceChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetEssenceControlAttribute()).AddLambda(
	[this](const FOnAttributeChangeData &Data)	{ OnEssenceControlChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetNanomancyAttribute()).AddLambda(
	[this](const FOnAttributeChangeData &Data)	{ OnNanomancyChanged.Broadcast(Data.NewValue);});

	// Bind secondary attributes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetVMCapacityAttribute()).AddLambda(
		[this](const FOnAttributeChangeData &Data)	{ OnVMCapacityChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetVMRecoveryAttribute()).AddLambda(
		[this](const FOnAttributeChangeData &Data)	{ OnVMRecoveryChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetEECapacityAttribute()).AddLambda(
	[this](const FOnAttributeChangeData &Data)	{ OnEECapacityChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetEERecoveryAttribute()).AddLambda(
	[this](const FOnAttributeChangeData &Data)	{ OnEERecoveryChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetARCapacityAttribute()).AddLambda(
	[this](const FOnAttributeChangeData &Data)	{ OnARCapacityChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetARRecoveryAttribute()).AddLambda(
	[this](const FOnAttributeChangeData &Data)	{ OnARRecoveryChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetKineticAbsorptionAttribute()).AddLambda(
		[this](const FOnAttributeChangeData &Data)	{ OnKineticAbsorptionChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetNanoshieldThresholdAttribute()).AddLambda(
		[this](const FOnAttributeChangeData &Data)	{ OnNanoshieldThresholdChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetResonanceSyncQualityAttribute()).AddLambda(
	[this](const FOnAttributeChangeData &Data)	{ OnResonanceSyncQualityChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetResonanceAmplificationAttribute()).AddLambda(
	[this](const FOnAttributeChangeData &Data)	{ OnResonanceAmplificationChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetEmpathicInfluenceAttribute()).AddLambda(
	[this](const FOnAttributeChangeData &Data)	{ OnEmpathicInfluenceChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetTechnologicalInterfaceAttribute()).AddLambda(
	[this](const FOnAttributeChangeData &Data)	{ OnTechnologicalInterfaceChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetSignalStealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData &Data)	{ OnSignalStealthChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ECMAttributeSet->GetDimensionalPocketCapacityAttribute()).AddLambda(
	[this](const FOnAttributeChangeData &Data)	{ OnDimensionalPocketCapacityChanged.Broadcast(Data.NewValue);});

	// Bind Tertiary attributes
	
	// Bind Message Widget Row
	Cast<UECMAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
	[this](const FGameplayTagContainer& AssetTags)
		{
			for(const FGameplayTag& Tag : AssetTags)
			{
				// Only look for row from data table if tag has message
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if(Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		}
		);
}
