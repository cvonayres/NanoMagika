// Copyright Electronic CAD Monkey [ECM]

#include "ECMCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/GameFrameworkComponentManager.h"
#include "NanoMagika/ECMGameplayTags.h"
#include "NanoMagika/NanoMagika.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemComponent.h"

AECMCharacterBase::AECMCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	NetUpdateFrequency = 100.f;
}

void AECMCharacterBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this); 	
}

void AECMCharacterBase::BeginPlay() { Super::BeginPlay(); }

// Set callbacks on ECM Ability System Component and native ASC
void AECMCharacterBase::InitializeAbilityActorInfo()
{
	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
}

// Initialise Default Attributes, Abilities and Gameplay tags
void AECMCharacterBase::InitializeCharacter()
{
	if (HasAuthority())	{
		
		GetECMASC()->BindEffectApplied();

		InitDefaultAttributes();
		InitDefaultAbilities();
	}
	
	InitDefaultGameplayTags();
}

void AECMCharacterBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);

	Super::EndPlay(EndPlayReason);
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

//TODO check if needed
// Helper function to Get ECM version of ASC & AS, if not available cast from default ASC.
UECMAbilitySystemComponent* AECMCharacterBase::GetECMASC() const
{
	if(ECMAbilitySystemComponent) return ECMAbilitySystemComponent;
	return CastChecked<UECMAbilitySystemComponent>(GetAbilitySystemComponent());
}

// Helper function to Get Socket Location on weapon to spawn projectiles from
FVector AECMCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	FVector Location = FVector::Zero();
	const FECMGameplayTags& GameplayTags = FECMGameplayTags::Get();
    
	if (MontageTag == GameplayTags.Montage_Attack_Weapon && IsValid(Weapon))
	{
		Location = Weapon->GetSocketLocation(WeaponTipSocketName);
	}
	else if (MontageTag == GameplayTags.Montage_Attack_RightHand)
	{
		Location = GetMesh()->GetSocketLocation(RightHandSocketName);
	}
	else if (MontageTag == GameplayTags.Montage_Attack_LeftHand)
	{
		Location = GetMesh()->GetSocketLocation(LeftHandSocketName);
	}
	
	return Location;
}

// Could replace with a die ability and play a montage [see hit react]
void AECMCharacterBase::Die() // Server Side only
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true)); // Drop weapon
	MulticastHandleDeath(); // RPC call for clients
}

// Ragdoll
void AECMCharacterBase::MulticastHandleDeath_Implementation()
{
	for (TArray<USkeletalMeshComponent*> SkMeshes = { GetMesh(), Weapon }; USkeletalMeshComponent* SkMesh : SkMeshes)
	{
		SkMesh->SetSimulatePhysics(true);
		SkMesh->SetEnableGravity(true);
		SkMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		SkMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	}

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Dissolve();
	
	bIsDead = true;
}

void AECMCharacterBase::Dissolve()
{
	UMaterialInstanceDynamic* DynamicMatInst = nullptr;
	UMaterialInstanceDynamic* WeaponDynamicMatInst = nullptr;
	if(IsValid(DissolveMaterialInstance))
	{
		DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, DynamicMatInst);
	};
	if (IsValid(WeaponDissolveMaterialInstance))
	{
		WeaponDynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
		Weapon->SetMaterial(0, WeaponDynamicMatInst);
	}
	if (DynamicMatInst != nullptr || WeaponDynamicMatInst != nullptr )
	{
		StartDissolveTimeline(DynamicMatInst, WeaponDynamicMatInst);
	}
}


void AECMCharacterBase::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	if (const UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
	{
		ASC->GetOwnedGameplayTags(TagContainer);
	}
}

bool AECMCharacterBase::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	if (const UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
	{
		return ASC->HasMatchingGameplayTag(TagToCheck);
	}

	return false;
}

bool AECMCharacterBase::HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	if (const UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
	{
		return ASC->HasAllMatchingGameplayTags(TagContainer);
	}

	return false;
}

bool AECMCharacterBase::HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	if (const UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
	{
		return ASC->HasAnyMatchingGameplayTags(TagContainer);
	}

	return false;
}

