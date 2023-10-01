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

	// Initialise Ability Actor Info
	InitAbilityActorInfo();

	// Add default Tags
	TArray<FGameplayTag> DefaultTags;
	DefaultTags.Add(FGameplayTag::RequestGameplayTag(FName("Character.Type.Enemy")));
	InitDefaultTags(AbilitySystemComponent, DefaultTags);
}

void AECMEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UECMAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}
