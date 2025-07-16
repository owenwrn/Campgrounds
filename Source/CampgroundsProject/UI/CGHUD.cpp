


#include "CGHUD.h"
#include "Blueprint/UserWidget.h"

void ACGHUD::Init()
{
	UIHUDWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), UIHUDWidgetClass);
	UIHUDWidget->AddToViewport();
}


