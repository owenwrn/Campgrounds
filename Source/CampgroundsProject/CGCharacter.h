// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CGCharacter.generated.h"

class UGameplayAbility;
class UCGAbilitySystemComponent;
class UCGAttributeSet;
class UGameplayEffect;


UCLASS()
class CAMPGROUNDSPROJECT_API ACGCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACGCharacter();

protected:

	void GiveDefaultAbilities();

	void InitDefaultAttributes() const;

	// Attribute Set and ASC
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UCGAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UCGAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;

public:
	// GAS Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UCGAttributeSet* GetAttributeSet() const;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
