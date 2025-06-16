


#include "CGPlayerState.h"
#include "AbilitySystem/CGAbilitySystemComponent.h"


// Sets default values
ACGPlayerState::ACGPlayerState()
{
	NetUpdateFrequency = 100.f;

	AbilitySystemComponent = CreateDefaultSubobject<UCGAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

}

UAbilitySystemComponent* ACGPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


