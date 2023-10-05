// Copyright Electronic CAD Monkey [ECM]

#include "ECMCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemComponent.h"
#include "Components/GameFrameworkComponentManager.h"

AECMCharacterBase::AECMCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AECMCharacterBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this); 	
}

// Empty function, called in child classes
void AECMCharacterBase::BeginPlay() { Super::BeginPlay(); }

void AECMCharacterBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);

	Super::EndPlay(EndPlayReason);
}

// Empty function, called in child classes
void AECMCharacterBase::InitializeCharacter() { }

// Sets ActorInfo for Ability System and bind call back for Gameplay Effects
void AECMCharacterBase::InitAbilityActorInfo() 
{
	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
	
	GetECMASC()->BindEffectApplied();
}

// Setup Default Attributes
void AECMCharacterBase::InitDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

// Add Default Gameplay Abilities
void AECMCharacterBase::InitDefaultAbilities() const
{
	if(!HasAuthority()) return;
	
	GetECMASC()->AddGameplayAbilities(DefaultCharacterAbilities);
}

// Add Default Gameplay Tags [loosely, i.e. with no ability]
void AECMCharacterBase::InitDefaultGameplayTags() const
{
	GetECMASC()->AddGameplayTags(DefaultCharacterTags);
}

// Generic Apply Effect To Self
void AECMCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);

	// Create Effect Spec Handle
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass,Level,ContextHandle);

	// Apply gameplay effect to Self
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(),AbilitySystemComponent);
}

// Helper function to Get ECM version of ASC, if not available cast from default ASC.
UECMAbilitySystemComponent* AECMCharacterBase::GetECMASC() const
{
	if(ECMAbilitySystemComponent) return ECMAbilitySystemComponent;

	return CastChecked<UECMAbilitySystemComponent>(GetAbilitySystemComponent());
}
