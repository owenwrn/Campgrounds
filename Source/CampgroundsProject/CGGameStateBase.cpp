


#include "CGGameStateBase.h"
#include "AbilitySystem/CGAbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"
#include <Kismet/GameplayStatics.h>
#include "UI/CGHUD.h"

ACGGameStateBase::ACGGameStateBase()
{
	Money = 0;
}

void ACGGameStateBase::Server_AddMoney_Implementation(int32 amount)
{
	if (amount <= 0) return;

	Money += amount;

	OnMoneyChanged.Broadcast(Money);
}

void ACGGameStateBase::Server_SpendMoney_Implementation(int32 amount)
{
	if (amount <= 0) return; 

	if (Money < amount) return; // Not enough money

	Money -= amount;

	OnMoneyChanged.Broadcast(Money);
}

void ACGGameStateBase::OnRep_Money()
{
	OnMoneyChanged.Broadcast(Money);
}

void ACGGameStateBase::Multicast_NextDay_Implementation()
{
	OnNextDay.Broadcast();
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
			CurrentDay++;
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
	DOREPLIFETIME(ACGGameStateBase, Money);
}

void ACGGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	StartMatchTimer();
}

void ACGGameStateBase::StartMatchTimer()
{
	if (HasAuthority())
	{
		MatchTime = InitialMatchTime;

		GetWorldTimerManager().SetTimer(MatchTimerHandle, this, &ACGGameStateBase::TickMatchTimer, 1.0f, true);
	}

	OnMatchStart.Broadcast();
	OnMatchTimeChanged.Broadcast(InitialMatchTime);
}

void ACGGameStateBase::StartMatchEndingTimer()
{
	if (HasAuthority())
	{
		MatchEndingTime = IntialMatchEndingTime;

		GetWorldTimerManager().SetTimer(MatchEndingTimerHandle, this, &ACGGameStateBase::TickMatchEndingTimer, 1.0f, true);
	}

	OnMatchEndingTimeChanged.Broadcast(IntialMatchEndingTime);
}

