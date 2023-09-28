// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ECMHUD.generated.h"

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
	UPROPERTY()
	TObjectPtr<UECMUserWidget> OverlayWidget;

	// Creates overlay widget and controller and adds to viewport
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	// Getter for Overview Widget Controller
	UECMOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParam& WCParams);
	
private:
	// BP defined classes
	UPROPERTY(EditAnywhere)
	TSubclassOf<UECMUserWidget> OverlayWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UECMOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UECMOverlayWidgetController> OverlayWidgetController;
};
