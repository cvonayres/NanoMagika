// Copyright Electronic CAD Monkey [ECM]

#include "ECMGameplayTags.h"
#include "GameplayTagsManager.h"

// Declare GameplayTags
FECMGameplayTags FECMGameplayTags::GameplayTags;

void FECMGameplayTags::InitNativeGameplayTags()
{
	auto AddTag = [](FGameplayTag& TagRef, const FName& TagName, const FString& TagDesc)
	{
		TagRef = UGameplayTagsManager::Get().AddNativeGameplayTag(TagName, TagDesc);
	};

	#define INIT_TAG(name, str, des) AddTag(GameplayTags.name, FName(str), FString(des));

#pragma region Game
	/** Declares the "Game States" gameplay tag. */
	INIT_TAG(Game_State_Preload, "Game.State.Preload", "Add Description")
	INIT_TAG(Game_State_Loading, "Game.State.Loading", "Add Description")
	INIT_TAG(Game_State_InGame, "Game.State.InGame", "Add Description")
	INIT_TAG(Game_State_PostGame, "Game.State.PostGame", "Add Description")
#pragma endregion Game

#pragma region Player
	/** Declares the "Player Modes" gameplay tag. */
	INIT_TAG(Player_CameraMode_FPV, "Player.CameraMode.FPV", "Add Description")
	INIT_TAG(Player_CameraMode_TPV, "Player.CameraMode.TPV", "Add Description")
	INIT_TAG(Player_CameraMode_TDV, "Player.CameraMode.TDV", "Add Description")

	/** Declares the "Player Regen/Poison Status" gameplay tag. */
	INIT_TAG(Player_Status_VM_Regen, "Player.Status.VM.Regen", "Add Description")
	INIT_TAG(Player_Status_VM_Poison, "Player.Status.VM.Poison", "Add Description")
	INIT_TAG(Player_Status_AR_Regen, "Player.Status.AR.Regen", "Add Description")
	INIT_TAG(Player_Status_AR_Poison, "Player.Status.AR.Poison", "Add Description")

#pragma endregion Player

#pragma region Input
	/** Declares the "Inputs" gameplay tag. */
	INIT_TAG(Input_Action_Action, "Input.Actions.Move", "Add Description")
	INIT_TAG(Input_Action_Move, "Input.Actions.Move", "Add Description")
	INIT_TAG(Input_Action_MoveByMouse, "Input.Actions.MoveByMouse", "Add Description")
	INIT_TAG(Input_Action_MoveToMouseClicked, "Input.Actions.MoveToMouseClicked", "Add Description")
	INIT_TAG(Input_Mouse_LMB, "Input.Mouse.LMB", "Add Description")
	INIT_TAG(Input_Mouse_RMB, "Input.Mouse.RMB", "Add Description")
	INIT_TAG(Input_Key_Num1, "Input.Key.Num1", "Add Description")
	INIT_TAG(Input_Key_Num2, "Input.Key.Num2", "Add Description")
	INIT_TAG(Input_Key_Num3, "Input.Key.Num3", "Add Description")
	INIT_TAG(Input_Key_Num4, "Input.Key.Num4", "Add Description")
	INIT_TAG(Input_Action_CameraMode_FPV, "Input.Action.CameraMode", "Add Description")
	INIT_TAG(Input_Action_CameraMode_FPV, "Input.Action.CameraMode.FPV", "Add Description")
	INIT_TAG(Input_Action_CameraMode_TPV, "Input.Action.CameraMode.TPV", "Add Description")
	INIT_TAG(Input_Action_CameraMode_TDV, "Input.Action.CameraMode.TDV", "Add Description")

#pragma endregion Input
	
#pragma region Abiltiies
	/** Declares the "Abiltiies" gameplay tag. */
	INIT_TAG(Abilities_Attack_Melee, "Abilities.Attack.Melee", "Add Description")
	INIT_TAG(Abilities_Attack_Ranged, "Abilities.Attack.Ranged", "Add Description")
	INIT_TAG(Abilities_Fire_Firebolt, "Abilities.Fire.Firebolt", "Add Description")

#pragma endregion Abiltiies

#pragma region Cooldown
	/** Declares the "Cooldown" gameplay tag. */
	INIT_TAG(CoolDown_Fire_Firebolt, "Cooldown.Fire.Firebolt", "Add Description")
#pragma endregion Cooldown
	
#pragma region Attributes
	/** Declares the "Vital Attributes" gameplay tag. */
	INIT_TAG(Attribute_Vital_VitalityMatrix, "Attribute.Vital.VitalityMatrix", "Add Description")
	INIT_TAG(Attribute_Vital_EnergeticEndurance, "Attribute.Vital.EnergeticEndurance", "Add Description")
	INIT_TAG(Attribute_Vital_ArcaneReservoir, "Attribute.Vital.ArcaneReservoir", "Add Description")
	INIT_TAG(Attribute_Vital_DefensiveSynchrony, "Attribute.Vital.DefensiveSynchrony", "Add Description")
	INIT_TAG(Attribute_Vital_BarrierMatrix, "Attribute.Vital.BarrierMatrix", "Add Description")

	/** Declares the "Primary Attributes" gameplay tag. */
	INIT_TAG(Attribute_Primary_Physique, "Attribute.Primary.Physique", "Add Description")
	INIT_TAG(Attribute_Primary_Adaptivity, "Attribute.Primary.Adaptivity", "Add Description")
	INIT_TAG(Attribute_Primary_NeuralAgility, "Attribute.Primary.NeuralAgility", "Add Description")
	INIT_TAG(Attribute_Primary_EmpathicResonance, "Attribute.Primary.EmpathicResonance", "Add Description")
	INIT_TAG(Attribute_Primary_EssenceControl, "Attribute.Primary.EssenceControl", "Add Description")
	INIT_TAG(Attribute_Primary_Nanomancy, "Attribute.Primary.Nanomancy", "Add Description")

	/** Declares the "Secondary Attributes" gameplay tag. */
	INIT_TAG(Attribute_Secondary_VMCapacity, "Attribute.Secondary.VMCapacity", "Add Description")
	INIT_TAG(Attribute_Secondary_VMRecovery, "Attribute.Secondary.VMRecovery", "Add Description")
	INIT_TAG(Attribute_Secondary_EECapacity, "Attribute.Secondary.EECapacity", "Add Description")
	INIT_TAG(Attribute_Secondary_EERecovery, "Attribute.Secondary.EERecovery", "Add Description")
	INIT_TAG(Attribute_Secondary_ARCapacity, "Attribute.Secondary.ARCapacity", "Add Description")
	INIT_TAG(Attribute_Secondary_ARRecovery, "Attribute.Secondary.ARRecovery", "Add Description")
	INIT_TAG(Attribute_Secondary_KineticAbsorption, "Attribute.Secondary.KineticAbsorption", "Add Description")
	INIT_TAG(Attribute_Secondary_NanoshieldThreshold, "Attribute.Secondary.NanoshieldThreshold", "Add Description")
	INIT_TAG(Attribute_Secondary_AdaptiveReflex, "Attribute.Secondary.AdaptiveReflex", "Add Description")
	INIT_TAG(Attribute_Secondary_ResonanceSyncQuality, "Attribute.Secondary.ResonanceSyncQuality", "Add Description")
	INIT_TAG(Attribute_Secondary_ResonanceAmplification, "Attribute.Secondary.ResonanceAmplification", "Add Description")
	INIT_TAG(Attribute_Secondary_EmpathicInfluence, "Attribute.Secondary.EmpathicInfluence", "Add Description")
	INIT_TAG(Attribute_Secondary_TechnologicalInterface, "Attribute.Secondary.TechnologicalInterface", "Add Description")
	INIT_TAG(Attribute_Secondary_SignalStealth, "Attribute.Secondary.SignalStealth", "Add Description")
	INIT_TAG(Attribute_Secondary_ReactionSpeed, "Attribute.Secondary.ReactionSpeed", "Add Description")
	INIT_TAG(Attribute_Secondary_DimensionalPocketCapacity, "Attribute.Secondary.DimensionalPocketCapacity", "Add Description")

	/** Declares the "Tertiary Attributes" gameplay tag. */
	INIT_TAG(Attribute_Resistance_Physical, "Attribute.Resistance.Physical", "Resistance to Physical Damage Attacks")
	INIT_TAG(Attribute_Resistance_Fire, "Attribute.Resistance.Fire", "Add Description")
	INIT_TAG(Attribute_Resistance_Frost, "Attribute.Resistance.Frost", "Add Description")
	INIT_TAG(Attribute_Resistance_Lightning, "Attribute.Resistance.Lightning", "Add Description")
	INIT_TAG(Attribute_Resistance_Earth, "Attribute.Resistance.Earth", "Add Description")
	INIT_TAG(Attribute_Resistance_Nanotech, "Attribute.Resistance.Nanotech", "Add Description")

#pragma endregion Attributes

#pragma region Character
	/** Declares the "Character Type" gameplay tag. */
	INIT_TAG(Character_Type_Player, "Character.Type.Player", "Add Description")

	INIT_TAG(Character_Type_Enemy, "Character.Type.Enemy", "Add Description")

	INIT_TAG(Character_Type_NPC_Quest, "Character.Type.NPC.Quest", "Add Description")
	INIT_TAG(Character_Type_NPC_Merchant, "Character.Type.NPC.Merchant", "Add Description")

	INIT_TAG(Character_Class_Melee, "Character.Class.Melee", "Add Description")
	INIT_TAG(Character_Class_Ranged, "Character.Class.Ranged", "Add Description")
#pragma endregion Character
	
#pragma region UIMessages
	/** Declares the "Potion Messages" gameplay tag. */
	INIT_TAG(Message_UI_Potion_VM_Healing, "Message.UI.Potion.VM.Healing", "Add Description")
	INIT_TAG(Message_UI_Potion_VM_Damage, "Message.UI.Potion.VM.Damage", "Add Description")
	INIT_TAG(Message_UI_Potion_VM_Regen, "Message.UI.Potion.VM.Regen", "Add Description")
	INIT_TAG(Message_UI_Potion_VM_Poison, "Message.UI.Potion.VM.Poison", "Add Description")
	INIT_TAG(Message_UI_Potion_AR_Healing, "Message.UI.Potion.AR.Healing", "Add Description")
	INIT_TAG(Message_UI_Potion_AR_Damage, "Message.UI.Potion.AR.Damage", "Add Description")
	INIT_TAG(Message_UI_Potion_AR_Regen, "Message.UI.Potion.AR.Regen", "Add Description")
	INIT_TAG(Message_UI_Potion_AR_Poison, "Message.UI.Potion.AR.Poison", "Add Description")
#pragma endregion UIMessages

#pragma region Effects
/** Declares the "Potion Messages" gameplay tag. */
	INIT_TAG(Effect_Healing, "Effect.Healing", "Add Description")
	INIT_TAG(Effect_Damage, "Effect.Damage", "Add Description")
	INIT_TAG(Effect_HitReact, "Effect.HitReact", "Add Description")
	
	INIT_TAG(Effect_Damage_Physical, "Effect.Damage.Physical", "Add Description")
	INIT_TAG(Effect_Damage_Fire, "Effect.Damage.Fire", "Add Description")
	INIT_TAG(Effect_Damage_Frost, "Effect.Damage.Frost", "Add Description")
	INIT_TAG(Effect_Damage_Lightning, "Effect.Damage.Lightning", "Add Description")
	INIT_TAG(Effect_Damage_Earth, "Effect.Damage.Earth", "Add Description")
	INIT_TAG(Effect_Damage_Nanotech, "Effect.Damage.Nanotech", "Add Description")

#pragma endregion Effects

#pragma region Montage
/** Declares the "Montage" gameplay tag. */
	INIT_TAG(Montage_Attack_Weapon, "Montage.Attack.Weapon", "Add Description")
	INIT_TAG(Montage_Attack_RightHand, "Montage.Attack.RighHand", "Add Description")
	INIT_TAG(Montage_Attack_LeftHand, "Montage.Attack.LeftHand", "Add Description")
	
#pragma endregion Montage

	#undef INIT_TAG

	// Add to TMap
	GameplayTags.DamageTypeToResistance.Add(GameplayTags.Effect_Damage_Physical, GameplayTags.Attribute_Resistance_Physical);
	GameplayTags.DamageTypeToResistance.Add(GameplayTags.Effect_Damage_Fire, GameplayTags.Attribute_Resistance_Fire);
	GameplayTags.DamageTypeToResistance.Add(GameplayTags.Effect_Damage_Frost, GameplayTags.Attribute_Resistance_Frost);
	GameplayTags.DamageTypeToResistance.Add(GameplayTags.Effect_Damage_Lightning, GameplayTags.Attribute_Resistance_Lightning);
	GameplayTags.DamageTypeToResistance.Add(GameplayTags.Effect_Damage_Earth, GameplayTags.Attribute_Resistance_Earth);
	GameplayTags.DamageTypeToResistance.Add(GameplayTags.Effect_Damage_Nanotech, GameplayTags.Attribute_Resistance_Nanotech);

}
