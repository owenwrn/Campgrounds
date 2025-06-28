

#pragma once

#include "CoreMinimal.h"
#include "CampgroundsProject/CGCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class CAMPGROUNDSPROJECT_API APlayerCharacter : public ACGCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void InitAbilitySystemComponent();

	void InitHUD();
	
};
