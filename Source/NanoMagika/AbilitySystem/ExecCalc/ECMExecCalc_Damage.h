// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ECMExecCalc_Damage.generated.h"

class UECMCharacterClassInfo;
class IECMCombatInterface;

UCLASS()
class NANOMAGIKA_API UECMExecCalc_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UECMExecCalc_Damage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

private:
	FGameplayEffectAttributeCaptureDefinition PhysiqueDef;

	static void ResistanceCal(const FGameplayEffectCustomExecutionParameters& ExecutionParams, const FAggregatorEvaluateParameters& EvaluateParameters, const FGameplayEffectSpec& Spec, float& Damage);

	static void BlockCal(const FGameplayEffectCustomExecutionParameters& ExecutionParams, const FAggregatorEvaluateParameters& EvaluateParameters, FGameplayEffectContextHandle& EffectContextHandle, float& Damage, bool& bBlockedHit);
	static void CritCal(const FGameplayEffectCustomExecutionParameters& ExecutionParams, const FAggregatorEvaluateParameters& EvaluateParameters, FGameplayEffectContextHandle& EffectContextHandle, float& Damage, bool& bCriticalHit);
	static void ArmorPenetrationCal(IECMCombatInterface* SourceCombatInterface, const UECMCharacterClassInfo* CharacterClassInfo, float& Damage);

};
