// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "Data/ECMCharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NanoMagika/UI/WidgetController/ECMWidgetController.h"
#include "ECMAbilitySystemLibrary.generated.h"

struct FGameplayEffectContextHandle;

UCLASS()
class NANOMAGIKA_API UECMAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Widget Controller functions
	static FWidgetControllerParam GetParams(APlayerController* PC);
	UFUNCTION(BlueprintPure, Category="ECMABilitySystemLibrary|WidgetController")
	static UECMOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, Category="ECMABilitySystemLibrary|WidgetController")
	static UECMAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	// Initializer for Enemy functions
	UFUNCTION(BlueprintCallable, Category="ECMABilitySystemLibrary|CharacterClass")
	static UECMCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, Category="ECMABilitySystemLibrary|CharacterClass")
	static UECMEnemySpecInfo* GetClassDefaultInfo(UECMCharacterClassInfo* CharacterClassInfo, FGameplayTag EnemyTag );UFUNCTION(BlueprintCallable, Category="ECMABilitySystemLibrary|CharacterClass")
	static void InitializeEnemyAttributes(const UObject* WorldContextObject, FGameplayTag EnemyTag, float CharacterLevel, UECMAbilitySystemComponent* ESMASC);
	UFUNCTION(BlueprintCallable, Category="ECMABilitySystemLibrary|CharacterClass")
	static void InitializeEnemyAbilities(const UObject* WorldContextObject, FGameplayTag EnemyTag, UECMAbilitySystemComponent* ESMASC);
	UFUNCTION(BlueprintCallable, Category="ECMABilitySystemLibrary|CharacterClass")
	static void InitializeEnemyTags(const UObject* WorldContextObject, FGameplayTag EnemyTag, UECMAbilitySystemComponent* ESMASC);

	// Extension from Ability Type functions
	UFUNCTION(BlueprintPure, Category="ECMABilitySystemLibrary|GameplayEffects")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);
	UFUNCTION(BlueprintCallable, Category="ECMABilitySystemLibrary|GameplayEffects")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit);
	UFUNCTION(BlueprintPure, Category="ECMABilitySystemLibrary|GameplayEffects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);
	UFUNCTION(BlueprintCallable, Category="ECMABilitySystemLibrary|GameplayEffects")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit);

	// Handles for Actor Tags
	static bool ActorHasASC(AActor* Actor);
	static bool ActorASCContainsTag(AActor* Actor, FGameplayTag TagToMatch);
	static void AddTagToActor(AActor* Actor, FGameplayTag TagToAdd);
	static void RemoveTagFromActor(AActor* Actor, FGameplayTag TagToRemove);
};
