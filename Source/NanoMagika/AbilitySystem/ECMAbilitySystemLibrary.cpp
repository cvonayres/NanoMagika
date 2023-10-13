// Copyright Electronic CAD Monkey [ECM]

#include "ECMAbilitySystemLibrary.h"
#include "ECMAbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NanoMagika/Game/ECMGameMode.h"
#include "NanoMagika/Player/PlayerState/ECMPlayerState.h"
#include "NanoMagika/UI/HUD/ECMHUD.h"
#include "NanoMagika/UI/WidgetController/ECMWidgetController.h"

FWidgetControllerParam UECMAbilitySystemLibrary::GetParams(APlayerController* PC)
{
	AECMPlayerState* PS = PC->GetPlayerState<AECMPlayerState>();
	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
	UAttributeSet* AS =  PS->GetAttributeSet();
	return FWidgetControllerParam (PC, PS, ASC, AS);
}

// Called from widget, returns Overlay Widget Controller
UECMOverlayWidgetController* UECMAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if(APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if(AECMHUD* ECMHUD = Cast<AECMHUD>(PC->GetHUD()))
		{
			return ECMHUD->GetOverlayWidgetController(GetParams(PC));
		}
	}
	return nullptr;
}

// Called from widget only, returns Attribute Menu Widget Controller
UECMAttributeMenuWidgetController* UECMAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if(APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if(AECMHUD* ECMHUD = Cast<AECMHUD>(PC->GetHUD()))
		{
			return ECMHUD->GetAttributeMenuWidgetController(GetParams(PC));
		}
	}
	return nullptr;
}

// Add Default Attributes defined in Character Class Info, Primary, Secondary & Vital
void UECMAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UECMAbilitySystemComponent* ESMASC)
{
	const AECMGameMode* ECMGameMode = Cast<AECMGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (ECMGameMode == nullptr) return;
	
	const TObjectPtr<UECMCharacterClassInfo> CharacterClassInfo = ECMGameMode->CharacterClassInfo;
	const FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	ESMASC->AddGameplayEffect(ClassDefaultInfo.PrimaryAttribute, Level );

	ESMASC->AddGameplayEffect( CharacterClassInfo->SecondaryAttribute, Level );

	ESMASC->AddGameplayEffect( CharacterClassInfo->VitalAttribute, Level );
}

// Add Default Abilities defined in Character Class Info, both CLass Specific and Common
void UECMAbilitySystemLibrary::InitializeDefaultAbilities(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UECMAbilitySystemComponent* ESMASC)
{
	const AECMGameMode* ECMGameMode = Cast<AECMGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (ECMGameMode == nullptr) return;
	
	const TObjectPtr<UECMCharacterClassInfo> CharacterClassInfo = ECMGameMode->CharacterClassInfo;
	const FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	
	ESMASC->AddGameplayAbilities( ClassDefaultInfo.Abilities, true ); // Enemy Specific Abilities	
	
	ESMASC->AddGameplayAbilities( CharacterClassInfo->CommonAbilities, true ); // Enemy Common Abilities
}

// Add Default Tags defined in Character Class Info, both CLass Specific and Common
void UECMAbilitySystemLibrary::InitializeDefaultTags(const UObject* WorldContextObject, ECharacterClass CharacterClass,	UECMAbilitySystemComponent* ECMASC)
{
	const AECMGameMode* ECMGameMode = Cast<AECMGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (ECMGameMode == nullptr) return;
	
	const TObjectPtr<UECMCharacterClassInfo> CharacterClassInfo = ECMGameMode->CharacterClassInfo;
	const FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	ECMASC->AddGameplayTags( ClassDefaultInfo.Tags );	// Enemy Specific Tag	

	ECMASC->AddGameplayTags( CharacterClassInfo->CommonTags ); // Enemy Common Tags
}
