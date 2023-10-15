// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "Data/ECMCharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NanoMagika/UI/WidgetController/ECMWidgetController.h"
#include "ECMAbilitySystemLibrary.generated.h"

class UECMAbilitySystemComponent;
class UECMAttributeMenuWidgetController;
class UECMOverlayWidgetController;

UCLASS()
class NANOMAGIKA_API UECMAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="ECMABilitySystemLibrary|WidgetController")
	static UECMOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="ECMABilitySystemLibrary|WidgetController")
	static UECMAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	static FWidgetControllerParam GetParams(APlayerController* PC);

	UFUNCTION(BlueprintCallable, Category="ECMABilitySystemLibrary|CharacterClass")
	static void InitializeEnemyAttributes(const UObject* WorldContextObject, FGameplayTag EnemyTag, float Level, UECMAbilitySystemComponent* ESMASC);

	UFUNCTION(BlueprintCallable, Category="ECMABilitySystemLibrary|CharacterClass")
	static void InitializeEnemyAbilities(const UObject* WorldContextObject, FGameplayTag EnemyTag, float Level, UECMAbilitySystemComponent* ESMASC);

	UFUNCTION(BlueprintCallable, Category="ECMABilitySystemLibrary|CharacterClass")
	static void InitializeEnemyTags(const UObject* WorldContextObject, FGameplayTag EnemyTag, UECMAbilitySystemComponent* ESMASC);

	UFUNCTION(BlueprintCallable, Category="ECMABilitySystemLibrary|CharacterClass")
	static UECMCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="ECMABilitySystemLibrary|CharacterClass")
	static UECMEnemySpecInfo* GetClassDefaultInfo(UECMCharacterClassInfo* CharacterClassInfo, FGameplayTag EnemyTag );
	
};
