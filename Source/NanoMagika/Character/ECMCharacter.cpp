// Copyright Electronic CAD Monkey [ECM]

#include "ECMCharacter.h"
#include "AbilitySystemComponent.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemComponent.h"
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

void AECMCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Controller Reference for the Server
	ControllerRef = Cast<AECMPlayerController>(NewController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();
}

void AECMCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Controller Reference for the Client
	ControllerRef = Cast<AECMPlayerController>(GetController());

	// Init ability actor info for the client
	InitAbilityActorInfo();
}

void AECMCharacter::BeginPlay()
{
	Super::BeginPlay();

	UpdatedViewMode();
}

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

void AECMCharacter::InitAbilityActorInfo()
{
	AECMPlayerState* ECMPlayerState =  GetPlayerState<AECMPlayerState>();
	check(ECMPlayerState);

	// Get Ability System Component
	AbilitySystemComponent = ECMPlayerState->GetAbilitySystemComponent();

	// Set callbacks on ECM Ability System Component
	Cast<UECMAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	// Sets callbacks for Native Ability System Component
	AbilitySystemComponent->InitAbilityActorInfo(ECMPlayerState, this);

	// Get Attribute Set
	AttributeSet = ECMPlayerState->GetAttributeSet();

	// Initialise Primary Attributes
	InitDefaultAttributes();
	
	// Gets Player controller and cast ability system and attribute set to Overlap
	if(AECMPlayerController* ECMPlayerController = Cast<AECMPlayerController>(GetController()))
	{
		if(AECMHUD* ECMHUD = Cast<AECMHUD>(ECMPlayerController->GetHUD()))
		{
			//ECMHUD->InitOverlay(ECMPlayerController, ECMPlayerState, AbilitySystemComponent ,AttributeSet);
		}
	}
	
}

