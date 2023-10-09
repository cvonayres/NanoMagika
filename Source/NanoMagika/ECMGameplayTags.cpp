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

#pragma region Game
	/** Declares the "Game States" gameplay tag. */
	INIT_TAG(Game_State_Preload, "Game.State.Preload")
	INIT_TAG(Game_State_Loading, "Game.State.Loading")
	INIT_TAG(Game_State_InGame, "Game.State.InGame")
	INIT_TAG(Game_State_PostGame, "Game.State.PostGame")
#pragma endregion Game

#pragma region Player
	/** Declares the "Player Modes" gameplay tag. */
	INIT_TAG(Player_CameraMode_FPV, "Player.CameraMode.FPV")
	INIT_TAG(Player_CameraMode_TPV, "Player.CameraMode.TPV")
	INIT_TAG(Player_CameraMode_TDV, "Player.CameraMode.TDV")

	/** Declares the "Player Regen/Poison Status" gameplay tag. */
	INIT_TAG(Player_Status_VM_Regen, "Player.Status.VM.Regen")
	INIT_TAG(Player_Status_VM_Poison, "Player.Status.VM.Poison")
	INIT_TAG(Player_Status_AR_Regen, "Player.Status.AR.Regen")
	INIT_TAG(Player_Status_AR_Poison, "Player.Status.AR.Poison")

#pragma endregion Player

#pragma region Input
	/** Declares the "Inputs" gameplay tag. */
	INIT_TAG(Input_Action_Action, "Input.Actions.Move")
	INIT_TAG(Input_Action_Move, "Input.Actions.Move")
	INIT_TAG(Input_Action_MoveByMouse, "Input.Actions.MoveByMouse")
	INIT_TAG(Input_Action_MoveToMouseClicked, "Input.Actions.MoveToMouseClicked")
	INIT_TAG(Input_Mouse_LMB, "Input.Mouse.LMB")
	INIT_TAG(Input_Mouse_RMB, "Input.Mouse.RMB")
	INIT_TAG(Input_Key_Num1, "Input.Key.Num1")
	INIT_TAG(Input_Key_Num2, "Input.Key.Num2")
	INIT_TAG(Input_Key_Num3, "Input.Key.Num3")
	INIT_TAG(Input_Key_Num4, "Input.Key.Num4")
#pragma endregion Input

#pragma region Attributes
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
#pragma endregion Attributes

#pragma region Character
	/** Declares the "Character Type" gameplay tag. */
	INIT_TAG(Character_Type_Player, "Character.Type.Player")
	INIT_TAG(Character_Type_Enemy, "Character.Type.Enemy")
	INIT_TAG(Character_Type_NPC, "Character.Type.NPC")
#pragma endregion Character

	#pragma region UIMessages
	/** Declares the "Potion Messages" gameplay tag. */
	INIT_TAG(Message_UI_Potion_VM_Healing, "Message.UI.Potion.VM.Healing")
	INIT_TAG(Message_UI_Potion_VM_Damage, "Message.UI.Potion.VM.Damage")
	INIT_TAG(Message_UI_Potion_VM_Regen, "Message.UI.Potion.VM.Regen")
	INIT_TAG(Message_UI_Potion_VM_Poison, "Message.UI.Potion.VM.Poison")
	INIT_TAG(Message_UI_Potion_AR_Healing, "Message.UI.Potion.AR.Healing")
	INIT_TAG(Message_UI_Potion_AR_Damage, "Message.UI.Potion.AR.Damage")
	INIT_TAG(Message_UI_Potion_AR_Regen, "Message.UI.Potion.AR.Regen")
	INIT_TAG(Message_UI_Potion_AR_Poison, "Message.UI.Potion.AR.Poison")
#pragma endregion UIMessages
	
	#undef INIT_TAG
}
