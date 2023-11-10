// Copyright Electronic CAD Monkey [ECM]

#include "ECMAbilitySystemLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "ECMAbilitySystemComponent.h"
#include "Data/ECMEnemySpecInfo.h"
#include "Kismet/GameplayStatics.h"
#include "NanoMagika/ECMAbilityTypes.h"
#include "NanoMagika/Game/ECMGameMode.h"
#include "NanoMagika/Player/PlayerState/ECMPlayerState.h"
#include "NanoMagika/UI/HUD/ECMHUD.h"
#include "NanoMagika/UI/WidgetController/ECMWidgetController.h"

# pragma region OverlayWidgetController
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
# pragma endregion OverlayWidgetController

// TODO make this generic to all NPCs
# pragma region InitializeEnemy
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

// Add Default Attributes defined in Character Class Info, Primary, Secondary & Vital
void UECMAbilitySystemLibrary::InitializeEnemyAttributes(const UObject* WorldContextObject, const FGameplayTag EnemyTag, const float CharacterLevel, UECMAbilitySystemComponent* ESMASC)
{
	const TObjectPtr<UECMCharacterClassInfo> CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	const TObjectPtr<UECMEnemySpecInfo> ClassDefaultInfo = GetClassDefaultInfo(CharacterClassInfo, EnemyTag);

	ESMASC->AddGameplayEffect( ClassDefaultInfo.Get()->PrimaryAttribute, CharacterLevel );

	ESMASC->AddGameplayEffect( CharacterClassInfo->SecondaryAttribute, CharacterLevel );

	ESMASC->AddGameplayEffect( CharacterClassInfo->VitalAttribute, CharacterLevel );
}

// Add Default Abilities defined in Character Class Info, both CLass Specific and Common
void UECMAbilitySystemLibrary::InitializeEnemyAbilities(const UObject* WorldContextObject, const FGameplayTag EnemyTag, UECMAbilitySystemComponent* ESMASC)
{
	const TObjectPtr<UECMCharacterClassInfo> CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	const TObjectPtr<UECMEnemySpecInfo> ClassDefaultInfo = GetClassDefaultInfo(CharacterClassInfo, EnemyTag);
	
	ESMASC->AddGameplayAbilities( ClassDefaultInfo.Get()->Abilities); // Enemy Specific Abilities	
	
	ESMASC->AddGameplayAbilities( CharacterClassInfo->CommonAbilities); // Enemy Common Abilities
}

// Add Default Tags defined in Character Class Info, both CLass Specific and Common
void UECMAbilitySystemLibrary::InitializeEnemyTags(const UObject* WorldContextObject, const FGameplayTag EnemyTag, UECMAbilitySystemComponent* ECMASC)
{
	const TObjectPtr<UECMCharacterClassInfo> CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	const TObjectPtr<UECMEnemySpecInfo> ClassDefaultInfo = GetClassDefaultInfo(CharacterClassInfo, EnemyTag);

	TArray<FGameplayTag> TagsToAdd;
	TagsToAdd.Empty();
	
	TagsToAdd.Add(EnemyTag);								// Enemy Definition Tag
	TagsToAdd.Add(ClassDefaultInfo.Get()->ClassTag);		// Enemy Class Tag	
	TagsToAdd.Append(ClassDefaultInfo.Get()->Tags);			// Enemy Specific Tag
	TagsToAdd.Append(CharacterClassInfo->CommonTags);		// Enemy Common Tags
	
	ECMASC->AddGameplayTags( TagsToAdd ); 
}
# pragma endregion InitializeEnemy

# pragma region DamageCalculation
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
# pragma endregion DamageCalculation

# pragma region ActorTags
bool UECMAbilitySystemLibrary::ActorHasASC(AActor* Actor)
{
	return UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor) != nullptr;
}

bool UECMAbilitySystemLibrary::ActorASCContainsTag(AActor* Actor, const FGameplayTag TagToMatch)
{
	checkf(ActorHasASC(Actor), TEXT("Actor: [%s] does not have a Ability System Component"));

	return UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor)->HasMatchingGameplayTag(TagToMatch);
}

void UECMAbilitySystemLibrary::AddTagToActor(AActor* Actor, FGameplayTag TagToAdd)
{
	checkf(ActorHasASC(Actor), TEXT("Actor: [%s] does not have a Ability System Component"));

	UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor)->AddLooseGameplayTag(TagToAdd);
}

void UECMAbilitySystemLibrary::RemoveTagFromActor(AActor* Actor, FGameplayTag TagToRemove)
{
	checkf(ActorHasASC(Actor), TEXT("Actor: [%s] does not have a Ability System Component"));

	UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor)->RemoveLooseGameplayTag(TagToRemove);
}

# pragma endregion ActorTags
