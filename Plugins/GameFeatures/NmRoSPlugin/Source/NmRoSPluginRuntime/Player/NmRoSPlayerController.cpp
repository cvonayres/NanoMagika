// Copyright Electronic CAD Monkey [ECM]

#include "NmRoSPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Components/SplineComponent.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemComponent.h"
#include "NanoMagika/Input/ECMInputComponent.h"
#include "NmRoSPluginRuntime/Interaction/ECMHightlightInterface.h"

void ANmRoSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	InitMouse(); // Sort out input mode & mouse
	
	// Set up timer for cursor trace [default 0.1s looping]
	FTimerHandle TimerHandle = FTimerHandle();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ANmRoSPlayerController::CursorTrace, 0.1f, true);
}

#pragma region InputActions
// Set up input components
void ANmRoSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	check(ECMInputComponent);
	// Bind input action to movement
	ECMInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANmRoSPlayerController::Move);
	// Bind input actions via Gameplay Tags
	ECMInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

// ReSharper disable once CppMemberFunctionMayBeConst; const don't work with binding input
void ANmRoSPlayerController::Move(const FInputActionValue& InputActionValve)
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
#pragma endregion InputActions

// Cursor Trace
#pragma region CursorTrace
void ANmRoSPlayerController::CursorTrace()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if(!Hit.bBlockingHit) return;
	LastActor = ThisActor;

	if(TArray<UActorComponent*> TComponents = Hit.GetActor()->GetComponentsByInterface(UECMHightlightInterface::StaticClass()); TComponents.IsEmpty())
	{
		ThisActor = nullptr;
	}
	else
	{
		for (UActorComponent* Component : TComponents)
		{
			ThisActor = Cast<IECMHightlightInterface>(Component);
			break;
		}
	}

	if(LastActor != ThisActor)
	{
		if(LastActor) LastActor->UnHighlightActor();
		if(ThisActor) ThisActor->HighlightActor();
	}
}

void ANmRoSPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
}

void ANmRoSPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if(GetASC() == nullptr) return
	GetASC()->AbilityInputTagReleased(InputTag);
}

void ANmRoSPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if(GetASC() == nullptr)
	{
		return;
	}
	GetASC()->AbilityInputTagHeld(InputTag);
}
#pragma endregion CursorTrace

// Initialise Mouse
void ANmRoSPlayerController::InitMouse()
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
