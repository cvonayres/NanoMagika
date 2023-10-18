// Copyright Electronic CAD Monkey [ECM]

#include "ECMPlayerCameraManager.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "NanoMagika/ECMGameplayTags.h"
#include "NanoMagika/Input/ECMInputComponent.h"
#include "NanoMagika/Player/PlayerController/ECMPlayerController.h"

//TODO add a static struct to define tags

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
	if(!GetCharacterASC()) return;

	const FGameplayTag FPVTag = FGameplayTag::RequestGameplayTag(FName("Player.CameraMode.FPV"));
	const FGameplayTag TPVTag = FGameplayTag::RequestGameplayTag(FName("Player.CameraMode.TPV"));
	const FGameplayTag TDVTag = FGameplayTag::RequestGameplayTag(FName("Player.CameraMode.TDV"));

	if (CheckCameraMode("Player.CameraMode.FPV"))	    { UpdateCameraMode(FPV_Settings, FPVTag, TPVTag, TDVTag); }
	else if (CheckCameraMode("Player.CameraMode.TPV"))	{ UpdateCameraMode(TPV_Settings, TPVTag, FPVTag, TDVTag); }
	else if (CheckCameraMode("Player.CameraMode.TDV"))	{ UpdateCameraMode(TDV_Settings, TDVTag, FPVTag, TPVTag); }
	else {	UE_LOG(LogTemp, Warning, TEXT("Player CameraMode Tag not found, check initial character tag includes CameraMode FPV,TPV or TDV")) }
}

// Call Update Camera Mode passing in right Data Asset and swaps the tags on Character.CameraMode
void AECMPlayerCameraManager::UpdateCameraMode(UDA_CameraMode* CameraModeDA, const FGameplayTag AddTag, const FGameplayTag RemoveTag1, const FGameplayTag RemoveTag2)
{
	UpdateCameraModeCPP(CameraModeDA);
	
	if(!GetCharacterASC()) return;

	if(CharacterASC->HasMatchingGameplayTag(AddTag)) return; // Finish if we are already have this tag active.

	CharacterASC->AddLooseGameplayTag(AddTag);
	CharacterASC->RemoveLooseGameplayTag(RemoveTag1);
	CharacterASC->RemoveLooseGameplayTag(RemoveTag2);
}

// Update setting dependent on Camera Mode
void AECMPlayerCameraManager::UpdateCameraModeCPP(const UDA_CameraMode* CameraModeDA)
{
	check(CameraModeDA);
	
	if(GetSpringArm()) // Set spring arm properties from Data Asset
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
	
	if(GetCamera()) // Set camera properties from Data Asset
	{
		CameraComponent->bUsePawnControlRotation = CameraModeDA->CameraSettings.CameraUsePawnControlRotation; // Prevent the camera from rotating with the spring arm	}
	}

	if(CharacterRef) // Set Character properties from Data Asset
	{
		CharacterRef->bUseControllerRotationPitch = CameraModeDA->CameraSettings.UseControllerRotationPitch;
		CharacterRef->bUseControllerRotationRoll = CameraModeDA->CameraSettings.UseControllerRotationRoll;
		CharacterRef->bUseControllerRotationYaw = CameraModeDA->CameraSettings.UseControllerRotationYaw;	
	}

	if(GetCharacterMovementComponent()) // Set Character Movement Component properties from Data Asset
	{
		CharacterCMC->bOrientRotationToMovement = CameraModeDA->CameraSettings.bOrientRotationToMovement;
		CharacterCMC->RotationRate = CameraModeDA->CameraSettings.RotationRate;
		CharacterCMC->bConstrainToPlane = CameraModeDA->CameraSettings.ConstrainToPlane;
		CharacterCMC->bSnapToPlaneAtStart = CameraModeDA->CameraSettings.SnapToPlaneAtStart;
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
	if(const FGameplayTag CameraModeTag = FGameplayTag::RequestGameplayTag(FName("Player.CameraMode")); !InputTag.MatchesTagExact(CameraModeTag)) 	{ return; }
	
	const FGameplayTag FPVTag = FGameplayTag::RequestGameplayTag(FName("Player.CameraMode.FPV"));
	const FGameplayTag TPVTag = FGameplayTag::RequestGameplayTag(FName("Player.CameraMode.TPV"));
	const FGameplayTag TDVTag = FGameplayTag::RequestGameplayTag(FName("Player.CameraMode.TDV"));
	
	if(InputTag.MatchesTagExact(FECMGameplayTags::Get().Input_Action_Camera_FPV))      { UpdateCameraMode(FPV_Settings, FPVTag, TPVTag, TDVTag); }
	else if(InputTag.MatchesTagExact(FECMGameplayTags::Get().Input_Action_Camera_TPV)) { UpdateCameraMode(TPV_Settings, TPVTag, FPVTag, TDVTag); }
	else if(InputTag.MatchesTagExact(FECMGameplayTags::Get().Input_Action_Camera_TDV)) { UpdateCameraMode(TDV_Settings, TDVTag, FPVTag, TPVTag); }
	else {	UE_LOG(LogTemp, Warning, TEXT("Player CameraMode Tag not found, during Tag update")) }
}

// ReSharper disable once CppMemberFunctionMayBeConst - due to use in input binding.
void AECMPlayerCameraManager::ZoomCamera(const FInputActionValue& InputActionValve)
{
	if(CheckCameraMode("Player.CameraMode.FPV")){ return; } // If in First Person View.
	
	if(SpringArmComponent == nullptr) return;
	
	const float InputAxisVector  = InputActionValve.Get<float>();

	SpringArmComponent->TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + (InputAxisVector * ZoomRate), ZoomMin, ZoomMax);
}

// Helper Functions
bool AECMPlayerCameraManager::GetSpringArm()
{
	if(SpringArmComponent) return true;

	SpringArmComponent = CharacterRef->FindComponentByClass<USpringArmComponent>();

	return (SpringArmComponent != nullptr);
}
bool AECMPlayerCameraManager::GetCamera()
{
	if(CameraComponent) return true;

	CameraComponent = CharacterRef->FindComponentByClass<UCameraComponent>();
	
	return (CameraComponent != nullptr);
}
bool AECMPlayerCameraManager::GetCharacterMovementComponent()
{
	if(CharacterCMC) return true;

	check(CharacterRef);
	
	CharacterCMC = CharacterRef->GetCharacterMovement();

	return (CharacterCMC != nullptr);
}
bool AECMPlayerCameraManager::GetCharacterASC()
{
	if(CharacterASC) return true;

	CharacterASC = Cast<UAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(CharacterRef));

	return (CharacterASC != nullptr);
}

bool AECMPlayerCameraManager::CheckCameraMode(FName TagName)
{
	if(!GetCharacterASC()) { return false; }
	
	const FGameplayTag Tag = FGameplayTag::RequestGameplayTag(TagName);
	return (CharacterASC->HasMatchingGameplayTag(Tag));
}
