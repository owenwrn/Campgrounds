


#include "CGGameStateBase.h"
#include "AbilitySystem/CGAbilitySystemComponent.h"
#include "CampgroundsProject/AbilitySystem/AttributeSets/EconomyAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include <Kismet/GameplayStatics.h>
#include "UI/CGHUD.h"

ACGGameStateBase::ACGGameStateBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCGAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UEconomyAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ACGGameStateBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UEconomyAttributeSet* ACGGameStateBase::GetAttributeSet() const
{
	return AttributeSet;
}

void ACGGameStateBase::Multicast_OnMatchEnding_Implementation()
{
	OnMatchEnding.Broadcast();
}

void ACGGameStateBase::Multicast_OnMatchEnd_Implementation()
{
	OnMatchEnd.Broadcast();
}

void ACGGameStateBase::OnRep_MatchTime()
{
	OnMatchTimeChanged.Broadcast(MatchTime);
}

void ACGGameStateBase::TickMatchTimer()
{
	if (HasAuthority())
	{
		MatchTime = MatchTime - 1.f;
		if (MatchTime <= 0)
		{
			MatchTime = 0;
			GetWorldTimerManager().ClearTimer(MatchTimerHandle);
			StartMatchEndingTimer();
			Multicast_OnMatchEnding();
		}

		ForceNetUpdate();
	}

	if (IsNetMode(NM_ListenServer))
	{
		OnRep_MatchTime();
	}
}

void ACGGameStateBase::OnRep_MatchEndingTime()
{
	OnMatchEndingTimeChanged.Broadcast(MatchEndingTime);
}

void ACGGameStateBase::TickMatchEndingTimer()
{
	if (HasAuthority())
	{
		MatchEndingTime = MatchEndingTime - 1.f;
		if (MatchEndingTime <= 0)
		{
			MatchTime = 0;
			GetWorldTimerManager().ClearTimer(MatchEndingTimerHandle);
			Multicast_OnMatchEnd();
			HandleEndGame();
		}

		ForceNetUpdate();
	}

	if (IsNetMode(NM_ListenServer))
	{
		OnRep_MatchEndingTime();
	}
}

void ACGGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ACGGameStateBase, MatchTime, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ACGGameStateBase, MatchEndingTime, COND_None, REPNOTIFY_Always);
}

void ACGGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(MatchTimerHandle, this, &ACGGameStateBase::TickMatchTimer, 1.0f, true);		
	}

	OnMatchStart.Broadcast();
}

void ACGGameStateBase::StartMatchEndingTimer()
{
	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(MatchEndingTimerHandle, this, &ACGGameStateBase::TickMatchEndingTimer, 1.0f, true);
	}
}

