// Copyright Electronic CAD Monkey [ECM]

#include "ECMExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "NanoMagika/ECMAbilityTypes.h"
#include "NanoMagika/ECMGameplayTags.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemLibrary.h"
#include "NanoMagika/AbilitySystem/Attributes/ECMAttributeSet.h"
#include "NanoMagika/Interaction/ECMCombatInterface.h"

struct ECMDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AdaptiveReflex);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResonanceSyncQuality);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResonanceAmplification);

	DECLARE_ATTRIBUTE_CAPTUREDEF(ResistancePhysical);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResistanceFire);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResistanceFrost);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResistanceLightning);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResistanceEarth);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResistanceNanotech);

	TMap <FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	
	ECMDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UECMAttributeSet, AdaptiveReflex, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UECMAttributeSet, ResonanceSyncQuality, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UECMAttributeSet, ResonanceAmplification, Source, true);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UECMAttributeSet, ResistancePhysical, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UECMAttributeSet, ResistanceFire, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UECMAttributeSet, ResistanceFrost, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UECMAttributeSet, ResistanceLightning, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UECMAttributeSet, ResistanceEarth, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UECMAttributeSet, ResistanceNanotech, Target, false);

		const FECMGameplayTags& Tags = FECMGameplayTags::Get();
		TagsToCaptureDefs.Add(Tags.Attribute_Secondary_AdaptiveReflex, AdaptiveReflexDef);
		TagsToCaptureDefs.Add(Tags.Attribute_Secondary_ResonanceSyncQuality, ResonanceSyncQualityDef);
		TagsToCaptureDefs.Add(Tags.Attribute_Secondary_ResonanceSyncQuality, ResonanceAmplificationDef);

		TagsToCaptureDefs.Add(Tags.Attribute_Resistance_Physical, ResistancePhysicalDef);
		TagsToCaptureDefs.Add(Tags.Attribute_Resistance_Fire, ResistanceFireDef);
		TagsToCaptureDefs.Add(Tags.Attribute_Resistance_Frost, ResistanceFrostDef);
		TagsToCaptureDefs.Add(Tags.Attribute_Resistance_Lightning, ResistanceLightningDef);
		TagsToCaptureDefs.Add(Tags.Attribute_Resistance_Earth, ResistanceEarthDef);
		TagsToCaptureDefs.Add(Tags.Attribute_Resistance_Nanotech, ResistanceNanotechDef);
		
	}
};

static const ECMDamageStatics& DamageStatics()
{
	static ECMDamageStatics DStatics;
	return DStatics;
}

UECMExecCalc_Damage::UECMExecCalc_Damage()
{
	const ECMDamageStatics& DStatic = DamageStatics();
	RelevantAttributesToCapture.Append({
		DStatic.AdaptiveReflexDef,
		DStatic.ResonanceSyncQualityDef,
		DStatic.ResonanceAmplificationDef,
		DStatic.ResistancePhysicalDef,
		DStatic.ResistanceFireDef,
		DStatic.ResistanceFrostDef,
		DStatic.ResistanceLightningDef,
		DStatic.ResistanceEarthDef,
		DStatic.ResistanceNanotechDef
	});
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
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
#pragma endregion BoilerPlate

	float Damage = 0.f;
	ResistanceCal(ExecutionParams, EvaluateParameters, Spec,Damage); // Modify Damage by Damage Type & Resistances
	
	bool bBlockedHit = false;
	BlockCal(ExecutionParams, EvaluateParameters, EffectContextHandle, Damage, bBlockedHit); // Modify Damage by Blocking Hit chance calculation

	if(!bBlockedHit)
	{
		bool bCriticalHit = false;
		CritCal(ExecutionParams, EvaluateParameters, EffectContextHandle, Damage, bCriticalHit); // Modify Damage by Critical Hit chance calculation
	} 

	// TODO add proper calculations, 
	// ArmorPenetrationCal(SourceCombatInterface, CharacterClassInfo, Damage);

	const FGameplayModifierEvaluatedData EvaluatedData(UECMAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}

void UECMExecCalc_Damage::ResistanceCal(const FGameplayEffectCustomExecutionParameters& ExecutionParams, const FAggregatorEvaluateParameters& EvaluateParameters, const FGameplayEffectSpec& Spec, float& Damage)
{
	for(const TTuple<FGameplayTag, FGameplayTag>& Pair : FECMGameplayTags::Get().DamageTypeToResistance)
	{
		const FGameplayTag DamageTypeTag = Pair.Key;

		if(float DamageTypeValve = Spec.GetSetByCallerMagnitude(DamageTypeTag, false); FMath::Abs(DamageTypeValve) > KINDA_SMALL_NUMBER)
			{
			const FGameplayTag ResistanceTag = Pair.Value;

			checkf(ECMDamageStatics().TagsToCaptureDefs.Contains(ResistanceTag), TEXT("TagsToCaptureDefs doesn't contain Tag: [%s] in ExecCalc_damage"), *ResistanceTag.ToString());
			const FGameplayEffectAttributeCaptureDefinition CaptureDef = ECMDamageStatics().TagsToCaptureDefs[ResistanceTag];
		
			float Resistance = 0.f;
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluateParameters,Resistance);
			Resistance = FMath::Clamp(Resistance, 0.f,100.f);
		
			DamageTypeValve *= (100.f - Resistance) / 100.f;

			Damage +=  DamageTypeValve;
			}
	}	
}

void UECMExecCalc_Damage::BlockCal(const FGameplayEffectCustomExecutionParameters& ExecutionParams, const FAggregatorEvaluateParameters& EvaluateParameters, FGameplayEffectContextHandle& EffectContextHandle, float& Damage, bool& bBlockedHit)
{
	// Get Attributes involved in calculation
	float TargetAdaptiveReflex = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AdaptiveReflexDef, EvaluateParameters, TargetAdaptiveReflex);
	TargetAdaptiveReflex = FMath::Max<float>(TargetAdaptiveReflex, 0);

	// Get random number and see if it was a blocked hit
	bBlockedHit = FMath::RandRange(1,100) < TargetAdaptiveReflex;

	// Pass block hit result to Static Library for inclusion in Effect Context
	UECMAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlockedHit);

	// Recalculate Damage based on result
	Damage = bBlockedHit ? Damage / 2.f : Damage;
}

void UECMExecCalc_Damage::CritCal(const FGameplayEffectCustomExecutionParameters& ExecutionParams, const FAggregatorEvaluateParameters& EvaluateParameters, FGameplayEffectContextHandle& EffectContextHandle, float& Damage, bool& bCriticalHit)
{
	// Get Attributes involved in calculation
	float SourceResonanceSyncQuality = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ResonanceSyncQualityDef, EvaluateParameters, SourceResonanceSyncQuality);
	SourceResonanceSyncQuality = FMath::Max<float>(SourceResonanceSyncQuality, 0);

	float SourceResonanceAmplification = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ResonanceAmplificationDef, EvaluateParameters, SourceResonanceAmplification);
	SourceResonanceAmplification = FMath::Max<float>(SourceResonanceAmplification, 0);

	// Get random number and see if it was a critical hit
	bCriticalHit = FMath::RandRange(1,100) < SourceResonanceSyncQuality;

	// Pass critical hit result to Static Library for inclusion in Effect Context
	UECMAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCriticalHit);

	// Recalculate Damage based on result
	Damage = bCriticalHit ? Damage * SourceResonanceAmplification : Damage;
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
