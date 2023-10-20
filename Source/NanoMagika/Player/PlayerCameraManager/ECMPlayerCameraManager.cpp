// Copyright Electronic CAD Monkey [ECM]

#include "ECMPlayerCameraManager.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemLibrary.h"
#include "NanoMagika/Input/ECMInputComponent.h"
#include "NanoMagika/Player/PlayerController/ECMPlayerController.h"

// Tries to Get Pawn and Controller - will repeat until time limit is reached
void AECMPlayerCameraManager::InitPCM(const ACharacter* Character)
{
	if(! Character->IsLocallyControlled() ) return;

	CharacterRef = const_cast<ACharacter*>(Character);
	
	checkf(CharacterRef, TEXT("Character const cast failed"));
	
	StartingViewMode(); // Update setting with ViewMode from Tag in Player Character
	
	BindInputs(); // Bind inputs for this class
}

// Call Specific View Mode dependent on Character Starting Tag
void AECMPlayerCameraManager::StartingViewMode()
{
	if( !UECMAbilitySystemLibrary::ActorHasASC(CharacterRef) ) return;

	if (UECMAbilitySystemLibrary::ActorASCContainsTag(CharacterRef, CameraLookUpTags.PlayerTag_FPV))
	{
		UpdateCameraModeCPP(FPV_Settings);
	}
	else if (UECMAbilitySystemLibrary::ActorASCContainsTag(CharacterRef, CameraLookUpTags.PlayerTag_TPV))
	{
		UpdateCameraModeCPP(FPV_Settings);
	}
	else if (UECMAbilitySystemLibrary::ActorASCContainsTag(CharacterRef, CameraLookUpTags.PlayerTag_TDV))
	{
		UpdateCameraModeCPP(TDV_Settings);
	}
	else {	UE_LOG(LogTemp, Warning, TEXT("Player CameraMode Tag not found, check initial character tag includes CameraMode FPV,TPV or TDV")) }
}

// Call Update Camera Mode passing in right Data Asset and swaps the tags on Character.CameraMode
void AECMPlayerCameraManager::UpdateCameraMode(UDA_CameraMode* CameraModeDA)
{
	if (UECMAbilitySystemLibrary::ActorASCContainsTag(CharacterRef, CameraModeDA->CameraSettings.GameplayTag) ) {	return;	} 
	
	UECMAbilitySystemLibrary::AddTagToActor(CharacterRef, CameraModeDA->CameraSettings.GameplayTag);
	UECMAbilitySystemLibrary::RemoveTagFromActor(CharacterRef, CameraModeDA->CameraSettings.TagToRemove1);
	UECMAbilitySystemLibrary::RemoveTagFromActor(CharacterRef, CameraModeDA->CameraSettings.TagToRemove2);
	
	UpdateCameraModeCPP(CameraModeDA);
}

// Update setting dependent on Camera Mode
void AECMPlayerCameraManager::UpdateCameraModeCPP(const UDA_CameraMode* CameraModeDA)
{
	check(CameraModeDA);
	
	if(IsSpringArmValid()) // Set spring arm properties from Data Asset
		{
		SpringArmComponent->SetRelativeLocation(CameraModeDA->CameraSettings.Location);
		SpringArmComponent->SetRelativeRotation(CameraModeDA->CameraSettings.Rotation);
		SpringArmComponent->TargetArmLength = CameraModeDA->CameraSettings.TargetArmLength; 
		SpringArmComponent->bUsePawnControlRotation = CameraModeDA->CameraSettings.SpringArmUsePawnControlRotation;
		SpringArmComponent->bInheritPitch = CameraModeDA->CameraSettings.InheritPitch;
		SpringArmComponent->bInheritRoll = CameraModeDA->CameraSettings.InheritRoll;
		SpringArmComponent->bInheritYaw = CameraModeDA->CameraSettings.InheritYaw;
		SpringArmComponent->bEnableCameraLag = CameraModeDA->CameraSettings.EnableCameraLag;
		}
	
	if(IsCameraValid()) // Set camera properties from Data Asset
		{
		CameraComponent->bUsePawnControlRotation = CameraModeDA->CameraSettings.CameraUsePawnControlRotation; // Prevent the camera from rotating with the spring arm	}
		}

	if(CharacterRef) // Set Character properties from Data Asset
	{
		CharacterRef->bUseControllerRotationPitch = CameraModeDA->CameraSettings.UseControllerRotationPitch;
		CharacterRef->bUseControllerRotationRoll = CameraModeDA->CameraSettings.UseControllerRotationRoll;
		CharacterRef->bUseControllerRotationYaw = CameraModeDA->CameraSettings.UseControllerRotationYaw;	

		if(UCharacterMovementComponent* CharacterCMC = CharacterRef->GetCharacterMovement()) // Set Character Movement Component properties from Data Asset
		{
			CharacterCMC->bOrientRotationToMovement = CameraModeDA->CameraSettings.bOrientRotationToMovement;
			CharacterCMC->RotationRate = CameraModeDA->CameraSettings.RotationRate;
			CharacterCMC->bConstrainToPlane = CameraModeDA->CameraSettings.ConstrainToPlane;
			CharacterCMC->bSnapToPlaneAtStart = CameraModeDA->CameraSettings.SnapToPlaneAtStart;
		}
	}
}

// Bind Enhanced Inputs
void AECMPlayerCameraManager::BindInputs()
{
	if (AECMPlayerController* ECMPC = Cast<AECMPlayerController>(PCOwner))
	{
		if (UECMInputComponent* ECMInputComponent = ECMPC->GetInputComponent())
		{
			ECMInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &AECMPlayerCameraManager::ZoomCamera);
			ECMInputComponent->BindActionToTagOnStarted(ECMPC->GetInputConfig(), this, &AECMPlayerCameraManager::AbilityInputTagPressed);
		}
	}
}

// Call Update ViewMode on Tags activation
void AECMPlayerCameraManager::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if( !InputTag.MatchesTag(CameraLookUpTags.InputTag_CameraMode)) 	{ return; }

	if(InputTag.MatchesTagExact(CameraLookUpTags.InputTag_FPV))
	{
		UpdateCameraMode(FPV_Settings);
	}
	else if(InputTag.MatchesTagExact(CameraLookUpTags.InputTag_TPV))
	{
		UpdateCameraMode(TPV_Settings);
	}
	else if(InputTag.MatchesTagExact(CameraLookUpTags.InputTag_TDV))
	{
		UpdateCameraMode(TDV_Settings);
	}
	else {	UE_LOG(LogTemp, Warning, TEXT("Player CameraMode Tag not found, during Tag update")) }
}

// ReSharper disable once CppMemberFunctionMayBeConst - due to use in input binding.
void AECMPlayerCameraManager::ZoomCamera(const FInputActionValue& InputActionValve)
{
	if( !UECMAbilitySystemLibrary::ActorHasASC(CharacterRef) || !IsSpringArmValid()) return;

	if (UECMAbilitySystemLibrary::ActorASCContainsTag(CharacterRef, CameraLookUpTags.PlayerTag_FPV)) return ; 
	
	const float InputAxisVector  = InputActionValve.Get<float>();

	SpringArmComponent->TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + (InputAxisVector * ZoomRate), ZoomMin, ZoomMax);
}

// Helper Functions
bool AECMPlayerCameraManager::IsSpringArmValid()
{
	if(SpringArmComponent) return true;

	SpringArmComponent = CharacterRef->FindComponentByClass<USpringArmComponent>();

	return (SpringArmComponent != nullptr);
}
bool AECMPlayerCameraManager::IsCameraValid()
{
	if(CameraComponent) return true;

	CameraComponent = CharacterRef->FindComponentByClass<UCameraComponent>();
	
	return (CameraComponent != nullptr);
}
