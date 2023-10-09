// Copyright Electronic CAD Monkey [ECM]

#include "ECMCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "NanoMagika/Player/PlayerController/ECMPlayerController.h"
#include "NanoMagika/Player/PlayerState/ECMPlayerState.h"

#include "NanoMagika/UI/HUD/ECMHUD.h"

AECMCharacter::AECMCharacter()
{
	// Create the spring arm component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);

	// Create the camera component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
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

/* Combat Interface */
int32 AECMCharacter::GetPlayerLevel()
{
	if(!PlayerStateRef) return 0;

	return PlayerStateRef->GetPlayerLevel();
}
/* end Combat Interface */
