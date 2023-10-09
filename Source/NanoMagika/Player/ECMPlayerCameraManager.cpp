// Copyright Electronic CAD Monkey [ECM]

#include "ECMPlayerCameraManager.h"
#include "ECMPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "NanoMagika/Input/ECMInputComponent.h"

void AECMPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	TryGetPawnAndController();
}

void AECMPlayerCameraManager::TryGetPawnAndController()
{
	if(PCOwner && PCOwner->GetPawn()) 
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_GetPawnAndController); // Clear Timer

		PlayerPawn = PCOwner->GetPawn(); // Store Pawn
		
		InitCamera(); // Initiate Camera Settings
		InitCMC(); // Initiate CharacterMovementComponent Settings
		BindInputs(); // Bind inputs for camera

	}
	else // Repeat until time limit
	{
		TimeElapsedTrying += CheckInterval; // Increment the elapsed time
        
		if(TimeElapsedTrying >= TimeLimitForCheck)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to get the PlayerController and Pawn in the allotted time."));
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle_GetPawnAndController);
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_GetPawnAndController, this, &AECMPlayerCameraManager::TryGetPawnAndController, CheckInterval, false);
		}
	}
}

void AECMPlayerCameraManager::InitCamera()
{
	if (PlayerPawn == nullptr) return;

	SpringArmComponent = PlayerPawn->FindComponentByClass<USpringArmComponent>();
	
	if(SpringArmComponent != nullptr)
	{
		// Set spring arm properties if needed
		SpringArmComponent->AddRelativeRotation(FRotator(-45.f,0.f,0.f));
		SpringArmComponent->TargetArmLength = ZoomDefault; 
		SpringArmComponent->bUsePawnControlRotation = false;
		SpringArmComponent->bInheritPitch = false;
		SpringArmComponent->bInheritRoll = false;
		SpringArmComponent->bInheritYaw = false;
		SpringArmComponent->bEnableCameraLag = true;
	}

	CameraComponent = PlayerPawn->FindComponentByClass<UCameraComponent>();
	
	if(CameraComponent != nullptr)
	{
		// Prevent the camera from rotating with the spring arm
		CameraComponent->bUsePawnControlRotation = false;
	}
}

void AECMPlayerCameraManager::InitCMC() const
{
	if (PlayerPawn == nullptr) return;

	ACharacter* Character = Cast<ACharacter>(PlayerPawn);
	if(Character)
	{
		Character->bUseControllerRotationPitch = false;
		Character->bUseControllerRotationRoll = false;
		Character->bUseControllerRotationYaw = false;
	}

	UCharacterMovementComponent* CharacterCMC = Character->GetCharacterMovement();
	
	if (CharacterCMC)
	{
		CharacterCMC->bOrientRotationToMovement = true;
		CharacterCMC->RotationRate = FRotator(0.f, 400.f,0.f);
		CharacterCMC->bConstrainToPlane = true;
		CharacterCMC->bSnapToPlaneAtStart = true;
	}
}

void AECMPlayerCameraManager::BindInputs()
{
	if (PCOwner == nullptr) return;

	if (AECMPlayerController* ECMPC = Cast<AECMPlayerController>(PCOwner))
	{
		if (UECMInputComponent* ECMInputComponent = ECMPC->GetInputComponent()
)
		{
			ECMInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &AECMPlayerCameraManager::ZoomCamera);
		}
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst - due to use in input binding.
void AECMPlayerCameraManager::ZoomCamera(const FInputActionValue& InputActionValve)
{
	if(SpringArmComponent == nullptr) return;
	
	const float InputAxisVector  = InputActionValve.Get<float>();

	SpringArmComponent->TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + (InputAxisVector * ZoomRate), ZoomMin, ZoomMax);
}
