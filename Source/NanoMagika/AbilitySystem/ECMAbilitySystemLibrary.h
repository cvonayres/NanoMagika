// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "Data/ECMCharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NanoMagika/UI/WidgetController/ECMWidgetController.h"
#include "ECMAbilitySystemLibrary.generated.h"

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
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);

};
