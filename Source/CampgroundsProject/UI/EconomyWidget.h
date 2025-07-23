#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EconomyWidget.generated.h"

UCLASS()
class CAMPGROUNDSPROJECT_API UEconomyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void BindToAttributes();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMoney(float Money);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetQuota(float Quota);
};
