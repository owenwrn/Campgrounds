


#include "PlayerCharacter.h"
#include "CampgroundsProject/AbilitySystem/CGAbilitySystemComponent.h"
#include "CampgroundsProject/CGPlayerState.h"
#include "CampgroundsProject/UI/CGHUD.h"
#include "CampgroundsProject/CGGameMode.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Forcibly set the DeadTag count to 0
	AbilitySystemComponent->SetTagMapCount(DeadTag, 0);

	InitAbilitySystemComponent();
	GiveDefaultAbilities();
	InitDefaultAttributes();
	AddStartUpEffects();
	InitHUD();
}


void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilitySystemComponent();
	InitDefaultAttributes();
	AddStartUpEffects();
	InitHUD();
}

void APlayerCharacter::FinishDying()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		ACGGameMode* GM = Cast<ACGGameMode>(GetWorld()->GetAuthGameMode());

		if (GM)
		{
			GM->PlayerDied(GetController());
		}
	}

	Super::FinishDying();
}

void APlayerCharacter::InitAbilitySystemComponent()
{
	ACGPlayerState* CGPlayerState = GetPlayerState<ACGPlayerState>();
	check(CGPlayerState);
	AbilitySystemComponent = CastChecked<UCGAbilitySystemComponent>(CGPlayerState->GetAbilitySystemComponent());
	AbilitySystemComponent->InitAbilityActorInfo(CGPlayerState, this);
	AttributeSet = CGPlayerState->GetAttributeSet();
}

void APlayerCharacter::InitHUD()
{
	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (ACGHUD* HUD = Cast<ACGHUD>(PlayerController->GetHUD()))
		{
			HUD->Init();
		}
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


