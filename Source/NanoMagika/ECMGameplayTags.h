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

#pragma region Game
	/** Declares the "Game States" gameplay tag. */
	DECLARE_GAMEPLAY_TAG(Game_State_Preload)
	DECLARE_GAMEPLAY_TAG(Game_State_Loading)
	DECLARE_GAMEPLAY_TAG(Game_State_InGame)
	DECLARE_GAMEPLAY_TAG(Game_State_PostGame)
#pragma endregion Game

#pragma region Player
	/** Declares the "Player Mode" gameplay tag. */
	DECLARE_GAMEPLAY_TAG(Player_CameraMode_FPV)
	DECLARE_GAMEPLAY_TAG(Player_CameraMode_TPV)
	DECLARE_GAMEPLAY_TAG(Player_CameraMode_TDV)
	
	/** Declares the "Player Regen/Poison Status" gameplay tag. */
	DECLARE_GAMEPLAY_TAG(Player_Status_VM_Regen)
	DECLARE_GAMEPLAY_TAG(Player_Status_VM_Poison)
	DECLARE_GAMEPLAY_TAG(Player_Status_AR_Regen)
	DECLARE_GAMEPLAY_TAG(Player_Status_AR_Poison)
#pragma endregion Player

#pragma region Input
	/** Declares the "Inputs" gameplay tag. */
	DECLARE_GAMEPLAY_TAG(Input_Action_Action)
	DECLARE_GAMEPLAY_TAG(Input_Action_Move)
	DECLARE_GAMEPLAY_TAG(Input_Action_MoveByMouse)
	DECLARE_GAMEPLAY_TAG(Input_Action_MoveToMouseClicked)
	
	DECLARE_GAMEPLAY_TAG(Input_Action_Camera_FPV)
	DECLARE_GAMEPLAY_TAG(Input_Action_Camera_TPV)
	DECLARE_GAMEPLAY_TAG(Input_Action_Camera_TDV)
	
	DECLARE_GAMEPLAY_TAG(Input_Mouse_LMB)
	DECLARE_GAMEPLAY_TAG(Input_Mouse_RMB)
	
	DECLARE_GAMEPLAY_TAG(Input_Key_Num1)
	DECLARE_GAMEPLAY_TAG(Input_Key_Num2)
	DECLARE_GAMEPLAY_TAG(Input_Key_Num3)
	DECLARE_GAMEPLAY_TAG(Input_Key_Num4)
#pragma endregion Input

#pragma region Attributes
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
#pragma endregion Attributes

#pragma region Character
	/** Declares the "Character Type" gameplay tag. */
	DECLARE_GAMEPLAY_TAG(Character_Type_Player)
	
	DECLARE_GAMEPLAY_TAG(Character_Type_Enemy_Goblin_Slingshot)
	DECLARE_GAMEPLAY_TAG(Character_Type_Enemy_Goblin_Spear)

	DECLARE_GAMEPLAY_TAG(Character_Type_NPC_Quest)
	DECLARE_GAMEPLAY_TAG(Character_Type_NPC_Merchant)
#pragma endregion Character
	
#pragma region UIMessages
	/** Declares the "Potion Messages" gameplay tag. */
	DECLARE_GAMEPLAY_TAG(Message_UI_Potion_VM_Healing)
	DECLARE_GAMEPLAY_TAG(Message_UI_Potion_VM_Damage)
	DECLARE_GAMEPLAY_TAG(Message_UI_Potion_VM_Regen)
	DECLARE_GAMEPLAY_TAG(Message_UI_Potion_VM_Poison)
	DECLARE_GAMEPLAY_TAG(Message_UI_Potion_AR_Healing)
	DECLARE_GAMEPLAY_TAG(Message_UI_Potion_AR_Damage)
	DECLARE_GAMEPLAY_TAG(Message_UI_Potion_AR_Regen)
	DECLARE_GAMEPLAY_TAG(Message_UI_Potion_AR_Poison)
#pragma endregion UIMessages

#pragma region Effects
	DECLARE_GAMEPLAY_TAG(Effect_Healing)
	DECLARE_GAMEPLAY_TAG(Effect_Damage)
	DECLARE_GAMEPLAY_TAG(Effect_HitReact)

#pragma endregion Effects

	
	#undef DECLARE_GAMEPLAY_TAG

private:
	static FECMGameplayTags GameplayTags;
};
