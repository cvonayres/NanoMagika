// Copyright Electronic CAD Monkey [ECM]

#include "ECMMMC_VMCapacity.h"
#include "NanoMagika/AbilitySystem/ECMAttributeSet.h"
#include "NanoMagika/Interaction/ECMCombatInterface.h"

UECMMMC_VMCapacity::UECMMMC_VMCapacity()
{
	PhysiqueDef.AttributeToCapture = UECMAttributeSet::GetPhysiqueAttribute();
	PhysiqueDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	PhysiqueDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(PhysiqueDef);
}

float UECMMMC_VMCapacity::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags form source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.SourceTags = SourceTags;
	EvaluationParams.TargetTags = TargetTags;

	// Get Primary attribute to be used, clamp to positive valve
	float Physique = 0.f;
	GetCapturedAttributeMagnitude(PhysiqueDef, Spec, EvaluationParams, Physique);
	Physique = FMath::Max<float>(Physique,0) ;

	// Get Player Level
	IECMCombatInterface* CombatInterface = 	Cast<IECMCombatInterface>(Spec.GetContext().GetSourceObject());
	checkf(CombatInterface, TEXT("CombatInterface Not set for Effect Spec Object"))
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return (BaseValve + (Physique * AttributeMultiplier)) * PlayerLevel ;	
}
