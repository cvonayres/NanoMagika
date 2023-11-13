// Copyright Electronic CAD Monkey [ECM]

#include "ECMPlayerCameraManager.h"
#include "DA_CameraMode.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "NanoMagika/ECMGameplayTags.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemLibrary.h"
#include "NanoMagika/Input/ECMInputComponent.h"
#include "NanoMagika/Player/PlayerController/ECMPlayerController.h"

// Call from Player Controller on Owning Local Client Only
void AECMPlayerCameraManager::InitPCM(const ACharacter* Character)
{
	if(! Character->IsLocallyControlled() ) return;

	CharacterRef = const_cast<ACharacter*>(Character);
	
	checkf(CharacterRef, TEXT("Character const cast failed"));
	
	InitaliseFromDA(); // Update setting with ViewMode from Tag in Player Character
	
	BindInputs(); // Bind inputs for this class
}

// Call Specific View Mode dependent on Character Starting Tag
void AECMPlayerCameraManager::InitaliseFromDA()
{
	if( !UECMAbilitySystemLibrary::ActorHasASC(CharacterRef) ) return;

	for (const auto Pair : CameraTags.TagToCameraSettingMapping)
	{
		if ( UECMAbilitySystemLibrary::ActorASCContainsTag(CharacterRef, Pair.Key) )
		{
			UpdateCameraMode(Pair.Value);
			return;
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Player CameraMode Tag not found, check initial character tag includes CameraMode FPV,TPV or TDV"))
}

// Bind Enhanced Inputs
void AECMPlayerCameraManager::BindInputs()
{
	if (const AECMPlayerController* ECMPC = Cast<AECMPlayerController>(PCOwner))
	{
		if (UECMInputComponent* ECMInputComponent = ECMPC->GetInputComponent())
		{
			ECMInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &AECMPlayerCameraManager::ZoomCamera);
			ECMInputComponent->BindActionToTagOnStarted(ECMPC->GetInputConfig(), this, &AECMPlayerCameraManager::AbilityInputTagPressed);
		}
	}
}

// Call Update ViewMode on Tags activation
void AECMPlayerCameraManager::AbilityInputTagPressed(FGameplayTag InputTag){
	const FGameplayTag CameraParentTag = FGameplayTag::RequestGameplayTag(FName("Input.Action.CameraMode"));
	if ( InputTag.MatchesTag( CameraParentTag ) )
	{
		const FGameplayTag CameraTag = CameraTags.GetCameraTagFromInputTag(InputTag);

		const TObjectPtr<UDA_CameraMode> CameraDA = CameraTags.GetSettingFromTag(CameraTag);
		if ( CameraDA == nullptr ) return;
	
		UECMAbilitySystemLibrary::AddTagToActor(CharacterRef, CameraDA->CameraTags.GameplayTag);
		UECMAbilitySystemLibrary::RemoveTagFromActor(CharacterRef, CameraDA->CameraTags.TagToRemove1);
		UECMAbilitySystemLibrary::RemoveTagFromActor(CharacterRef, CameraDA->CameraTags.TagToRemove2);
	
		UpdateCameraMode(CameraDA);
	}
}

// Update setting dependent on Camera Mode
void AECMPlayerCameraManager::UpdateCameraMode(TObjectPtr<UDA_CameraMode> CameraDA )
{
	if ( CameraDA == nullptr ) return;

	// Turns on CanCheckForFaceActors that it used in BP
	if( CharacterRef && IsCameraValid() )  { bCanCheckForFade = CameraDA->bCanCheckForFadeActors; }
	
	if(IsSpringArmValid()) // Set spring arm properties from Data Asset
		{
		SpringArmComponent->SetRelativeLocation(CameraDA->SpringArmSettings.Location);
		SpringArmComponent->SetRelativeRotation(CameraDA->SpringArmSettings.Rotation);
		SpringArmComponent->TargetArmLength = CameraDA->SpringArmSettings.TargetArmLength; 
		SpringArmComponent->bUsePawnControlRotation = CameraDA->SpringArmSettings.UsePawnControlRotation;
		SpringArmComponent->bInheritPitch = CameraDA->SpringArmSettings.InheritPitch;
		SpringArmComponent->bInheritRoll = CameraDA->SpringArmSettings.InheritRoll;
		SpringArmComponent->bInheritYaw = CameraDA->SpringArmSettings.InheritYaw;
		SpringArmComponent->bEnableCameraLag = CameraDA->SpringArmSettings.EnableCameraLag;
		}
	
	if(IsCameraValid()) // Set camera properties from Data Asset
		{
		CameraComponent->bUsePawnControlRotation = CameraDA->Camera.UsePawnControlRotation; // Prevent the camera from rotating with the spring arm	}
		}

	if(CharacterRef) // Set Character properties from Data Asset
	{
		CharacterRef->bUseControllerRotationPitch = CameraDA->Character.UseControllerRotationPitch;
		CharacterRef->bUseControllerRotationRoll = CameraDA->Character.UseControllerRotationRoll;
		CharacterRef->bUseControllerRotationYaw = CameraDA->Character.UseControllerRotationYaw;	

		if(UCharacterMovementComponent* CharacterCMC = CharacterRef->GetCharacterMovement()) // Set Character Movement Component properties from Data Asset
		{
			CharacterCMC->bOrientRotationToMovement = CameraDA->CharacterMC.bOrientRotationToMovement;
			CharacterCMC->RotationRate = CameraDA->CharacterMC.RotationRate;
			CharacterCMC->bConstrainToPlane = CameraDA->CharacterMC.ConstrainToPlane;
			CharacterCMC->bSnapToPlaneAtStart = CameraDA->CharacterMC.SnapToPlaneAtStart;
		}
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst - due to use in input binding.
void AECMPlayerCameraManager::ZoomCamera(const FInputActionValue& InputActionValve)
{
	if( !UECMAbilitySystemLibrary::ActorHasASC(CharacterRef) || !IsSpringArmValid()) return;

	if (UECMAbilitySystemLibrary::ActorASCContainsTag(CharacterRef, FECMGameplayTags::Get().Player_CameraMode_FPV)) return ; 
	
	const float InputAxisVector  = InputActionValve.Get<float>();
	const float NewArmLength =	SpringArmComponent->TargetArmLength + (InputAxisVector * ZoomSettings.ZoomRate);
	
	SpringArmComponent->TargetArmLength = FMath::Clamp(NewArmLength, ZoomSettings.ZoomMin, ZoomSettings.ZoomMax);
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
