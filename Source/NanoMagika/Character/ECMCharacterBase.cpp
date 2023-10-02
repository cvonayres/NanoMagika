// Copyright Electronic CAD Monkey [ECM]

#include "ECMCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "NanoMagika/NanoMagika.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemComponent.h"

AECMCharacterBase::AECMCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);	

	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

// Empty function, called in child classes
void AECMCharacterBase::BeginPlay() { Super::BeginPlay(); }

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

// Helper function to Get ECM version of ASC, if no avable cast from default ASC.
UECMAbilitySystemComponent* AECMCharacterBase::GetECMASC() const
{
	if(ECMAbilitySystemComponent) return ECMAbilitySystemComponent;

	return CastChecked<UECMAbilitySystemComponent>(GetAbilitySystemComponent());
}

/* Highlight Interface */
void AECMCharacterBase::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
}
void AECMCharacterBase::UnHighlighActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}
/* end Highlight Interface */

/* Ability System Interface */
/* end Ability System Interface */

/* Combat Interface */
/* end Combat Interface */
