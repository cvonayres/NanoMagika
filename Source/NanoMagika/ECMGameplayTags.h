// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 *	ECMGameplayTags
 *
 *	Singleton containing native Gameplay Tags
 */

struct FECMGameplayTags
{
public:
	static const FECMGameplayTags& Get() { return GameplayTags;}
	static void InitNativeGameplayTags ();

	#define DECLARE_GAMEPLAY_TAG(name) FGameplayTag name;

	/** Declares the "Vital Attributes" gameplay tag. */
	DECLARE_GAMEPLAY_TAG(Attribute_Vital_VitalityMatrix)
	DECLARE_GAMEPLAY_TAG(Attribute_Vital_EnergeticEndurance)
	DECLARE_GAMEPLAY_TAG(Attribute_Vital_ArcaneReservoir)
	DECLARE_GAMEPLAY_TAG(Attribute_Vital_DefensiveSynchrony)
	DECLARE_GAMEPLAY_TAG(Attribute_Vital_BarrierMatrix)

	/** Declares the "Primary Attributes" gameplay tag. */
	DECLARE_GAMEPLAY_TAG(Attribute_Primary_Physique)
	DECLARE_GAMEPLAY_TAG(Attribute_Primary_Adaptivity)
	DECLARE_GAMEPLAY_TAG(Attribute_Primary_NeuralAgility)
	DECLARE_GAMEPLAY_TAG(Attribute_Primary_EmpathicResonance)
	DECLARE_GAMEPLAY_TAG(Attribute_Primary_EssenceControl)
	DECLARE_GAMEPLAY_TAG(Attribute_Primary_Nanomancy)

	/** Declares the "Secondary Attributes" gameplay tag. */
	DECLARE_GAMEPLAY_TAG(Attribute_Secondary_VMCapacity)
	DECLARE_GAMEPLAY_TAG(Attribute_Secondary_VMRecovery)
	DECLARE_GAMEPLAY_TAG(Attribute_Secondary_EECapacity)
	DECLARE_GAMEPLAY_TAG(Attribute_Secondary_EERecovery)
	DECLARE_GAMEPLAY_TAG(Attribute_Secondary_ARCapacity)
	DECLARE_GAMEPLAY_TAG(Attribute_Secondary_ARRecovery)
	DECLARE_GAMEPLAY_TAG(Attribute_Secondary_KineticAbsorption)
	DECLARE_GAMEPLAY_TAG(Attribute_Secondary_NanoshieldThreshold)
	DECLARE_GAMEPLAY_TAG(Attribute_Secondary_ResonanceSyncQuality)
	DECLARE_GAMEPLAY_TAG(Attribute_Secondary_ResonanceAmplification)
	DECLARE_GAMEPLAY_TAG(Attribute_Secondary_EmpathicInfluence)
	DECLARE_GAMEPLAY_TAG(Attribute_Secondary_TechnologicalInterface)
	DECLARE_GAMEPLAY_TAG(Attribute_Secondary_SignalStealth)
	DECLARE_GAMEPLAY_TAG(Attribute_Secondary_ReactionSpeed)
	DECLARE_GAMEPLAY_TAG(Attribute_Secondary_DimensionalPocketCapacity)
		
	/** Declares the "Tertiary Attributes" gameplay tag. */
	DECLARE_GAMEPLAY_TAG(Attribute_Tertiary_FireResistance)
	DECLARE_GAMEPLAY_TAG(Attribute_Tertiary_LightingResistance)
	DECLARE_GAMEPLAY_TAG(Attribute_Tertiary_NanotechResistance)

	#undef DECLARE_GAMEPLAY_TAG

protected:

private:
	static FECMGameplayTags GameplayTags;
};
