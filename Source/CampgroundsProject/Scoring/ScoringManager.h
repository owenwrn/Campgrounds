

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Scoring.h"
#include "ScoringManager.generated.h"

UCLASS()
class CAMPGROUNDSPROJECT_API AScoringManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScoringManager();

	UFUNCTION(BlueprintCallable)
	int32 CalculateBaseScore(const TArray<FScoring>& Items);

	TMap<EColour, float> GetColourDistribution(const TArray<FScoring>& Items);
	TMap<EShape, float> GetShapeDistribution(const TArray<FScoring>& Items);

	UFUNCTION(BlueprintCallable)
	int32 CalculateBonus(const TArray<FScoring>& Items);

	UFUNCTION(BlueprintCallable)
	int32 CalculateFinalScore(const TArray<FScoring>& Items);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MonochromePercentThreshold = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FColourScheme> ColourScheme;
};
