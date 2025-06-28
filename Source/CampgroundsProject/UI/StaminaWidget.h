

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StaminaWidget.generated.h"

UCLASS()
class CAMPGROUNDSPROJECT_API UStaminaWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void BindToAttributes();

protected:
	UPROPERTY(BlueprintReadOnly)
	float StaminaPerecent;
	
};
