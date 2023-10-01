// Copyright Electronic CAD Monkey [ECM]

#include "ECMEnemy.h"

#include "NanoMagika/AbilitySystem/ECMAbilitySystemComponent.h"
#include "NanoMagika/AbilitySystem/ECMAttributeSet.h"

AECMEnemy::AECMEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UECMAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UECMAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

void AECMEnemy::BeginPlay()
{
	Super::BeginPlay();

	// Initialise Actor Info & Default Tags
	InitAbilityActorInfo();
	InitDefaultGameplayTags();
}

void AECMEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UECMAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}
