#include "CGCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/CGAbilitySystemComponent.h"
#include "CGAttributeSet.h"
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

void ACGCharacter::AddStartUpEffects()
{
	check(AbilitySystemComponent);
	if (!HasAuthority()) return;

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartUpEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
		}
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

bool ACGCharacter::IsAlive() const
{
	return GetCurrentHealth() > 0.0f;
}

float ACGCharacter::GetCurrentHealth() const
{
	return AttributeSet ? AttributeSet->GetCurrentHealth() : 0.f;
}

float ACGCharacter::GetMaxHealth() const
{
	return AttributeSet ? AttributeSet->GetMaxHealth() : 0.f;
}

float ACGCharacter::GetCurrentStamina() const
{
	return AttributeSet ? AttributeSet->GetCurrentStamina() : 0.f;
}

float ACGCharacter::GetMaxStamina() const
{
	return AttributeSet ? AttributeSet->GetMaxStamina() : 0.f;
}

float ACGCharacter::GetMovementSpeed() const
{
	return AttributeSet ? AttributeSet->GetMovementSpeed() : 600.f;
}


