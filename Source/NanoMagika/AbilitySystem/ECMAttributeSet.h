// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ECMAttributeSet.generated.h"

#pragma region Macros
// Macro for creating attribute getters, setters,etc
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
#pragma endregion Macros

struct AttributeFunctionMappings;

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	//  Effect Context Handle
	UPROPERTY()
	FGameplayEffectContextHandle EffectContextHandle;
	
	// Source Info
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	// Target Avatar Info
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

//  TStaticFuncPtr generic to specified function
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

UCLASS()
class NANOMAGIKA_API UECMAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UECMAttributeSet();
	
	// Replicate variables
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Used to Clamp Attributes before change
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	// Used to Clamp Attributes after change and harvest data of change
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// Returns attribute from Gameplay Tag
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;
	
// Vital - Gameplay Attributes
#pragma region VitalAttributes
		UPROPERTY(BlueprintReadOnly, Category = "Attributes|Vital", ReplicatedUsing = OnRep_VitalityMatrix)
		FGameplayAttributeData VitalityMatrix;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, VitalityMatrix);

		UPROPERTY(BlueprintReadOnly, Category = "Attributes|Vital", ReplicatedUsing = OnRep_EnergeticEndurance)
		FGameplayAttributeData EnergeticEndurance;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, EnergeticEndurance);

		UPROPERTY(BlueprintReadOnly, Category = "Attributes|Vital", ReplicatedUsing = OnRep_ArcaneReservoir)
		FGameplayAttributeData ArcaneReservoir;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, ArcaneReservoir);
	
		UPROPERTY(BlueprintReadOnly, Category = "Attributes|Vital", ReplicatedUsing = OnRep_DefensiveSynchrony)
		FGameplayAttributeData DefensiveSynchrony;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, DefensiveSynchrony);
	
		UPROPERTY(BlueprintReadOnly, Category = "Attributes|Vital", ReplicatedUsing = OnRep_BarrierMatrix)
		FGameplayAttributeData BarrierMatrix;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, BarrierMatrix);

	#pragma region Vital_OnReps
		UFUNCTION()
		void OnRep_VitalityMatrix(const FGameplayAttributeData& OldVM) const;
		UFUNCTION()
		void OnRep_EnergeticEndurance(const FGameplayAttributeData& OldEE) const;
		UFUNCTION()
		void OnRep_ArcaneReservoir(const FGameplayAttributeData& OldAR) const;
		UFUNCTION()
		void OnRep_DefensiveSynchrony(const FGameplayAttributeData& OldDS) const;
		UFUNCTION()
		void OnRep_BarrierMatrix(const FGameplayAttributeData& OldBM) const;
	#pragma endregion Vital_OnReps
#pragma endregion VitalAttributes

// Primary - Gameplay Attributes
#pragma region PrimaryAttributes
	#pragma region Stats
		UPROPERTY(BlueprintReadOnly, Category = "Attributes|Primary", ReplicatedUsing = OnRep_Physique)
		FGameplayAttributeData Physique;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, Physique);

		UPROPERTY(BlueprintReadOnly, Category = "Attributes|Primary", ReplicatedUsing = OnRep_Adaptivity)
		FGameplayAttributeData Adaptivity;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, Adaptivity);

		UPROPERTY(BlueprintReadOnly, Category = "Attributes|Primary", ReplicatedUsing = OnRep_NeuralAgility)
		FGameplayAttributeData NeuralAgility;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, NeuralAgility);

		UPROPERTY(BlueprintReadOnly, Category = "Attributes|Primary", ReplicatedUsing = OnRep_EmpathicResonance)
		FGameplayAttributeData EmpathicResonance;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, EmpathicResonance);

		UPROPERTY(BlueprintReadOnly, Category = "Attributes|Primary", ReplicatedUsing = OnRep_EssenceControl)
		FGameplayAttributeData EssenceControl;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, EssenceControl);

		UPROPERTY(BlueprintReadOnly, Category = "Attributes|Primary", ReplicatedUsing = OnRep_Nanomancy)
		FGameplayAttributeData Nanomancy;
		ATTRIBUTE_ACCESSORS(UECMAttributeSet, Nanomancy);
	#pragma endregion Stats
	
	#pragma region Priamry_OnReps
		// Vital - OnReps
		UFUNCTION()
		void OnRep_Physique(const FGameplayAttributeData& OldPhy) const;
		UFUNCTION()
		void OnRep_Adaptivity(const FGameplayAttributeData& OldAD) const;
		UFUNCTION()
		void OnRep_NeuralAgility(const FGameplayAttributeData& OldNA) const;
		UFUNCTION()
		void OnRep_EmpathicResonance(const FGameplayAttributeData& OldER) const;
		UFUNCTION()
		void OnRep_EssenceControl(const FGameplayAttributeData& OldEC) const;
		UFUNCTION()
		void OnRep_Nanomancy(const FGameplayAttributeData& OldNM) const;
	#pragma endregion Priamry_OnReps
#pragma endregion PrimaryAttributes

// Secondary - Gameplay Attributes
#pragma region SecondaryAttributes
	#pragma region Stats
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_VMCapacity)
	FGameplayAttributeData VMCapacity;
	ATTRIBUTE_ACCESSORS(UECMAttributeSet, VMCapacity);
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_VMRecovery)
	FGameplayAttributeData VMRecovery;
	ATTRIBUTE_ACCESSORS(UECMAttributeSet, VMRecovery);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_EECapacity)
	FGameplayAttributeData EECapacity;
	ATTRIBUTE_ACCESSORS(UECMAttributeSet, EECapacity);
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_EERecovery)
	FGameplayAttributeData EERecovery;
	ATTRIBUTE_ACCESSORS(UECMAttributeSet, EERecovery);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_ARCapacity)
	FGameplayAttributeData ARCapacity;
	ATTRIBUTE_ACCESSORS(UECMAttributeSet, ARCapacity);
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_ARRecovery)
	FGameplayAttributeData ARRecovery;
	ATTRIBUTE_ACCESSORS(UECMAttributeSet, ARRecovery);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_KineticAbsorption)
	FGameplayAttributeData KineticAbsorption;
	ATTRIBUTE_ACCESSORS(UECMAttributeSet, KineticAbsorption);
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_NanoshieldThreshold)
	FGameplayAttributeData NanoshieldThreshold;
	ATTRIBUTE_ACCESSORS(UECMAttributeSet, NanoshieldThreshold);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_ResonanceSyncQuality)
	FGameplayAttributeData ResonanceSyncQuality;
	ATTRIBUTE_ACCESSORS(UECMAttributeSet, ResonanceSyncQuality);
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_ResonanceAmplification)
	FGameplayAttributeData ResonanceAmplification;
	ATTRIBUTE_ACCESSORS(UECMAttributeSet, ResonanceAmplification);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_EmpathicInfluence)
	FGameplayAttributeData EmpathicInfluence;
	ATTRIBUTE_ACCESSORS(UECMAttributeSet, EmpathicInfluence);
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_TechnologicalInterface)
	FGameplayAttributeData TechnologicalInterface;
	ATTRIBUTE_ACCESSORS(UECMAttributeSet, TechnologicalInterface);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_SignalStealth)
	FGameplayAttributeData SignalStealth;
	ATTRIBUTE_ACCESSORS(UECMAttributeSet, SignalStealth);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_ReactionSpeed)
	FGameplayAttributeData ReactionSpeed;
	ATTRIBUTE_ACCESSORS(UECMAttributeSet, ReactionSpeed);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_DimensionalPocketCapacity)
	FGameplayAttributeData DimensionalPocketCapacity;
	ATTRIBUTE_ACCESSORS(UECMAttributeSet, DimensionalPocketCapacity);
#pragma endregion Stats
	
	#pragma region Secondary_OnReps
	// Vital - OnReps
	UFUNCTION()
	void OnRep_VMCapacity(const FGameplayAttributeData& OldVMC) const;
	UFUNCTION()
	void OnRep_VMRecovery(const FGameplayAttributeData& OldVMR) const;
	UFUNCTION()
	void OnRep_EECapacity(const FGameplayAttributeData& OldEEC) const;
	UFUNCTION()
	void OnRep_EERecovery(const FGameplayAttributeData& OldEER) const;
	UFUNCTION()
	void OnRep_ARCapacity(const FGameplayAttributeData& OldARC) const;
	UFUNCTION()
	void OnRep_ARRecovery(const FGameplayAttributeData& OldARR) const;
	UFUNCTION()
	void OnRep_KineticAbsorption(const FGameplayAttributeData& OldKA) const;
	UFUNCTION()
	void OnRep_NanoshieldThreshold(const FGameplayAttributeData& OldNST) const;
	UFUNCTION()
	void OnRep_ResonanceSyncQuality(const FGameplayAttributeData& OldRSQ) const;
	UFUNCTION()
	void OnRep_ResonanceAmplification(const FGameplayAttributeData& OldRA) const;
	UFUNCTION()
	void OnRep_EmpathicInfluence(const FGameplayAttributeData& OldEI) const;
	UFUNCTION()
	void OnRep_TechnologicalInterface(const FGameplayAttributeData& OldTI) const;
	UFUNCTION()
	void OnRep_SignalStealth(const FGameplayAttributeData& OldSS) const;
	UFUNCTION()
	void OnRep_ReactionSpeed(const FGameplayAttributeData& OldRS) const;
	UFUNCTION()
	void OnRep_DimensionalPocketCapacity(const FGameplayAttributeData& OldDPC) const;
	#pragma endregion Secondary_OnReps
#pragma endregion SecondaryAttributes

// Tertiary - Gameplay Attributes
#pragma region TertiaryAttributes
#pragma endregion TertiaryAttributes


// Meta - Gameplay Attributes
#pragma region MetaAttributes
	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UECMAttributeSet, IncomingDamage);



	
#pragma endregion MetaAttributes

	
private:
	static void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties &Props);

	// Container for Attribute Mappings
	static TArray<AttributeFunctionMappings> GetVitalValvesMappings();
	static TArray<AttributeFunctionMappings> GetPrimaryValvesMappings();

	// Maximum valve for Primary Attributes
	UPROPERTY(VisibleAnywhere,Category="Attributes")
	float MaxPrimaryAttribute = 20.f;
};
