


#include "CGPlayerState.h"
#include "AbilitySystem/CGAbilitySystemComponent.h"
#include "CampgroundsProject/CGAttributeSet.h"


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


