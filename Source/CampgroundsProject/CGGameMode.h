

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CGGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CAMPGROUNDSPROJECT_API ACGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACGGameMode();

	virtual void BeginPlay() override;

	void PlayerDied(AController* Controller);

	UFUNCTION()
	void HandleDayEnd();

	UFUNCTION(BlueprintCallable)
	void HandleNextDay();

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float RespawnDelay;

	void RespawnHero(AController* Controller);
	
};
