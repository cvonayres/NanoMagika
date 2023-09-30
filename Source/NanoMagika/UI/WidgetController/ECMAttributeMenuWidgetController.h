// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "ECMWidgetController.h"
#include "ECMAttributeMenuWidgetController.generated.h"

UCLASS(BlueprintType, Blueprintable)
class NANOMAGIKA_API UECMAttributeMenuWidgetController : public UECMWidgetController
{
	GENERATED_BODY()

public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;
};
