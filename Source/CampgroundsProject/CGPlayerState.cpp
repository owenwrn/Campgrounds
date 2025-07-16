


#include "CGPlayerState.h"
#include "AbilitySystem/CGAbilitySystemComponent.h"
#include "CampgroundsProject/CGAttributeSet.h"
#include "Characters/PlayerCharacter.h"


// Sets default values
ACGPlayerState::ACGPlayerState()
{
	NetUpdateFrequency = 100.f;

	AbilitySystemComponent = CreateDefaultSubobject<UCGAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UCGAttributeSet>("AttributeSet");

}

UAbilitySystemComponent* ACGPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UCGAttributeSet* ACGPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}

void ACGPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		// Attribute change callbacks
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetCurrentHealthAttribute()).AddUObject(this, &ACGPlayerState::HealthChanged);
	}
}

void ACGPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue;

	APlayerCharacter* Player = Cast<APlayerCharacter>(GetPawn());
	// If the player died, handle death
	if (Health <= 0.0f && !AbilitySystemComponent->HasMatchingGameplayTag(DeadTag))
	{
		if (Player)
		{
			Player->Die();
		}
	}

}


