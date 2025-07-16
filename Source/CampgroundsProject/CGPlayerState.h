

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "CGPlayerState.generated.h"

class UCGAbilitySystemComponent;
class UCGAttributeSet;

UCLASS()
class CAMPGROUNDSPROJECT_API ACGPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACGPlayerState();

	// GAS Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UCGAttributeSet* GetAttributeSet() const;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UCGAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UCGAttributeSet> AttributeSet;
	
	FGameplayTag DeadTag;

	FDelegateHandle HealthChangedDelegateHandle;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Attribute changed callbacks
	virtual void HealthChanged(const FOnAttributeChangeData& Data);
};
