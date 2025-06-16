

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "CGPlayerState.generated.h"

class UCGAbilitySystemComponent;

UCLASS()
class CAMPGROUNDSPROJECT_API ACGPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACGPlayerState();

	// GAS Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:

	UPROPERTY()
	TObjectPtr<UCGAbilitySystemComponent> AbilitySystemComponent;
	
};
