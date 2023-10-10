// Copyright Electronic CAD Monkey [ECM]

#include "ECMAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NanoMagika/Game/ECMGameMode.h"
#include "NanoMagika/Player/PlayerState/ECMPlayerState.h"
#include "NanoMagika/UI/HUD/ECMHUD.h"
#include "NanoMagika/UI/WidgetController/ECMWidgetController.h"

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

FWidgetControllerParam UECMAbilitySystemLibrary::GetParams(APlayerController* PC)
{
	AECMPlayerState* PS = PC->GetPlayerState<AECMPlayerState>();
	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
	UAttributeSet* AS =  PS->GetAttributeSet();
	return FWidgetControllerParam (PC, PS, ASC, AS);
}

void UECMAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{const AECMGameMode* ECMGameMode = Cast<AECMGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (ECMGameMode == nullptr) return;
	
	const TObjectPtr<UECMCharacterClassInfo> CharacterClassInfo = ECMGameMode->CharacterClassInfo;
	const FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	
	FGameplayEffectContextHandle PrimaryAttributeContextHandle = ASC->MakeEffectContext();
	PrimaryAttributeContextHandle.AddSourceObject(ASC->GetAvatarActor());
	const FGameplayEffectSpecHandle PrimaryAttributeSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttribute, Level, PrimaryAttributeContextHandle) ;
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributeSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributeContextHandle = ASC->MakeEffectContext();
	SecondaryAttributeContextHandle.AddSourceObject(ASC->GetAvatarActor());
	const FGameplayEffectSpecHandle SecondaryAttributeSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttribute, Level, SecondaryAttributeContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributeSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributeContextHandle = ASC->MakeEffectContext();
	VitalAttributeContextHandle.AddSourceObject(ASC->GetAvatarActor());
	const FGameplayEffectSpecHandle VitalAttributeSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttribute, Level, VitalAttributeContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributeSpecHandle.Data.Get());
}
