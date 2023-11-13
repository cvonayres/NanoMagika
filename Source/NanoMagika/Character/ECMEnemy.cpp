// Copyright Electronic CAD Monkey [ECM]

#include "ECMEnemy.h"

#include "ECMCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NanoMagika/ECMGameplayTags.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemComponent.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemLibrary.h"
#include "NanoMagika/AbilitySystem/Attributes/ECMAttributeSet.h"
#include "NanoMagika/AbilitySystem/Data/ECMEnemySpecInfo.h"
#include "NanoMagika/AI/ECMAIController.h"
#include "NanoMagika/UI/Widget/ECMUserWidget.h"

// TODO BUG 1) Healthbar not changing on client
// TODO BUG 1) Ememy not reacting to character on client

AECMEnemy::AECMEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bUseControllerDesiredRotation;
	
	AbilitySystemComponent = CreateDefaultSubobject<UECMAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UECMAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

// Server side ready
void AECMEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if(!HasAuthority()) return; // Only on server
	AIController = Cast<AECMAIController>(NewController);
	AIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	AIController->RunBehaviorTree(BehaviorTree);
}

void AECMEnemy::BeginPlay()
{
	Super::BeginPlay();

	ClassInfo = UECMAbilitySystemLibrary::GetCharacterClassInfo(this);
	if (ClassInfo && EnemyTag.IsValid() )
	{
		ClassSpec =  UECMAbilitySystemLibrary::GetClassDefaultInfo(ClassInfo, EnemyTag);
	}
	if (ClassSpec == nullptr) return;
	
	InitializeCharacter();
	
	InitHealthBar_Implementation();
}

void AECMEnemy::InitializeCharacter()
{
	InitializeAbilityActorInfo();
	
	Cast<UECMAbilitySystemComponent>(AbilitySystemComponent)->BindEffectApplied();

	if (HasAuthority())
	{
		InitDefaultAttributes();
		InitDefaultAbilities();
		InitDefaultGameplayTags();
	}
	
	if( GetAbilitySystemComponent() ) // Bind for hit react
	{
		GetAbilitySystemComponent()->RegisterGameplayTagEvent(FECMGameplayTags::Get().Effect_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
		this, &AECMEnemy::HitReactTagChanged);
	}
}

void AECMEnemy::InitDefaultAttributes()
{
	UECMAbilitySystemLibrary::InitializeEnemyAttributes(this, EnemyTag, Level, GetECMASC());

	checkf(ClassSpec, TEXT("Class not found for enemy"));
	GetCharacterMovement()->MaxWalkSpeed = ClassSpec->DefaultWalkingSpeed;
}
void AECMEnemy::InitDefaultAbilities()
{
	UECMAbilitySystemLibrary::InitializeEnemyAbilities(this, EnemyTag, GetECMASC());
}
void AECMEnemy::InitDefaultGameplayTags()
{
	UECMAbilitySystemLibrary::InitializeEnemyTags(this, EnemyTag, GetECMASC());
}

void AECMEnemy::InitHealthBar_Implementation()
{
	if (UECMUserWidget* AuraUserWidget = Cast<UECMUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		AuraUserWidget->SetWidgetControllerRef(this);
	}
	
	if (const UECMAttributeSet* ECMAS = Cast<UECMAttributeSet>(GetAttributeSet()) )
	{
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
}

void AECMEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, const int32 NewCount)
{
	bHitReacting = NewCount > 0;

	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f: ClassSpec->DefaultWalkingSpeed;
}

void AECMEnemy::Die()
{
	SetLifeSpan(ClassInfo->LifeSpan);
	if ( BlackboardComponentRef ) BlackboardComponentRef->SetValueAsBool(FName("IsDead"), true);
	
	Super::Die();
}
