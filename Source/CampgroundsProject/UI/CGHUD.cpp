


#include "CGHUD.h"
#include "CampgroundsProject/UI/PlayerHUDWidget.h"

void ACGHUD::Init()
{
	UIHUDWidget = CreateWidget<UPlayerHUDWidget>(GetOwningPlayerController(), UIHUDWidgetClass);
	UIHUDWidget->AddToViewport();
}


