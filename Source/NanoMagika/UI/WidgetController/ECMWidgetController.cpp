// Copyright Electronic CAD Monkey [ECM]

#include "ECMWidgetController.h"

#include "AttributeSet.h"
#include "NanoMagika/AbilitySystem/Data/ECMAttributeInformation.h"

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

void UECMWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const
{
	FECMAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValve = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
