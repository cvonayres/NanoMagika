// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "ECMInputConfig.h"
#include "ECMInputComponent.generated.h"


UCLASS()
class NANOMAGIKA_API UECMInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UECMInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
	
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UECMInputComponent::BindAbilityActions(const UECMInputConfig* InputConfig, UserClass* Object,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);

	for (const FECMInputAction& Action: InputConfig->AbilityInputActions)
	{
		if(Action.InputAction &&Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}			
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}			
			if(HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
			}
		}
	}
}

