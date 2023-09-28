// Copyright Electronic CAD Monkey [ECM]

#include "ECMUserWidget.h"

void UECMUserWidget::SetWidgetControllerRef(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
