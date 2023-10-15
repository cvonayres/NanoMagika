// Copyright Electronic CAD Monkey [ECM]

#include "ECMAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "NanoMagika/ECMGameplayTags.h"
#include "NanoMagika/Interaction/ECMCombatInterface.h"
#include "NanoMagika/Player/PlayerController/ECMPlayerController.h"
#include "Net/UnrealNetwork.h"

#pragma region Mapping
UECMAttributeSet::UECMAttributeSet()
{
	const FECMGameplayTags& GameplayTags = FECMGameplayTags::Get();
	
	// Vital Attributes to be mapped
	TagsToAttributes.Add(GameplayTags.Attribute_Vital_VitalityMatrix, GetVitalityMatrixAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Vital_EnergeticEndurance, GetEnergeticEnduranceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Vital_ArcaneReservoir, GetArcaneReservoirAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Vital_DefensiveSynchrony, GetDefensiveSynchronyAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Vital_EnergeticEndurance, GetEnergeticEnduranceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Nanomancy, GetNanomancyAttribute);
	
	// Primary Attributes to be mapped
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Physique, GetPhysiqueAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Adaptivity, GetAdaptivityAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_NeuralAgility, GetNeuralAgilityAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_EmpathicResonance, GetEmpathicResonanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_EssenceControl, GetEssenceControlAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Nanomancy, GetNanomancyAttribute);

	// Secondary Attributes to be mapped
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_VMCapacity, GetVMCapacityAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_VMRecovery, GetVMRecoveryAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_EECapacity, GetEECapacityAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_EERecovery, GetEERecoveryAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_ARCapacity, GetARCapacityAttribute);
    TagsToAttributes.Add(GameplayTags.Attribute_Secondary_ARRecovery, GetARRecoveryAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_KineticAbsorption, GetKineticAbsorptionAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_NanoshieldThreshold, GetNanoshieldThresholdAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_AdaptiveReflex, GetAdaptiveReflexAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_ResonanceSyncQuality, GetResonanceSyncQualityAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_ResonanceAmplification, GetResonanceAmplificationAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_EmpathicInfluence, GetEmpathicInfluenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_TechnologicalInterface, GetTechnologicalInterfaceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_SignalStealth, GetSignalStealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_ReactionSpeed, GetReactionSpeedAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_DimensionalPocketCapacity, GetDimensionalPocketCapacityAttribute);

	// Tertiary Attributes to be mapped

}

#pragma endregion Mapping

#pragma region AttributeChange

struct FECMAttibuteTMap
{
	FECMAttibuteTMap(){ }

	struct AttributeFunctionMappings
	{
		float (UECMAttributeSet::*Getter)() const = nullptr;
		void (UECMAttributeSet::*Setter)(float) = nullptr;
		float (UECMAttributeSet::*MaxFunc)() const;
	};
	
	TMap<FGameplayAttribute, AttributeFunctionMappings> AttributeMap {
			{ UECMAttributeSet::GetVitalityMatrixAttribute(), { &UECMAttributeSet::GetVitalityMatrix, &UECMAttributeSet::SetVitalityMatrix, &UECMAttributeSet::GetVMCapacity } },
			{ UECMAttributeSet::GetEnergeticEnduranceAttribute(), { &UECMAttributeSet::GetEnergeticEndurance, &UECMAttributeSet::SetEnergeticEndurance, &UECMAttributeSet::GetEECapacity } },
			{ UECMAttributeSet::GetArcaneReservoirAttribute(), { &UECMAttributeSet::GetArcaneReservoir, &UECMAttributeSet::SetArcaneReservoir, &UECMAttributeSet::GetARCapacity } },
			{ UECMAttributeSet::GetDefensiveSynchronyAttribute(), { &UECMAttributeSet::GetDefensiveSynchrony, &UECMAttributeSet::SetDefensiveSynchrony, &UECMAttributeSet::GetKineticAbsorption } },
			{ UECMAttributeSet:: GetBarrierMatrixAttribute(), { &UECMAttributeSet::GetBarrierMatrix, &UECMAttributeSet::SetBarrierMatrix, &UECMAttributeSet::GetNanoshieldThreshold } },

			{ UECMAttributeSet::GetPhysiqueAttribute(), { &UECMAttributeSet::GetPhysique, &UECMAttributeSet::SetPhysique, &UECMAttributeSet::GetMaxPrimaryStat } },
			{ UECMAttributeSet::GetAdaptivityAttribute(), { &UECMAttributeSet::GetAdaptivity, &UECMAttributeSet::SetAdaptivity, &UECMAttributeSet::GetMaxPrimaryStat } },
			{ UECMAttributeSet::GetNeuralAgilityAttribute(), { &UECMAttributeSet::GetNeuralAgility, &UECMAttributeSet::SetNeuralAgility, &UECMAttributeSet::GetMaxPrimaryStat } },
			{ UECMAttributeSet::GetEmpathicResonanceAttribute(), { &UECMAttributeSet::GetEmpathicResonance, &UECMAttributeSet::SetEmpathicResonance, &UECMAttributeSet::GetMaxPrimaryStat } },
			{ UECMAttributeSet::GetEssenceControlAttribute(), { &UECMAttributeSet::GetEssenceControl, &UECMAttributeSet::SetEssenceControl, &UECMAttributeSet::GetMaxPrimaryStat } },
			{ UECMAttributeSet::GetNanomancyAttribute(), { &UECMAttributeSet::GetNanomancy, &UECMAttributeSet::SetNanomancy, &UECMAttributeSet::GetMaxPrimaryStat } },
			} ;
};

static const FECMAttibuteTMap& GetAttributeTMap()
{
	static FECMAttibuteTMap AttributeTMapStatic;
	return AttributeTMapStatic;
}

// Clamp Valves
void UECMAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (auto AttributeMap = GetAttributeTMap().AttributeMap; AttributeMap.Contains(Attribute))
	{
		NewValue = FMath::Clamp(NewValue, 0.f, (this->*AttributeMap.Find(Attribute)->MaxFunc)());
	}
}

void UECMAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props)
{
	// Source = causer, Target = target of the effect (owner of this AS)

	Props.EffectContextHandle = Data.EffectSpec.GetContext();	//Get Context Handle

	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent(); 	//Get Source Ability System Component

	// Get Source Actor, Controller & Character
	if(IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor =  Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if(Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if(Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	// Get Target Actor, Controller & Character
	if(Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UECMAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	FEffectProperties Props;
	SetEffectProperties(Data, Props); // Set Effect Properties [i.e. source/target ASC, ACtor, Controller & Character]

	ClampAttributePost(Data.EvaluatedData.Attribute); // Clamp Attribute

	HandleDamage(Data.EvaluatedData.Attribute, Props); 	// Handle Damage

}

void UECMAttributeSet::ClampAttributePost(const FGameplayAttribute& Attribute)
{
	if(GetAttributeTMap().AttributeMap.Contains(Attribute) == false) return;

	const FECMAttibuteTMap::AttributeFunctionMappings* AttributeFunc = GetAttributeTMap().AttributeMap.Find(Attribute);

	(this->*AttributeFunc->Setter)(FMath::Clamp((this->*AttributeFunc->Getter)(), 0.f, (this->*AttributeFunc->MaxFunc)()));
}

void UECMAttributeSet::HandleDamage(const FGameplayAttribute& Attribute, const FEffectProperties& Props)
{
	if (Attribute != GetIncomingDamageAttribute() || GetIncomingDamage() <= 1.f) return;

	const float LocalIncomingDamage = GetIncomingDamage();
	SetIncomingDamage(0.f);

	const float NewHealth  = GetVitalityMatrix() - LocalIncomingDamage;
	SetVitalityMatrix(FMath::Clamp(NewHealth, 0, GetVMCapacity()));

	ShowDamageText(Props, LocalIncomingDamage); // Show floating damage numbers
			
	if(NewHealth <- 0.f)   // Check if dead
	{
		if(IECMCombatInterface* CombatInterface = Cast<IECMCombatInterface>(Props.TargetAvatarActor))
		{
			CombatInterface->Die();
		}
	}
	else
	{
		HitReaction(Props);
	}
}

void UECMAttributeSet::ShowDamageText(const FEffectProperties& Props, const float LocalIncomingDamage)
{
	if(Props.SourceCharacter != Props.TargetCharacter)
	{
		if (AECMPlayerController* PC = Cast<AECMPlayerController>(UGameplayStatics::GetPlayerController(Props.SourceCharacter, 0)))
		{
			PC->ShowDamageNumber(LocalIncomingDamage, Props.TargetCharacter );
		}
	}
}

void UECMAttributeSet::HitReaction(const FEffectProperties& Props)
{
	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(FECMGameplayTags::Get().Effect_HitReact);
	Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);	
}

#pragma endregion AttributeChange

#pragma region Replicate
// Replicate attributes
void UECMAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Vital Attributes to be replicated
	#pragma region RepVitalAttributes
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, VitalityMatrix, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, EnergeticEndurance, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, ArcaneReservoir, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, DefensiveSynchrony, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, BarrierMatrix, COND_None, REPNOTIFY_Always);
	#pragma endregion RepVitalAttributes
	
	// Primary Attributes to be replicated
	#pragma region RepPrimaryAttributes
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, Physique, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, Adaptivity, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, NeuralAgility, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, EmpathicResonance, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, EssenceControl, COND_None, REPNOTIFY_Always);
	#pragma endregion RepPrimaryAttributes

	// Secondary Attributes to be replicated
	#pragma region RepSecondaryAttributes
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, VMCapacity, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, VMRecovery, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, EECapacity, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, EERecovery, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, ARCapacity, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, ARRecovery, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, KineticAbsorption, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, NanoshieldThreshold, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, AdaptiveReflex, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, ResonanceSyncQuality, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, ResonanceAmplification, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, EmpathicInfluence, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, TechnologicalInterface, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, SignalStealth, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, ReactionSpeed, COND_None, REPNOTIFY_Always);
		DOREPLIFETIME_CONDITION_NOTIFY(UECMAttributeSet, DimensionalPocketCapacity, COND_None, REPNOTIFY_Always);
	#pragma endregion RepSecondaryAttributes
	
	// Tertiary Attributes to be replicated
	#pragma region RepTertiaryAttributes
	#pragma endregion RepTertiaryAttributes
}
#pragma endregion Replicate

#pragma region RefNofifies
// Macro for creating  repetitive Repfunctions
#define DEFINE_ATTRIBUTE_REPNOTIFY(ClassName, AttributeName) \
void ClassName::OnRep_##AttributeName(const FGameplayAttributeData& Old##AttributeName) const \
{ \
GAMEPLAYATTRIBUTE_REPNOTIFY(ClassName, AttributeName, Old##AttributeName); \
}

// Vital - Gameplay Attributes
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, VitalityMatrix)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, EnergeticEndurance)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, ArcaneReservoir)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, DefensiveSynchrony)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, BarrierMatrix)

// Primary - Gameplay Attributes
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, Physique)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, Adaptivity)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, NeuralAgility)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, EmpathicResonance)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, EssenceControl)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, Nanomancy)

// Secondary - Gameplay Attributes
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, VMCapacity)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, VMRecovery)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, EECapacity)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, EERecovery)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, ARCapacity)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, ARRecovery)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, KineticAbsorption)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, NanoshieldThreshold)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, AdaptiveReflex)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, ResonanceSyncQuality)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, ResonanceAmplification)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, EmpathicInfluence)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, TechnologicalInterface)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, SignalStealth)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, ReactionSpeed)
DEFINE_ATTRIBUTE_REPNOTIFY(UECMAttributeSet, DimensionalPocketCapacity)

// Tertiary - Gameplay Attributes

// Undefine the macro to prevent possible interference with other code
#undef DEFINE_ATTRIBUTE_REPNOTIFY

#pragma endregion RefNofifies
