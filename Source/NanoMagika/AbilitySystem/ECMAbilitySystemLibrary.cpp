// Copyright Electronic CAD Monkey [ECM]

#include "ECMAbilitySystemLibrary.h"
#include "ECMAbilitySystemComponent.h"
#include "Data/ECMEnemySpecInfo.h"
#include "Kismet/GameplayStatics.h"
#include "NanoMagika/ECMAbilityTypes.h"
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
void UECMAbilitySystemLibrary::InitializeEnemyAttributes(const UObject* WorldContextObject, FGameplayTag EnemyTag, float Level, UECMAbilitySystemComponent* ESMASC)
{
	const TObjectPtr<UECMCharacterClassInfo> CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	const TObjectPtr<UECMEnemySpecInfo> ClassDefaultInfo = GetClassDefaultInfo(CharacterClassInfo, EnemyTag);

	ESMASC->AddGameplayEffect( ClassDefaultInfo.Get()->PrimaryAttribute, Level );

	ESMASC->AddGameplayEffect( CharacterClassInfo->SecondaryAttribute, Level );

	ESMASC->AddGameplayEffect( CharacterClassInfo->VitalAttribute, Level );
}

// Add Default Abilities defined in Character Class Info, both CLass Specific and Common
void UECMAbilitySystemLibrary::InitializeEnemyAbilities(const UObject* WorldContextObject, FGameplayTag EnemyTag, float Level, UECMAbilitySystemComponent* ESMASC)
{
	const TObjectPtr<UECMCharacterClassInfo> CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	const TObjectPtr<UECMEnemySpecInfo> ClassDefaultInfo = GetClassDefaultInfo(CharacterClassInfo, EnemyTag);
	
	ESMASC->AddGameplayAbilities( ClassDefaultInfo.Get()->Abilities, false ); // Enemy Specific Abilities	
	
	ESMASC->AddGameplayAbilities( CharacterClassInfo->CommonAbilities, false ); // Enemy Common Abilities
}

// Add Default Tags defined in Character Class Info, both CLass Specific and Common
void UECMAbilitySystemLibrary::InitializeEnemyTags(const UObject* WorldContextObject, FGameplayTag EnemyTag, UECMAbilitySystemComponent* ECMASC)
{
	const TObjectPtr<UECMCharacterClassInfo> CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	const TObjectPtr<UECMEnemySpecInfo> ClassDefaultInfo = GetClassDefaultInfo(CharacterClassInfo, EnemyTag);

	ECMASC->AddGameplayTags( ClassDefaultInfo.Get()->Tags );	// Enemy Specific Tag	

	ECMASC->AddGameplayTags( CharacterClassInfo->CommonTags ); // Enemy Common Tags
}

UECMCharacterClassInfo* UECMAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	const AECMGameMode* ECMGameMode = Cast<AECMGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (ECMGameMode == nullptr) return nullptr;
	return ECMGameMode->CharacterClassInfo;
}

UECMEnemySpecInfo* UECMAbilitySystemLibrary::GetClassDefaultInfo(UECMCharacterClassInfo* CharacterClassInfo, const FGameplayTag EnemyTag )
{
	return CharacterClassInfo->GetClassDefaultInfo(EnemyTag);
}

bool UECMAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(const FECMGameplayEffectContext* ECMEffectContext = static_cast<const FECMGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return ECMEffectContext->IsBlockedHit();
	}
	return false;	
}

void UECMAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit)
{
	if(FECMGameplayEffectContext* ECMEffectContext = static_cast<FECMGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		ECMEffectContext->SetIsBlockingHit(bInIsBlockedHit);
	}
}

bool UECMAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(const FECMGameplayEffectContext* ECMEffectContext = static_cast<const FECMGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return ECMEffectContext->IsCriticalHit();
	}
	return false;	
}

void UECMAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle,	bool bInIsCriticalHit)
{
	if(FECMGameplayEffectContext* ECMEffectContext = static_cast<FECMGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		ECMEffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}
