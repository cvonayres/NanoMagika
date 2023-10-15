// Copyright Electronic CAD Monkey [ECM]

#include "ECMPlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/GameFrameworkComponentManager.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemComponent.h"
#include "NanoMagika/Input/ECMInputComponent.h"
#include "NanoMagika/UI/Widget/ECMDamageTextComponent.h"

AECMPlayerController::AECMPlayerController()
{
	bReplicates = true;
}

// Register to modular game framework manager
void AECMPlayerController::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	
	UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this); 	
}

void AECMPlayerController::ShowDamageNumber_Implementation(float Damage, ACharacter* TargetCharacter)
{
	if (IsValid(TargetCharacter) && DamageTextComponentClass)
	{
		// Create
		UECMDamageTextComponent* DamageText = NewObject<UECMDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent();
		// Set location to target at spawn then detach
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		// Set damage text
		DamageText->SetDamageText(Damage);
	}
}

void AECMPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	check(InputContext);
	if(UEnhancedInputLocalPlayerSubsystem*  Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputContext,0);
	}
}

// Remove from modular game framework manager
void AECMPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);

	Super::EndPlay(EndPlayReason);
}

// Cast Input Component and bind Input Actions
void AECMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	ECMInputComponent = CastChecked<UECMInputComponent>(InputComponent);
}


void AECMPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	// GEngine->AddOnScreenDebugMessage(1,3,FColor::Red, *InputTag.ToString());
}

void AECMPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	// GEngine->AddOnScreenDebugMessage(2,3,FColor::Blue, *InputTag.ToString());
}

void AECMPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	// GEngine->AddOnScreenDebugMessage(3,3,FColor::Green, *InputTag.ToString());
}

// Helper functions
bool AECMPlayerController::GetECMCharacterASC()
{
	if(ECMCharacterASC) return true;
	
	ECMCharacterASC = Cast<UECMAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	
	return (ECMCharacterASC != nullptr);
}
bool AECMPlayerController::CheckCameraMode(FName TagName)
{
	if(!GetECMCharacterASC()) { return false; }
	
	const FGameplayTag Tag = FGameplayTag::RequestGameplayTag(TagName);
	return (ECMCharacterASC->HasMatchingGameplayTag(Tag));
}
