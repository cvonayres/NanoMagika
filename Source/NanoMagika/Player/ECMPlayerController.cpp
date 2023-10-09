// Copyright Electronic CAD Monkey [ECM]

#include "ECMPlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/GameFrameworkComponentManager.h"
#include "EnhancedInputSubsystems.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemComponent.h"
#include "NanoMagika/Input/ECMInputComponent.h"

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

// Helper function to Get ECM Ability System Component
UECMAbilitySystemComponent* AECMPlayerController::GetASC()
{
	if(ECMAbilitySystemComponent == nullptr)
	{
		ECMAbilitySystemComponent= Cast<UECMAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return ECMAbilitySystemComponent;
}
