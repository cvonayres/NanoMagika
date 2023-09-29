// Copyright Electronic CAD Monkey [ECM]

#include "ECMMMC_AttributeBase.h"
#include "NanoMagika/Interaction/ECMCombatInterface.h"

// Private function to set the attribute to be captured
void UECMMMC_AttributeBase::PrepData(const FGameplayAttribute& Attribute)
{
	AttributeDef.AttributeToCapture = Attribute;
	AttributeDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	AttributeDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(AttributeDef);
}

// Private function to gather the attribute and the player level
void UECMMMC_AttributeBase::GatherData(const FGameplayEffectSpec& Spec, float& AttributeValveOut, int32& PlayerLevelOut) const
{
	// Gather tags form source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.SourceTags = SourceTags;
	EvaluationParams.TargetTags = TargetTags;

	// Get Primary attribute to be used, clamp to positive valve
	GetCapturedAttributeMagnitude(AttributeDef, Spec, EvaluationParams, AttributeValveOut);
	AttributeValveOut = FMath::Max<float>(AttributeValveOut,0) ;

	// Get Player Level
	IECMCombatInterface* CombatInterface = 	Cast<IECMCombatInterface>(Spec.GetContext().GetSourceObject());
	checkf(CombatInterface, TEXT("CombatInterface Not set for Effect Spec Object"))
	PlayerLevelOut = CombatInterface->GetPlayerLevel();
}
