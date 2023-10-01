// Copyright Electronic CAD Monkey [ECM]

#include "ECMAttributeMenuWidgetController.h"
#include "NanoMagika/AbilitySystem/ECMAttributeSet.h"

// Bind callback when Attribute change
void UECMAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UECMAttributeSet* AS = CastChecked<UECMAttributeSet>(AttributeSet);
	check(AttributeInfo);

	for(auto& Pair :AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
		[this, Pair] (const FOnAttributeChangeData& Data)
		{
			BroadcastAttributeInfo(Pair.Key,Pair.Value());
		}
	);
	}
}

// Broadcast initial valves
void UECMAttributeMenuWidgetController::BroadcastInitialValues()
{
	// Get Attribute Set
	UECMAttributeSet* AS =  CastChecked<UECMAttributeSet>(AttributeSet);
	check(AttributeInfo);
	
	// Loop through attribute tags
	for (auto& Pair : AS->TagsToAttributes){
		BroadcastAttributeInfo(Pair.Key,Pair.Value());
	}
}

