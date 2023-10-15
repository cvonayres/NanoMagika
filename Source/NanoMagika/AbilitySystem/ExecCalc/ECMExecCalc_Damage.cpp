// Copyright Electronic CAD Monkey [ECM]

#include "ECMExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "NanoMagika/ECMGameplayTags.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemLibrary.h"
#include "NanoMagika/AbilitySystem/Attributes/ECMAttributeSet.h"
#include "NanoMagika/Interaction/ECMCombatInterface.h"

struct ECMDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AdaptiveReflex);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResonanceSyncQuality);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResonanceAmplification);

	ECMDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UECMAttributeSet, AdaptiveReflex, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UECMAttributeSet, ResonanceSyncQuality, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UECMAttributeSet, ResonanceAmplification, Source, false);
	}
};

static const ECMDamageStatics& DamageStatics()
{
	static ECMDamageStatics DStatics;
	return DStatics;
}

UECMExecCalc_Damage::UECMExecCalc_Damage()
{
	//Attributes to capture
	RelevantAttributesToCapture.Add(DamageStatics().AdaptiveReflexDef);
	RelevantAttributesToCapture.Add(DamageStatics().ResonanceSyncQualityDef);
	RelevantAttributesToCapture.Add(DamageStatics().ResonanceAmplificationDef);

}

void UECMExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
#pragma region BoilerPlate
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	IECMCombatInterface* SourceCombatInterface = Cast<IECMCombatInterface>(SourceAvatar);
	IECMCombatInterface* TargetCombatInterface = Cast<IECMCombatInterface>(TargetAvatar);

	const UECMCharacterClassInfo* CharacterClassInfo = UECMAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();


#pragma endregion BoilerPlate
	
	float Damage = Spec.GetSetByCallerMagnitude(FECMGameplayTags::Get().Effect_Damage); // Get Damage Set by Caller Magnitude

	bool bBlocked = false;
	BlockCal(ExecutionParams, EvaluateParameters, Damage, bBlocked); // Modify Damage by Critical Hit chance calculation

	bool bCritHit = false;
	if(bBlocked == false) {	CritCal(ExecutionParams, EvaluateParameters, Damage, bCritHit); } // Modify Damage by Critical Hit chance calculation

	// TODO add proper calculations, 
	// ArmorPenetrationCal(SourceCombatInterface,CharacterClassInfo,Damage);

	const FGameplayModifierEvaluatedData EvaluatedData(UECMAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}

void UECMExecCalc_Damage::BlockCal(const FGameplayEffectCustomExecutionParameters& ExecutionParams, const FAggregatorEvaluateParameters& EvaluateParameters, float& Damage, bool& bBlocked)
{
	float TargetAdaptiveReflex = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AdaptiveReflexDef, EvaluateParameters, TargetAdaptiveReflex);
	TargetAdaptiveReflex = FMath::Max<float>(TargetAdaptiveReflex, 0);

	bBlocked = FMath::RandRange(1,100) < TargetAdaptiveReflex;

	Damage = bBlocked ? Damage / 2.f : Damage;
}

void UECMExecCalc_Damage::CritCal(const FGameplayEffectCustomExecutionParameters& ExecutionParams,	const FAggregatorEvaluateParameters& EvaluateParameters, float& Damage, bool& bCritHit)
{
	float SourceResonanceSyncQuality = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ResonanceSyncQualityDef, EvaluateParameters, SourceResonanceSyncQuality);
	SourceResonanceSyncQuality = FMath::Max<float>(SourceResonanceSyncQuality, 0);

	float SourceResonanceAmplification = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ResonanceAmplificationDef, EvaluateParameters, SourceResonanceAmplification);
	SourceResonanceAmplification = FMath::Max<float>(SourceResonanceAmplification, 0);

	bCritHit = FMath::RandRange(1,100) < SourceResonanceSyncQuality;

	Damage = bCritHit ? Damage * SourceResonanceAmplification : Damage;
}

void UECMExecCalc_Damage::ArmorPenetrationCal(IECMCombatInterface* SourceCombatInterface, const UECMCharacterClassInfo* CharacterClassInfo, float& Damage)
{
	
	// Get coefficient form Character Class
	const FRealCurve* ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString());
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourceCombatInterface->GetPlayerLevel());
	
	// Example of armor penetration ( with scale if required ):
	// const float EffectiveArmor = TargetArmor * (100 - SourceArmorPenetration * ArmorPenetrationCoefficient ) / 100.f;
	// EffectiveArmor = FMath::Max<float>(EffectiveArmor, 0);
	// Damage *=  ( 100 - EffectiveArmor * scale ) / 100.f;
}
