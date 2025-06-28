

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"

UCLASS()
class CAMPGROUNDSPROJECT_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void BindToAttributes();

protected:
	UPROPERTY(BlueprintReadOnly)
	float HealthPerecent;

};
