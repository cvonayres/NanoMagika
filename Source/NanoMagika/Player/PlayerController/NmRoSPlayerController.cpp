// Copyright Electronic CAD Monkey [ECM]

#include "NmRoSPlayerController.h"
#include "EnhancedInputComponent.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Components/SplineComponent.h"
#include "NanoMagika/ECMGameplayTags.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemComponent.h"
#include "NanoMagika/Input/ECMInputComponent.h"
#include "NanoMagika/Interaction/ECMHightlightInterface.h"

ANmRoSPlayerController::ANmRoSPlayerController()
{
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void ANmRoSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	InitMouse(); // Sort out input mode & mouse
	
	// Set up timer for cursor trace [default 0.1s looping]
	FTimerHandle TimerHandle = FTimerHandle();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ANmRoSPlayerController::CursorTrace, 0.1f, true);
}

void ANmRoSPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(bAutoRunning) AutoRun();
}

#pragma region InputActions
// Set up input components
void ANmRoSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	check(ECMInputComponent);
	// Bind input actions via Gameplay Tags
	ECMInputComponent->BindActionsToTags_3Param(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
	// Bind input actions
	ECMInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANmRoSPlayerController::Move);
	ECMInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANmRoSPlayerController::Look);

	ECMInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &ANmRoSPlayerController::ShiftPressed);
	ECMInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &ANmRoSPlayerController::ShiftReleased);
}

// ReSharper disable once CppMemberFunctionMayBeConst; const don't work with binding input
void ANmRoSPlayerController::Move(const FInputActionValue& InputActionValve)
{
	// input is a Vector2D
	const FVector2D MovementVector = InputActionValve.Get<FVector2D>();

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		// add movement 
		ControlledPawn->AddMovementInput(ControlledPawn->GetActorForwardVector(), MovementVector.Y);
		ControlledPawn->AddMovementInput(ControlledPawn->GetActorRightVector(), MovementVector.X);
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst; const don't work with binding input
void ANmRoSPlayerController::Look(const FInputActionValue& InputActionValve)
{
	if(CheckCameraMode("Player.CameraMode.TDV")){ return; } // If in Top down view, get out.

	// input is a Vector2D
	const FVector2D LookAxisVector = InputActionValve.Get<FVector2D>();

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		// add yaw and pitch input to controller
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
		ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ANmRoSPlayerController::AutoRun()
{
	if(APawn* ControlledPawn = GetPawn())
	{
		const FVector PawnLocation = GetPawn()->GetActorLocation();
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(PawnLocation, ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(PawnLocation, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius) bAutoRunning = false;
	}
}
#pragma endregion InputActions

// Cursor Trace
#pragma region CursorTrace
void ANmRoSPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if(!CursorHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	if(TArray<UActorComponent*> TComponents = CursorHit.GetActor()->GetComponentsByInterface(UECMHightlightInterface::StaticClass()); TComponents.IsEmpty())
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
	if(InputTag.MatchesTagExact(FECMGameplayTags::Get().Input_Mouse_LMB))
	{
		bTargeting = ThisActor ? true : false; // Valid pointer = true, null pointer = false
		bAutoRunning = false;
	}
}

void ANmRoSPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if(GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
	
	if(!InputTag.MatchesTagExact(FECMGameplayTags::Get().Input_Mouse_LMB))	{ return; }

	if(!bTargeting && !bShiftKeyDown)  // Move to button pressed
	{
		CheckClickToMovePressed();
	}
}

void ANmRoSPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if(!InputTag.MatchesTagExact(FECMGameplayTags::Get().Input_Mouse_LMB))
	{
		if(GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
		return;
	}
	
	if(bTargeting || bShiftKeyDown)
	{
		if(GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
	}
	else // Move to held button
	{
		CheckClickToMoveHeld();
	}	
}

void ANmRoSPlayerController::CheckClickToMovePressed()
{
	if(!CheckCameraMode("Player.CameraMode.TDV")){ return; } // If not in Top down view, get out.

	const APawn* ControlledPawn = GetPawn();
	if(FollowTime <= ShortPressThreshold && ControlledPawn)
	{
		if(UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
		{
			Spline->ClearSplinePoints();
			for(const FVector PointLoc : NavPath->PathPoints)
			{
				Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
			}
			CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num()-1];
			bAutoRunning = true;
		}
	}
	FollowTime = 0.f;
	bTargeting = false;
}

void ANmRoSPlayerController::CheckClickToMoveHeld()
{
	if(!CheckCameraMode("Player.CameraMode.TDV")){ return; } // If not in Top down view, get out.
		
	FollowTime += GetWorld()->GetDeltaSeconds();
	if (CursorHit.bBlockingHit) CachedDestination = CursorHit.ImpactPoint;

	if(APawn* ControlledPawn = GetPawn())
	{
		const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection);
	}
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


bool ANmRoSPlayerController::CheckCameraMode(FName TagName)
{
	const FGameplayTag Tag = FGameplayTag::RequestGameplayTag(TagName);
	return (GetViewMode() == Tag);
}
