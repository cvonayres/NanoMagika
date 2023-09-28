// Copyright Electronic CAD Monkey [ECM]

#include "ECMWidgetController.h"

UECMWidgetController::UECMWidgetController()
{
}

void UECMWidgetController::SetWidgetControllerParam(const FWidgetControllerParam WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState= WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UECMWidgetController::BroadcastInitialValues()
{
}

void UECMWidgetController::BindCallbacksToDependencies()
{
}
