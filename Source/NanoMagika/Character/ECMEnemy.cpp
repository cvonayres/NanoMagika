// Copyright Electronic CAD Monkey [ECM]

#include "ECMEnemy.h"

#include "NanoMagika/AbilitySystem/ECMAbilitySystemComponent.h"
#include "NanoMagika/AbilitySystem/ECMAttributeSet.h"

AECMEnemy::AECMEnemy()
{
	SetAbilitySystemComponent(CreateDefaultSubobject<UECMAbilitySystemComponent>("AbilitySystemComponent"));
	AECMCharacterBase::GetAbilitySystemComponent()->SetIsReplicated(true);
	AECMCharacterBase::GetAbilitySystemComponent()->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	SetAttributeSet(CreateDefaultSubobject<UECMAttributeSet>("AttributeSet"));

	NetUpdateFrequency = 100.f;
}

void AECMEnemy::BeginPlay()
{
	Super::BeginPlay();

	// Initialise Actor Info & Default Tags
	InitializeCharacter();
}

void AECMEnemy::InitializeCharacter()
{
	// Set callbacks on ECM Ability System Component and native ASC
	InitAbilityActorInfo();
	
	// Initialise Default Gameplay tags
	InitDefaultGameplayTags();
}


