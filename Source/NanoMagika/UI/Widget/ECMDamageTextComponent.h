// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "ECMDamageTextComponent.generated.h"

class UECMDamageTextWidget;

UCLASS()
class NANOMAGIKA_API UECMDamageTextComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetDamageText(float Damage, bool bBlockHit, bool bCriticalHit);
};
