#include "CGAttributeSet.h"
#include "Net/UnrealNetwork.h"

UCGAttributeSet::UCGAttributeSet()
{
	CurrentHealth = 100.f;
	MaxHealth = 100.f;
	CurrentStamina = 100.f;
	MaxStamina = 100.f;
	Attack = 10.f;
	MovementSpeed = 500.f;
}

void UCGAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCGAttributeSet, CurrentHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCGAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCGAttributeSet, CurrentStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCGAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCGAttributeSet, Attack, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCGAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);
}

// OnRep functions
void UCGAttributeSet::OnRep_CurrentHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCGAttributeSet, CurrentHealth, OldValue);
	CurrentHealth.SetCurrentValue(FMath::Clamp(CurrentHealth.GetCurrentValue(), 0.0f, MaxHealth.GetCurrentValue()));
}

void UCGAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCGAttributeSet, MaxHealth, OldValue);
	CurrentHealth.SetCurrentValue(FMath::Clamp(CurrentHealth.GetCurrentValue(), 0.0f, MaxHealth.GetCurrentValue()));
}

void UCGAttributeSet::OnRep_CurrentStamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCGAttributeSet, CurrentStamina, OldValue);
	CurrentStamina.SetCurrentValue(FMath::Clamp(CurrentStamina.GetCurrentValue(), 0.0f, MaxStamina.GetCurrentValue()));
}

void UCGAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCGAttributeSet, MaxStamina, OldValue);
	CurrentStamina.SetCurrentValue(FMath::Clamp(CurrentStamina.GetCurrentValue(), 0.0f, MaxStamina.GetCurrentValue()));
}

void UCGAttributeSet::OnRep_Attack(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCGAttributeSet, Attack, OldValue);
}

void UCGAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCGAttributeSet, MovementSpeed, OldValue);
}



