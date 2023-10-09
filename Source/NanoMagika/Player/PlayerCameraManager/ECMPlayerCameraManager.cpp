// Copyright Electronic CAD Monkey [ECM]

#include "ECMPlayerCameraManager.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "NanoMagika/Input/ECMInputComponent.h"
#include "NanoMagika/Player/PlayerController/ECMPlayerController.h"


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

		// Set Camera Mode Settings
		if(StartingCameraMode == EStartingCameraMode::FirstPersonView){ FirstPersonViewMode(); }
		if(StartingCameraMode == EStartingCameraMode::ThirdPersonView){ ThirdPersonViewMode(); }
		if(StartingCameraMode == EStartingCameraMode::TopDownView){ TopDownViewMode(); }
		
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

void AECMPlayerCameraManager::UpdateCameraMode(const UDA_CameraMode* CameraMode)
{
	check(CameraMode);
	
	if(GetSpringArm()) // Set spring arm properties from Data Asset
	{
		SpringArmComponent->SetRelativeLocation(CameraMode->CameraSettings.Location);
		SpringArmComponent->SetRelativeRotation(CameraMode->CameraSettings.Rotation);
		SpringArmComponent->TargetArmLength = CameraMode->CameraSettings.TargetArmLength; 
		SpringArmComponent->bUsePawnControlRotation = CameraMode->CameraSettings.SpringArmUsePawnControlRotation;
		SpringArmComponent->bInheritPitch = CameraMode->CameraSettings.InheritPitch;
		SpringArmComponent->bInheritRoll = CameraMode->CameraSettings.InheritRoll;
		SpringArmComponent->bInheritYaw = CameraMode->CameraSettings.InheritYaw;
		SpringArmComponent->bEnableCameraLag = CameraMode->CameraSettings.EnableCameraLag;
	}
	
	if(GetCamera()) // Set camera properties from Data Asset
	{
		CameraComponent->bUsePawnControlRotation = CameraMode->CameraSettings.CameraUsePawnControlRotation; // Prevent the camera from rotating with the spring arm	}
	}

	if(GetCharacter()) // Set Character properties from Data Asset
	{
		Character->bUseControllerRotationPitch = CameraMode->CameraSettings.UseControllerRotationPitch;
		Character->bUseControllerRotationRoll = CameraMode->CameraSettings.UseControllerRotationRoll;
		Character->bUseControllerRotationYaw = CameraMode->CameraSettings.UseControllerRotationYaw;	
	}

	if(GetCharacterMovementComponent()) // Set Character Movement Component properties from Data Asset
	{
		CharacterCMC->bOrientRotationToMovement = CameraMode->CameraSettings.bOrientRotationToMovement;
		CharacterCMC->RotationRate = CameraMode->CameraSettings.RotationRate;
		CharacterCMC->bConstrainToPlane = CameraMode->CameraSettings.ConstrainToPlane;
		CharacterCMC->bSnapToPlaneAtStart = CameraMode->CameraSettings.SnapToPlaneAtStart;
	}
}

// Bind Enhanced Inputs
void AECMPlayerCameraManager::BindInputs()
{
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

// Helper Functions
bool AECMPlayerCameraManager::GetSpringArm()
{
	if(SpringArmComponent) return true;

	SpringArmComponent = PlayerPawn->FindComponentByClass<USpringArmComponent>();

	return (SpringArmComponent != nullptr);
}
bool AECMPlayerCameraManager::GetCamera()
{
	if(CameraComponent) return true;

	CameraComponent = PlayerPawn->FindComponentByClass<UCameraComponent>();
	
	return (CameraComponent != nullptr);

}
bool AECMPlayerCameraManager::GetCharacter()
{
	if(Character) return true;

	Character = Cast<ACharacter>(PlayerPawn);

	return (Character != nullptr);
}
bool AECMPlayerCameraManager::GetCharacterMovementComponent()
{
	if(CharacterCMC) return true;

	check(Character);
	
	CharacterCMC = Character->GetCharacterMovement();

	return (CharacterCMC != nullptr);
}
