// Copyright Electronic CAD Monkey [ECM]

#include "ECMMMC_AttributeBase.h"
#include "NanoMagika/Interaction/ECMCombatInterface.h"

// Private function to set the attribute to be captured
void UECMMMC_AttributeBase::PrepData(const TArray<FGameplayAttribute>& AttributesOut)
{
	checkf((AttributeDefs.Max() >= AttributesOut.Max()),TEXT("More attributes specified for MMC than defined in ECMMMC_AttributeBase"));
	
	for (int32 i = 0; i < AttributesOut.Num(); i++)
	{
		FGameplayEffectAttributeCaptureDefinition& CurrentDef = AttributeDefs[i]; // Assuming AttributeDefs is an array
		CurrentDef.AttributeToCapture = AttributesOut[i];
		CurrentDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
		CurrentDef.bSnapshot = false;
		RelevantAttributesToCapture.Add(CurrentDef);
	}
}

void UECMMMC_AttributeBase::GatherData(const FGameplayEffectSpec Spec, TArray<float>& AttributeValuesOut,
	FDataExt& DataExtOut) const
{
	checkf((AttributeDefs.Max() >= AttributeValuesOut.Max()),TEXT("More attributes values specified for MMC than defined in ECMMMC_AttributeBase"));

	// Get get source and target tags for Evaluation Parameters
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.SourceTags = SourceTags;
	EvaluationParams.TargetTags = TargetTags;

	// Populate DataExt
	IECMCombatInterface* CombatInterface = Cast<IECMCombatInterface>(Spec.GetContext().GetSourceObject());
	checkf(CombatInterface, TEXT("CombatInterface Not set for Effect Spec Object"))
	DataExtOut.PlayerLevel = CombatInterface->GetPlayerLevel();

	// Cycle through all attributes and fill in appropriate Attribute definitions.
	for (int32 i = 0; i < AttributeValuesOut.Num(); i++)
	{
		GetCapturedAttributeMagnitude(AttributeDefs[i], Spec, EvaluationParams, AttributeValuesOut[i]);
		AttributeValuesOut[i] = FMath::Max<float>(AttributeValuesOut[i], 0);
	}
}
