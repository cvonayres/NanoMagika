// Copyright Electronic CAD Monkey [ECM]

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ECMUserWidget.generated.h"


UCLASS()
class NANOMAGIKA_API UECMUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerRef(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UObject> WidgetController;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
};
