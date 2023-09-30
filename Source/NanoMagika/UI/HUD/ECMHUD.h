// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ECMHUD.generated.h"

class UECMAttributeMenuWidgetController;
class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParam;
class UECMOverlayWidgetController;
class UECMUserWidget;

UCLASS()
class NANOMAGIKA_API AECMHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	// Creates overlay widget and controller and adds to viewport
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	// Getter for Overview Widget Controller
	UECMOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParam& WCParams);
	// Getter for Attribute Menu Widget Controller
	UECMAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParam& WCParams);
	
private:
	// Overlap Widget Controller
	UPROPERTY()
	TObjectPtr<UECMUserWidget> OverlayWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UECMUserWidget> OverlayWidgetClass;
	UPROPERTY()
	TObjectPtr<UECMOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UECMOverlayWidgetController> OverlayWidgetControllerClass;
	
	// Attribute Menu Widget Controller
	UPROPERTY()
	TObjectPtr<UECMAttributeMenuWidgetController> AttributeMenuWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UECMAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;

};
