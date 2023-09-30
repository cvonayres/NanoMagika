// Copyright Electronic CAD Monkey [ECM]

#include "ECMHUD.h"
#include "NanoMagika/UI/Widget/ECMUserWidget.h"
#include "NanoMagika/UI/WidgetController/ECMOverlayWidgetController.h"
#include "Blueprint/UserWidget.h"
#include "NanoMagika/UI/WidgetController/ECMAttributeMenuWidgetController.h"

// Creates overlay widget and controller and adds to viewport
void AECMHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_ECMHUD"))
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_ECMHUD"))

	// Create widget
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UECMUserWidget>(Widget);

	// ??
	const FWidgetControllerParam WidgetControllerParam(PC, PS, ASC, AS);
	UECMOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParam);

	// Create Widget controller and pass [PC,PS,ASC,AS]
	OverlayWidget->SetWidgetControllerRef(WidgetController);

	// Broadcast bound variables 
	WidgetController->BroadcastInitialValues();
	
	Widget->AddToViewport();
}

// Getter for Overlay Widget Controller
UECMOverlayWidgetController* AECMHUD::GetOverlayWidgetController(const FWidgetControllerParam &WCParams)
{
	if(OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UECMOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParam(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
		
		return OverlayWidgetController;
	}
	return OverlayWidgetController;	
}

// Getter for Attribute Menu Widget Controller
UECMAttributeMenuWidgetController* AECMHUD::GetAttributeMenuWidgetController(const FWidgetControllerParam& WCParams)
{
	if(AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UECMAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParam(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
		
		return AttributeMenuWidgetController;
	}
	return AttributeMenuWidgetController;	
}
