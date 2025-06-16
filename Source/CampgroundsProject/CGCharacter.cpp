#include "CGCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/CGAbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

ACGCharacter::ACGCharacter()
{
	// Set this character to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

}

void ACGCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACGCharacter::GiveDefaultAbilities()
{
	check(AbilitySystemComponent);
	if (!HasAuthority()) return;

	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultAbilities)
	{
		const FGameplayAbilitySpec AbilitySpec(AbilityClass, 1);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

void ACGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind ability inputs here if needed
}

UAbilitySystemComponent* ACGCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


