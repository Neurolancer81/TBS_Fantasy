// Copyright NeuroGames


#include "UI/Widget/TBSUserWidget.h"

void UTBSUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
