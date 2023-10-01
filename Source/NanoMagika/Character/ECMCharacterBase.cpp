// Copyright Electronic CAD Monkey [ECM]

#include "ECMCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "NanoMagika/ECMGameplayTags.h"
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

void AECMCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Empty function, called in child classes
void AECMCharacterBase::InitAbilityActorInfo()
{
}

// Setup Primary and Secondary Attributes
void AECMCharacterBase::InitDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

// Add Default Gameplay Tags [loosely, i.e. with no ability]

void AECMCharacterBase::InitDefaultTags(UAbilitySystemComponent* ASC, const TArray<FGameplayTag>& Tags)
{
	check(ASC);
	for (FGameplayTag Tag : Tags)
	{
		ASC->AddLooseGameplayTag(Tag);
	}
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

/* Hightlight Interface */
void AECMCharacterBase::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);

	// Blueprint implementable event
	Highlighted(true);
}
void AECMCharacterBase::UnHightlighActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);

	// Blueprint implementable event
	Highlighted(false);
}
/* end Hightlight Interface */

/* Ability System Interface */
UAbilitySystemComponent* AECMCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
/* end Ability System Interface */

/* Combat Interface */

/* end Combat Interface */
