// Copyright Electronic CAD Monkey [ECM]

#include "ECMCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/GameFrameworkComponentManager.h"
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
	GetECMASC()->BindEffectApplied();

	InitDefaultAttributes();
	InitDefaultAbilities();
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

// Helper function to Get ECM version of ASC & AS, if not available cast from default ASC.
UECMAbilitySystemComponent* AECMCharacterBase::GetECMASC() const
{
	if(ECMAbilitySystemComponent) return ECMAbilitySystemComponent;
	return CastChecked<UECMAbilitySystemComponent>(GetAbilitySystemComponent());
}

// Helper function to Get Socket Location on weapon to spawn projectiles from
FVector AECMCharacterBase::GetCombatSocketLocation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
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
}

void AECMCharacterBase::Dissolve()
{
	if(IsValid(DissolveMaterialInstance) && IsValid(WeaponDissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, DynamicMatInst);

		UMaterialInstanceDynamic* WeaponDynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
		Weapon->SetMaterial(0, WeaponDynamicMatInst);

		StartDissolveTimeline(DynamicMatInst, WeaponDynamicMatInst);
	}
}
