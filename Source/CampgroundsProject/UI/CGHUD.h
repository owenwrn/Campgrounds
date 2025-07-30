

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CGHUD.generated.h"

class UPlayerHUDWidget;
/**
 * 
 */
UCLASS()
class CAMPGROUNDSPROJECT_API ACGHUD : public AHUD
{
	GENERATED_BODY()

public:
	void Init();

	UFUNCTION()
	void DestroyPlayerHUD();
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> UIHUDWidgetClass;

private:
	UPROPERTY()
	TObjectPtr<UUserWidget> UIHUDWidget;
		
};
