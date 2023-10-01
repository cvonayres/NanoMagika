// Copyright Electronic CAD Monkey [ECM]

#include "ECMCharacter.h"
#include "AbilitySystemComponent.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemComponent.h"
#include "NanoMagika/Player/ECMPlayerController.h"
#include "NanoMagika/Player/ECMPlayerState.h"
#include "NanoMagika/UI/HUD/ECMHUD.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayTagContainer.h"

AECMCharacter::AECMCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f,0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
}

// Server side ready
void AECMCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Controller Reference for the Server
	ControllerRef = Cast<AECMPlayerController>(NewController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();

}

// Client side ready
void AECMCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Controller Reference for the Client
	ControllerRef = Cast<AECMPlayerController>(GetController());

	// Init ability actor info for the client
	InitAbilityActorInfo();
}

// Begin Play
void AECMCharacter::BeginPlay()
{
	Super::BeginPlay();

	UpdatedViewMode();
}

// Init Ability System for character
void AECMCharacter::InitAbilityActorInfo()
{
	PlayerStateRef =  GetPlayerState<AECMPlayerState>();
	check(PlayerStateRef);

	// Get Ability System Component
	AbilitySystemComponent = PlayerStateRef->GetAbilitySystemComponent();

	// Set callbacks on ECM Ability System Component
	Cast<UECMAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	// Sets callbacks for Native Ability System Component
	AbilitySystemComponent->InitAbilityActorInfo(PlayerStateRef, this);

	// Get Attribute Set
	AttributeSet = PlayerStateRef->GetAttributeSet();
	
	// Initialise Default Attributes Tags
	InitDefaultAttributes();
	InitDefaultGameplayTags();
	
	// Gets Player controller and cast ability system and attribute set to Overlap
	if(AECMPlayerController* ECMPlayerController = Cast<AECMPlayerController>(GetController()))
	{
		if(AECMHUD* ECMHUD = Cast<AECMHUD>(ECMPlayerController->GetHUD()))
		{
			ECMHUD->InitOverlay(ECMPlayerController, PlayerStateRef, AbilitySystemComponent ,AttributeSet);
		}
	}
}

// Blueprint callable function
void AECMCharacter::UpdatedViewMode()
{
	if(!ControllerRef) return;

	if(ControllerRef->ViewMode == EViewMode::FPV)
	{ }
	else if (ControllerRef->ViewMode == EViewMode::TPV)
	{
		bUseControllerRotationPitch = false;
		bUseControllerRotationRoll = false;
		bUseControllerRotationYaw = true;
	}
	else if (ControllerRef->ViewMode == EViewMode::TDV)
	{
		bUseControllerRotationPitch = false;
		bUseControllerRotationRoll = false;
		bUseControllerRotationYaw = false;
	}
}

/* Combat Interface */
int32 AECMCharacter::GetPlayerLevel()
{
	if(PlayerStateRef)
	{
		return PlayerStateRef->GetPlayerLevel();
	}
	return 0;
}
/* end Combat Interface */
