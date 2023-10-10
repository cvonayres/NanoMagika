// Copyright Electronic CAD Monkey [ECM]

#include "ECMEnemy.h"

#include "Components/WidgetComponent.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemComponent.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemLibrary.h"
#include "NanoMagika/AbilitySystem/ECMAttributeSet.h"
#include "NanoMagika/UI/Widget/ECMUserWidget.h"

AECMEnemy::AECMEnemy()
{
	SetAbilitySystemComponent(CreateDefaultSubobject<UECMAbilitySystemComponent>("AbilitySystemComponent"));
	AECMCharacterBase::GetAbilitySystemComponent()->SetIsReplicated(true);
	AECMCharacterBase::GetAbilitySystemComponent()->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	SetAttributeSet(CreateDefaultSubobject<UECMAttributeSet>("AttributeSet"));

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void AECMEnemy::BeginPlay()
{
	Super::BeginPlay();

	// Initialise Actor Info & Default Tags
	InitializeCharacter();

	InitHealthBar();
}

void AECMEnemy::InitializeCharacter()
{
	// Set callbacks on ECM Ability System Component and native ASC
	InitAbilityActorInfo();
	
	// Initialise Default Gameplay tags
	InitDefaultGameplayTags();
	
	// Initialise Attributes
	InitDefaultAttributes();
}

void AECMEnemy::InitHealthBar()
{
	// Setting Widget Controller To Self
	if( UECMUserWidget* ECMUserWidget = Cast<UECMUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		ECMUserWidget->SetWidgetControllerRef(this);
	}
	
	if(const UECMAttributeSet* ECMAS = Cast<UECMAttributeSet>(GetAttributeSet()))
	{
		if(UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
		{
			// Bind Health and Max health changes
			ASC->GetGameplayAttributeValueChangeDelegate(ECMAS->GetVitalityMatrixAttribute()).AddLambda(
		[this](const FOnAttributeChangeData Data)
				{
					OnHealthChange.Broadcast(Data.NewValue);
				}
			);
			ASC->GetGameplayAttributeValueChangeDelegate(ECMAS->GetVMCapacityAttribute()).AddLambda(
		[this](const FOnAttributeChangeData Data)
				{
					OnMaxHealthChange.Broadcast(Data.NewValue);
				}
			);

		//Broadcast initial valves
		OnHealthChange.Broadcast(ECMAS->GetVitalityMatrix());
		OnMaxHealthChange.Broadcast(ECMAS->GetVMCapacity());
			
		}
	}
}

void AECMEnemy::InitDefaultAttributes() const
{
		UECMAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, GetAbilitySystemComponent());
}

