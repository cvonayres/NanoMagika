// Copyright Electronic CAD Monkey [ECM]

#include "ECMPlayerController.h"
#include "ECMPlayerCameraManager.h"
#include "EnhancedInputSubsystems.h"
#include  "EnhancedInputComponent.h"
#include "Components/GameFrameworkComponentManager.h"

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

	// Setup Input Mode 
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

	// Setup cursor
	bShowMouseCursor=true;
	DefaultMouseCursor = EMouseCursor::Default;

	CameraManager =  Cast<AECMPlayerCameraManager>(PlayerCameraManager);
	CameraManager->InitCamera();

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

// Cast InputComponent and bind Input Actions
void AECMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AECMPlayerController::Move);
	EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &AECMPlayerController::ZoomCamera);
}

// Move Function
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

// Zoom Camera
void AECMPlayerController::ZoomCamera(const FInputActionValue& InputActionValve)
{
	CameraManager->UpdateZoom(InputActionValve.Get<float>());
}


