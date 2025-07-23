#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "AbilitySystemInterface.h"
#include "CGGameStateBase.generated.h"

class UCGAbilitySystemComponent;
class UEconomyAttributeSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMatchStartDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMatchEndingDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMatchEndDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMatchTimeChangedDelegate, int32, time);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMatchEndingTimeChangedDelegate, int32, time);

UCLASS()
class CAMPGROUNDSPROJECT_API ACGGameStateBase : public AGameStateBase, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    ACGGameStateBase();

    //GAS Interface
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    virtual UEconomyAttributeSet* GetAttributeSet() const;

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

    FTimerHandle MatchTimerHandle;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, ReplicatedUsing = OnRep_MatchTime)
    int32 MatchTime = 300;

    UFUNCTION()
    void OnRep_MatchTime();

    void TickMatchTimer();

    FTimerHandle MatchEndingTimerHandle;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, ReplicatedUsing = OnRep_MatchEndingTime)
    int32 MatchEndingTime = 30;

    UFUNCTION()
    void OnRep_MatchEndingTime();

    void TickMatchEndingTimer();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
    TObjectPtr<UCGAbilitySystemComponent> AbilitySystemComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
    TObjectPtr<UEconomyAttributeSet> AttributeSet;

    virtual void BeginPlay() override;

    void StartMatchEndingTimer();

};
