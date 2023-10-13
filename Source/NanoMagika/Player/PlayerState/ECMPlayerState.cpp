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
}

UAbilitySystemComponent* AECMPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AECMPlayerState::OnRep_Level(int32 oldLevel)
{
	
}
