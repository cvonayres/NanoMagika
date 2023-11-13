// Copyright Electronic CAD Monkey [ECM]

#include "ECMPlayerState.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemComponent.h"
#include "NanoMagika/AbilitySystem/Attributes/ECMAttributeSet.h"
#include "Net/UnrealNetwork.h"

AECMPlayerState::AECMPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UECMAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	// Validate the AttributeSetClass before creating an object of its type.
	AttributeSet = CreateDefaultSubobject<UECMAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

// Replicates old Level
void AECMPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AECMPlayerState, Level);
	DOREPLIFETIME(AECMPlayerState, XP);
}

UAbilitySystemComponent* AECMPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

#pragma region AddToStats
void AECMPlayerState::AddToLevel(int32 InLevel)
{
	Level += InLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void AECMPlayerState::AddToXP(int32 InXP)
{
	XP += InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AECMPlayerState::AddToAttributePoints(int32 InAttributePoints)
{
	AttributePoints += InAttributePoints;
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AECMPlayerState::AddToAbilityPoints(int32 InAbilityPoints)
{
	AbilityPoints += InAbilityPoints;
	OnXPChangedDelegate.Broadcast(AbilityPoints);
}
#pragma endregion AddToStats

#pragma region SetToStats
void AECMPlayerState::SetLevel(int32 InLevel)
{
	Level = InLevel;
	OnAbilityPointsChangedDelegate.Broadcast(AbilityPoints);
}

void AECMPlayerState::SetXP(int32 InXP)
{
	XP = InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AECMPlayerState::SetAttributePoints(int32 InAttributePoints)
{
	AttributePoints = InAttributePoints;
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AECMPlayerState::SetAbilityPoints(int32 InAbilityPoints)
{
	AbilityPoints = InAbilityPoints;
	OnAbilityPointsChangedDelegate.Broadcast(AbilityPoints);
}
#pragma endregion SetToStats

#pragma region OnRep_Stats
void AECMPlayerState::OnRep_Level(int32 oldLevel)
{
	OnLevelChangedDelegate.Broadcast(Level);
}

void AECMPlayerState::OnRep_XP(int32 oldXP)
{
	OnXPChangedDelegate.Broadcast(XP);
}

void AECMPlayerState::OnRep_AttributePoints(int32 oldAttPoints)
{
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AECMPlayerState::OnRep_AbilityPoints(int32 oldAbilityPoints)
{
	OnAbilityPointsChangedDelegate.Broadcast(AbilityPoints);
}
#pragma endregion OnRep_Stats
