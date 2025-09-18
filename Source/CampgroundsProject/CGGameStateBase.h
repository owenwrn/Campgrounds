#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "CGGameStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMatchStartDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMatchEndingDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMatchEndDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMatchTimeChangedDelegate, int32, time);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMatchEndingTimeChangedDelegate, int32, time);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNextDayDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoneyChangedDelegate, int32, value);

UCLASS()
class CAMPGROUNDSPROJECT_API ACGGameStateBase : public AGameStateBase
{
    GENERATED_BODY()

public:
    ACGGameStateBase();

    UPROPERTY(ReplicatedUsing = OnRep_money, BlueprintReadOnly, Category = "Currency")
    int32 Money;

    UPROPERTY(BlueprintAssignable, Category = "Currency")
    FOnMoneyChangedDelegate OnMoneyChanged;

    UFUNCTION(Server, Reliable)
    void Server_AddMoney(int32 amount);

    UFUNCTION(Server, Reliable)
    void Server_SpendMoney(int32 amount);

    UFUNCTION()
    void OnRep_Money();

    UPROPERTY(BlueprintAssignable, Category = "Day System")
    FOnNextDayDelegate OnNextDay;

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_NextDay();

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Day System")
    int32 CurrentDay;

    UPROPERTY(BlueprintAssignable)
    FMatchStartDelegate OnMatchStart;

    UPROPERTY(BlueprintAssignable)
    FMatchEndingDelegate OnMatchEnding;

    UPROPERTY(BlueprintAssignable)
    FMatchEndDelegate OnMatchEnd;

    UPROPERTY(BlueprintAssignable)
    FMatchTimeChangedDelegate OnMatchTimeChanged;

    UPROPERTY(BlueprintAssignable)
    FMatchEndingTimeChangedDelegate OnMatchEndingTimeChanged;

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_OnMatchEnding();

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_OnMatchEnd();

    FTimerHandle MatchTimerHandle;

    UPROPERTY(ReplicatedUsing = OnRep_MatchTime)
    int32 MatchTime;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    int32 InitialMatchTime = 300;

    UFUNCTION()
    void OnRep_MatchTime();

    void TickMatchTimer();

    FTimerHandle MatchEndingTimerHandle;

    UPROPERTY(ReplicatedUsing = OnRep_MatchEndingTime)
    int32 MatchEndingTime;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    int32 IntialMatchEndingTime = 30;

    UFUNCTION()
    void OnRep_MatchEndingTime();

    void TickMatchEndingTimer();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    void StartMatchTimer();

protected:

    virtual void BeginPlay() override;

    void StartMatchEndingTimer();

    UFUNCTION(BlueprintImplementableEvent)
    void HandleEndGame();

};
