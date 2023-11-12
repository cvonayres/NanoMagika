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
	SetAbilitySystemComponent(CreateDefaultSubobject<UECMAbilitySystemComponent>("AbilitySystemComponent"));
	AECMCharacterBase::GetAbilitySystemComponent()->SetIsReplicated(true);
	AECMCharacterBase::GetAbilitySystemComponent()->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UECMAttributeSet>("AttributeSet");
	
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());

	GetCharacterMovement()->bUseControllerDesiredRotation;
	GetCharacterMovement()->RotationRate = FRotator(0,360,0);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

// Server side ready
void AECMEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(!HasAuthority()) return; // Only on server
	AIController = Cast<AECMAIController>(NewController);
	
	BlackboardComponentRef = AIController->GetBlackboardComponent();
	check(BlackboardComponentRef);
	BlackboardComponentRef->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	AIController->RunBehaviorTree(BehaviorTree);

	ClassInfo = UECMAbilitySystemLibrary::GetCharacterClassInfo(this);
	if(ClassInfo == nullptr ) return;
	
	ClassSpec =  UECMAbilitySystemLibrary::GetClassDefaultInfo(ClassInfo, EnemyTag);
	if(ClassSpec == nullptr ) return;
	
	InitializeAbilityActorInfo();
	
	InitializeCharacter();	

}

// Client side ready
void AECMEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	ClassInfo = UECMAbilitySystemLibrary::GetCharacterClassInfo(this);
	if(ClassInfo == nullptr ) return;
	
	ClassSpec =  UECMAbilitySystemLibrary::GetClassDefaultInfo(ClassInfo, EnemyTag);
	if(ClassSpec == nullptr ) return;
	
	InitializeAbilityActorInfo();
	
	InitializeCharacter();	
}

void AECMEnemy::InitializeCharacter()
{
	Super::InitializeCharacter();

	InitHealthBar(); // Health Bar
	
	if( GetAbilitySystemComponent() ) // Hit React
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

void AECMEnemy::InitHealthBar()
{
	auto* WidgetObject = HealthBar->GetUserWidgetObject();
	UECMUserWidget* ECMUserWidget = Cast<UECMUserWidget>(WidgetObject);
	if (ECMUserWidget )
	{
		ECMUserWidget->SetWidgetControllerRef(this); // Setting Widget Controller To Self
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
