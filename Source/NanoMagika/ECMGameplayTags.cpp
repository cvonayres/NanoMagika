// Copyright Electronic CAD Monkey [ECM]

#include "ECMGameplayTags.h"
#include "GameplayTagsManager.h"

// Declare GameplayTags
FECMGameplayTags FECMGameplayTags::GameplayTags;

void FECMGameplayTags::InitNativeGameplayTags()
{
	auto AddTag = [](FGameplayTag& TagRef, const FName& TagName)
	{
		TagRef = UGameplayTagsManager::Get().AddNativeGameplayTag(TagName);
	};

	#define INIT_TAG(name, str) AddTag(GameplayTags.name, FName(str));

	/** Declares the "Vital Attributes" gameplay tag. */
	INIT_TAG(Attribute_Vital_VitalityMatrix, "Attribute.Vital.VitalityMatrix")
	INIT_TAG(Attribute_Vital_EnergeticEndurance, "Attribute.Vital.EnergeticEndurance")
	INIT_TAG(Attribute_Vital_ArcaneReservoir, "Attribute.Vital.ArcaneReservoir")
	INIT_TAG(Attribute_Vital_DefensiveSynchrony, "Attribute.Vital.DefensiveSynchrony")
	INIT_TAG(Attribute_Vital_BarrierMatrix, "Attribute.Vital.BarrierMatrix")

	/** Declares the "Primary Attributes" gameplay tag. */
	INIT_TAG(Attribute_Primary_Physique, "Attribute.Primary.Physique")
	INIT_TAG(Attribute_Primary_Adaptivity, "Attribute.Primary.Adaptivity")
	INIT_TAG(Attribute_Primary_NeuralAgility, "Attribute.Primary.NeuralAgility")
	INIT_TAG(Attribute_Primary_EmpathicResonance, "Attribute.Primary.EmpathicResonance")
	INIT_TAG(Attribute_Primary_EssenceControl, "Attribute.Primary.EssenceControl")
	INIT_TAG(Attribute_Primary_Nanomancy, "Attribute.Primary.Nanomancy")

	/** Declares the "Secondary Attributes" gameplay tag. */
	INIT_TAG(Attribute_Secondary_VMCapacity, "Attribute.Secondary.VMCapacity")
	INIT_TAG(Attribute_Secondary_VMRecovery, "Attribute.Secondary.VMRecovery")
	INIT_TAG(Attribute_Secondary_EECapacity, "Attribute.Secondary.EECapacity")
	INIT_TAG(Attribute_Secondary_EERecovery, "Attribute.Secondary.EERecovery")
	INIT_TAG(Attribute_Secondary_ARCapacity, "Attribute.Secondary.ARCapacity")
	INIT_TAG(Attribute_Secondary_ARRecovery, "Attribute.Secondary.ARRecovery")
	INIT_TAG(Attribute_Secondary_KineticAbsorption, "Attribute.Secondary.KineticAbsorption")
	INIT_TAG(Attribute_Secondary_NanoshieldThreshold, "Attribute.Secondary.NanoshieldThreshold")
	INIT_TAG(Attribute_Secondary_ResonanceSyncQuality, "Attribute.Secondary.ResonanceSyncQuality")
	INIT_TAG(Attribute_Secondary_ResonanceAmplification, "Attribute.Secondary.ResonanceAmplification")
	INIT_TAG(Attribute_Secondary_EmpathicInfluence, "Attribute.Secondary.EmpathicInfluence")
	INIT_TAG(Attribute_Secondary_TechnologicalInterface, "Attribute.Secondary.TechnologicalInterface")
	INIT_TAG(Attribute_Secondary_SignalStealth, "Attribute.Secondary.SignalStealth")
	INIT_TAG(Attribute_Secondary_ReactionSpeed, "Attribute.Secondary.ReactionSpeed")
	INIT_TAG(Attribute_Secondary_DimensionalPocketCapacity, "Attribute.Secondary.DimensionalPocketCapacity")

	/** Declares the "Tertiary Attributes" gameplay tag. */
	INIT_TAG(Attribute_Tertiary_FireResistance, "Attribute.Tertiary.FireResistance")
	INIT_TAG(Attribute_Tertiary_LightingResistance, "Attribute.Tertiary.LightingResistance")
	INIT_TAG(Attribute_Tertiary_NanotechResistance, "Attribute.Tertiary.NanotechResistance")
	
#undef INIT_TAG
}
