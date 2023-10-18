// Copyright Electronic CAD Monkey [ECM]

#include "ECMEnemy.h"

#include "ECMCharacter.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NanoMagika/ECMGameplayTags.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemComponent.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemLibrary.h"
#include "NanoMagika/AbilitySystem/Attributes/ECMAttributeSet.h"
#include "NanoMagika/UI/Widget/ECMUserWidget.h"

AECMEnemy::AECMEnemy()
{
	SetAbilitySystemComponent(CreateDefaultSubobject<UECMAbilitySystemComponent>("AbilitySystemComponent"));
	AECMCharacterBase::GetAbilitySystemComponent()->SetIsReplicated(true);
	AECMCharacterBase::GetAbilitySystemComponent()->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UECMAttributeSet>("AttributeSet");
	
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void AECMEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeAbilityActorInfo();
	
	InitializeCharacter();	
}

void AECMEnemy::InitializeCharacter()
{
	if (HasAuthority())
	{
		Super::InitializeCharacter();
	}
	
	InitHealthBar(); // Health Bar
	
	if(GetAbilitySystemComponent()) // Hit React
	{
		GetAbilitySystemComponent()->RegisterGameplayTagEvent(FECMGameplayTags::Get().Effect_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
		this, &AECMEnemy::HitReactTagChanged);
	}
}

void AECMEnemy::InitDefaultAttributes()
{
	UECMAbilitySystemLibrary::InitializeEnemyAttributes(this, EnemyTag, Level, GetECMASC());
}
void AECMEnemy::InitDefaultAbilities()
{
	UECMAbilitySystemLibrary::InitializeEnemyAbilities(this, EnemyTag, Level, GetECMASC());
}
void AECMEnemy::InitDefaultGameplayTags()
{
	UECMAbilitySystemLibrary::InitializeEnemyTags(this, EnemyTag, GetECMASC());
}

void AECMEnemy::InitHealthBar()
{
	UECMUserWidget* ECMUserWidget = Cast<UECMUserWidget>(HealthBar->GetUserWidgetObject());
	if (ECMUserWidget == nullptr) return;

	ECMUserWidget->SetWidgetControllerRef(this); // Setting Widget Controller To Self


	auto  ECMAS = Cast<UECMAttributeSet>(GetAttributeSet());
	if (ECMAS == nullptr) return;

	// Bind Health and Max health changes
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(ECMAS->GetVitalityMatrixAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChange.Broadcast(Data.NewValue);
			});
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(ECMAS->GetVMCapacityAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChange.Broadcast(Data.NewValue);
			});

	//Broadcast initial valves
	OnHealthChange.Broadcast(ECMAS->GetVitalityMatrix());
	OnMaxHealthChange.Broadcast(ECMAS->GetVMCapacity());
}


void AECMEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;

	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f: DefaultWalkingSpeed;
}

void AECMEnemy::Die()
{
	SetLifeSpan(LifeSpan);
	
	Super::Die();
}
