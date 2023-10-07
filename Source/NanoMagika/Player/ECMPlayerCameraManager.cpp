// Copyright Electronic CAD Monkey [ECM]

#include "ECMPlayerCameraManager.h"
#include "ECMPlayerController.h"
#include "NanoMagika/Character/ECMCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NanoMagika/Input/ECMInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

void AECMPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	PC = GetOwningPlayerController(); // Get Player Controller Reference

	AECMPlayerController* ECMPC = Cast<AECMPlayerController>(PC);
	ECMPC->OnActionBindingRequested.AddDynamic(this, &AECMPlayerCameraManager::BindActionToInput);
}

void AECMPlayerCameraManager::InitPCM(const TObjectPtr<USpringArmComponent> SpringArm,
                                      const TObjectPtr<UCameraComponent> Camera)
{
	PC = GetOwningPlayerController(); // Get Player Controller Reference
	if(PC == nullptr) return;

	AECMCharacter* Character = Cast<AECMCharacter>(PC->GetCharacter());
	if(Character == nullptr) return;

	InitCamera(SpringArm,Camera);
	InitCMC(Character);
}

void AECMPlayerCameraManager::BindActionToInput(UECMInputComponent* InputComponentRef)
{
	if(InputComponentRef == nullptr) return;
	
	InputComponentRef->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &AECMPlayerCameraManager::ZoomCamera);
}


void AECMPlayerCameraManager::InitCamera(const TObjectPtr<USpringArmComponent> SpringArm, const TObjectPtr<UCameraComponent> Camera)
{
	if(SpringArm != nullptr)
	{
		// Set spring arm properties if needed
		SpringArmComponent = SpringArm;
		SpringArmComponent->AddRelativeRotation(FRotator(-45.f,0.f,0.f));
		SpringArmComponent->TargetArmLength = ZoomDefault; 
		SpringArmComponent->bUsePawnControlRotation = false;
		SpringArmComponent->bInheritPitch = false;
		SpringArmComponent->bInheritRoll = false;
		SpringArmComponent->bInheritYaw = false;
		SpringArmComponent->bEnableCameraLag = true;
	}
	
	if(Camera != nullptr)
	{
		// Prevent the camera from rotating with the spring arm
		Camera->bUsePawnControlRotation = false;
	}
}

// ReSharper disable once CppMemberFunctionMayBeStatic - don't want it to be static
void AECMPlayerCameraManager::InitCMC(AECMCharacter* Character)
{
	if(Character == nullptr) return;
	
	Character->bUseControllerRotationPitch = false;
	Character->bUseControllerRotationRoll = false;
	Character->bUseControllerRotationYaw = false;
	
	if (UCharacterMovementComponent* CMC = Character->GetCharacterMovement())
	{
		CMC->bOrientRotationToMovement = true;
		CMC->RotationRate = FRotator(0.f, 400.f,0.f);
		CMC->bConstrainToPlane = true;
		CMC->bSnapToPlaneAtStart = true;
	}
}

void AECMPlayerCameraManager::BindInputs()
{
	if (PC == nullptr) return;
	const AECMPlayerController* ECMPC = Cast<AECMPlayerController>(PC);

	if (ECMPC == nullptr) return;
	UECMInputComponent* ECMInputComponent = ECMPC->GetInputComponent();

	if (ECMInputComponent == nullptr) return;
	ECMInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &AECMPlayerCameraManager::ZoomCamera);
}

// ReSharper disable once CppMemberFunctionMayBeConst - due to use in input binding.
void AECMPlayerCameraManager::ZoomCamera(const FInputActionValue& InputActionValve)
{
	if(SpringArmComponent == nullptr) return;
	
	const float InputAxisVector  = InputActionValve.Get<float>();

	SpringArmComponent->TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + (InputAxisVector * ZoomRate), ZoomMin, ZoomMax);
}
