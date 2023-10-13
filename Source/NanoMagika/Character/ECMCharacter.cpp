// Copyright Electronic CAD Monkey [ECM]

#include "ECMCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemComponent.h"
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

	Super::InitializeCharacter();
	
	// Initialise HUD Overlay widget Controller
	InitHUD();
}

// Setup Default Attributes, Abilities & Tags
void AECMCharacter::InitDefaultAttributes() 
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void AECMCharacter::InitDefaultAbilities() 
{
	if(!HasAuthority()) return;
	
	GetECMASC()->AddGameplayAbilities(DefaultCharacterAbilities, true);
}

void AECMCharacter::InitDefaultGameplayTags()
{
	GetECMASC()->AddGameplayTags(DefaultCharacterTags);
}

// Gets Player controller and cast ability system and attribute set to Overlap
void AECMCharacter::InitHUD() const
{
	if(ControllerRef == nullptr) return;

	AECMHUD* ECMHUD = Cast<AECMHUD>(ControllerRef->GetHUD());
	if(ECMHUD == nullptr) return;

	ECMHUD->InitOverlay(ControllerRef, PlayerStateRef, GetAbilitySystemComponent() ,GetAttributeSet());
}

/* Combat Interface */
int32 AECMCharacter::GetPlayerLevel()
{
	if(PlayerStateRef == nullptr) return 0;

	return PlayerStateRef->GetPlayerLevel();
}


/* end Combat Interface */
