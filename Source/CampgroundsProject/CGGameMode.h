

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

	void PlayerDied(AController* Controller);

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float RespawnDelay;

	void RespawnHero(AController* Controller);
	
};
