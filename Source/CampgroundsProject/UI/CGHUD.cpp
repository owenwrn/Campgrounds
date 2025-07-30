


#include "CGHUD.h"
#include "Blueprint/UserWidget.h"
#include "CampgroundsProject/CGGameStateBase.h"

void ACGHUD::Init()
{
	UIHUDWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), UIHUDWidgetClass);
	UIHUDWidget->AddToViewport();

	ACGGameStateBase* GS = GetWorld()->GetGameState<ACGGameStateBase>();
	if (!GS) return;

	GS->OnMatchEnd.AddDynamic(this, &ACGHUD::DestroyPlayerHUD);
}

void ACGHUD::DestroyPlayerHUD()
{
	UIHUDWidget->RemoveFromParent();
}


