#include "CGCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/CGAbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

ACGCharacter::ACGCharacter()
{
	// Set this character to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

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

void ACGCharacter::InitDefaultAttributes() const
{

	if (!AbilitySystemComponent || !DefaultAttributeEffect) return;

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1.f, EffectContext);

	if (SpecHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
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

UCGAttributeSet* ACGCharacter::GetAttributeSet() const
{
	return AttributeSet;
}


