


#include "PlayerCharacter.h"
#include "CampgroundsProject/AbilitySystem/CGAbilitySystemComponent.h"
#include "CampgroundsProject/CGPlayerState.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilitySystemComponent();
	GiveDefaultAbilities();
}


void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilitySystemComponent();
}

void APlayerCharacter::InitAbilitySystemComponent()
{
	ACGPlayerState* CGPlayerState = GetPlayerState<ACGPlayerState>();
	check(CGPlayerState);
	AbilitySystemComponent = CastChecked<UCGAbilitySystemComponent>(CGPlayerState->GetAbilitySystemComponent());
	AbilitySystemComponent->InitAbilityActorInfo(CGPlayerState, this);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


