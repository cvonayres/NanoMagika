// Copyright Electronic CAD Monkey [ECM]

#include "ECMCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "NanoMagika/ECMLogChannels.h"
#include "NanoMagika/AbilitySystem/ECMAbilitySystemComponent.h"
#include "NanoMagika/Player/PlayerCameraManager/ECMPlayerCameraManager.h"
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

	// Init ability actor info for the Server
	InitializeCharacter();
	InitDefaultAbilities();
}

// Client side ready
void AECMCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitializeCharacter();
}

// Initialise all characters
void AECMCharacter::InitializeCharacter()
{
	PlayerStateRef = GetPlayerState<AECMPlayerState>();
	check(PlayerStateRef);
	
	PlayerStateRef->GetAbilitySystemComponent()->InitAbilityActorInfo(PlayerStateRef, this);

	Cast<UECMAbilitySystemComponent>(PlayerStateRef->GetAbilitySystemComponent())->BindEffectApplied();
	
	AbilitySystemComponent = PlayerStateRef->GetAbilitySystemComponent();
	AttributeSet = PlayerStateRef->GetAttributeSet();
	
	ControllerRef = Cast<AECMPlayerController>(GetController());
	if ( ControllerRef  != nullptr)
	{
		InitDefaultGameplayTags();

		InitPCM();

		InitHUD();
	}
	
	InitDefaultAttributes();
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
	if(!HasAuthority() || DefaultCharacterAbilities.IsEmpty()) return;
	
	GetECMASC()->AddGameplayAbilities(DefaultCharacterAbilities);
}

void AECMCharacter::InitDefaultGameplayTags()
{
	GetECMASC()->AddGameplayTags(DefaultCharacterTags);
}

// Get ECM Player Camera Manager and calls Initialise
void AECMCharacter::InitPCM() const
{
	
	if(AECMPlayerCameraManager* PCM = Cast<AECMPlayerCameraManager>(ControllerRef->PlayerCameraManager))
	{
		PCM->InitPCM(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Camera Manager not found for [%s]"), *this->GetActorNameOrLabel())
	}
}

// Get ECMHUD and calls Initialise sending along ability system and attribute set to Overlap
void AECMCharacter::InitHUD() const
{
	if(AECMHUD* ECMHUD = Cast<AECMHUD>(ControllerRef->GetHUD()))
	{
		ECMHUD->InitOverlay(ControllerRef, PlayerStateRef, GetAbilitySystemComponent() ,GetAttributeSet());
	}
	else
	{
		UE_LOG(LogECM, Warning, TEXT("HUD not found for [%s]"), *this->GetActorNameOrLabel())
	}
}

/* Combat Interface */
int32 AECMCharacter::GetPlayerLevel()
{
	if(PlayerStateRef == nullptr) return 0;

	return PlayerStateRef->GetPlayerLevel();
}
/* end Combat Interface */
