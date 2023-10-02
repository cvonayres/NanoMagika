// Copyright Electronic CAD Monkey [ECM]

#include "ECMCharacter.h"
#include "NanoMagika/Player/ECMPlayerController.h"
#include "NanoMagika/Player/ECMPlayerState.h"
#include "NanoMagika/UI/HUD/ECMHUD.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	// Init Character for the Server
	InitializeCharacter();
}

// Client side ready
void AECMCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Controller Reference for the Client
	ControllerRef = Cast<AECMPlayerController>(GetController());

	// Init Character for the client
	InitializeCharacter();
}

void AECMCharacter::InitializeCharacter()
{
	PlayerStateRef =  GetPlayerState<AECMPlayerState>();
	check(PlayerStateRef);

	// Get Ability System Component
	SetAbilitySystemComponent(PlayerStateRef->GetAbilitySystemComponent());
	check(GetAbilitySystemComponent());

	// Get Attribute Set
	SetAttributeSet(PlayerStateRef->GetAttributeSet());
	check(GetAttributeSet());

	// Set callbacks on ECM Ability System Component and native ASC
	InitAbilityActorInfo();
	
	// Initialise Default Attributes, Abilities and Gameplay tags
	InitDefaultAttributes();
	InitDefaultAbilities();
	InitDefaultGameplayTags();

	// Initialise HUD Overlay widget Controller
	InitHUD();

	// Set parameters based on view mode
	SetViewMode();
}

// Gets Player controller and cast ability system and attribute set to Overlap
void AECMCharacter::InitHUD() const
{
	if(!ControllerRef) return;
	
	if(AECMHUD* ECMHUD = Cast<AECMHUD>(ControllerRef->GetHUD()))
	{
		ECMHUD->InitOverlay(ControllerRef, PlayerStateRef, GetAbilitySystemComponent() ,GetAttributeSet());
	}
}

// Blueprint callable function
void AECMCharacter::SetViewMode()
{
	if(!ControllerRef) return;

	if(ControllerRef->ViewMode == EViewMode::FPV)
	{
		
	}
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
	if(!PlayerStateRef) return 0;

	return PlayerStateRef->GetPlayerLevel();
}
/* end Combat Interface */
