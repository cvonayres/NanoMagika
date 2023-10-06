// Copyright Electronic CAD Monkey [ECM]

#include "ECMPlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/GameFrameworkComponentManager.h"
#include "EnhancedInputSubsystems.h"
#include "NanoMagika/Input/ECMInputComponent.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemComponent.h"

AECMPlayerController::AECMPlayerController() { bReplicates = true; }

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
	
	InitMouse(); // Sort out input mode & mouse

	// Set up timer for cursor trace [default 0.1s looping]
	FTimerHandle TimerHandle = FTimerHandle();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AECMPlayerController::CursorTrace, 0.1f, true);
}

// Remove from modular game framework manager
void AECMPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);

	Super::EndPlay(EndPlayReason);
}

// Cursor Trace on Tick, multicast hit result
void AECMPlayerController::CursorTrace() const
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if(Hit.bBlockingHit)
	{
		CursorHitEvent.Broadcast(Hit);
		//GEngine->AddOnScreenDebugMessage(2,1,FColor::Red, FString::Printf(TEXT("%s"), *Hit.GetActor()->GetActorNameOrLabel()));
	}
}

// Cast Input Component and bind Input Actions
void AECMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	ECMInputComponent = CastChecked<UECMInputComponent>(InputComponent);

	// Bind input actions via Gameplay Tags
	ECMInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);

	// TODO move to ability actions
	ECMInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AECMPlayerController::Move);
}

// Call function on ASC when bound input actions are used
void AECMPlayerController::AbilityInputTagPressed(const FGameplayTag InputTag)
{
	// GEngine->AddOnScreenDebugMessage(1,3,FColor::Red, *InputTag.ToString());
}
void AECMPlayerController::AbilityInputTagReleased(const FGameplayTag InputTag)
{
	if(GetASC() == nullptr) return
	GetASC()->AbilityInputTagReleased(InputTag);
	// GEngine->AddOnScreenDebugMessage(2,3,FColor::Blue, *InputTag.ToString());
}
void AECMPlayerController::AbilityInputTagHeld(const FGameplayTag InputTag)
{
	if(GetASC() == nullptr)
	{
		return;
	}
	GetASC()->AbilityInputTagHeld(InputTag);
	// GEngine->AddOnScreenDebugMessage(3,3,FColor::Green, *InputTag.ToString());
}

// ReSharper disable once CppMemberFunctionMayBeConst - due to bound to input action.
void AECMPlayerController::Move(const FInputActionValue& InputActionValve)
{
	const FVector2d InputAxisVector = InputActionValve.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation (0.f, Rotation.Yaw, 0.f);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}

// Initialise Input mode and mouse
void AECMPlayerController::InitMouse()
{	
	// Setup Input Mode 
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

	// Setup cursor
	bShowMouseCursor=true;
	DefaultMouseCursor = EMouseCursor::Default;
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
