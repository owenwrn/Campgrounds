


#include "ScoringManager.h"


// Sets default values
AScoringManager::AScoringManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

int32 AScoringManager::CalculateBaseScore(const TArray<FScoring>& Items)
{
    int32 Total = 0;
    for (const FScoring& Item : Items)
    {
        Total += Item.Score;
    }
    return Total;
}

TMap<EColour, float> AScoringManager::GetColourDistribution(const TArray<FScoring>& Items)
{
    TMap<EColour, int32> Counts;
    for (const FScoring& Item : Items)
    {
        if (Item.Colour != EColour::None)
        {
            Counts.FindOrAdd(Item.Colour)++;
        }
    }

    TMap<EColour, float> Distribution;
    if (Items.Num() > 0)
    {
        for (auto& Elem : Counts)
        {
            Distribution.Add(Elem.Key, (float)Elem.Value / (float)Items.Num());
        }
    }
    return Distribution;
}

TMap<EShape, float> AScoringManager::GetShapeDistribution(const TArray<FScoring>& Items)
{
    TMap<EShape, int32> Counts;
    for (const FScoring& Item : Items)
    {
        if (Item.Shape != EShape::None)
        {
            Counts.FindOrAdd(Item.Shape)++;
        }
    }

    TMap<EShape, float> Distribution;
    if (Items.Num() > 0)
    {
        for (auto& Elem : Counts)
        {
            Distribution.Add(Elem.Key, (float)Elem.Value / (float)Items.Num());
        }
    }
    return Distribution;
}

int32 AScoringManager::CalculateBonus(const TArray<FScoring>& Items)
{
    int32 Bonus = 0;

    // Color distribution
    TMap<EColour, float> ColourDist = GetColourDistribution(Items);

    // Rule 1: Monochrome bonus (80%+ same color)
    for (auto& Elem : ColourDist)
    {
        if (Elem.Value >= MonochromePercentThreshold)
        {
            Bonus += 50;
            break;
        }
    }

    for (auto& Scheme : ColourScheme)
    {
        bool bMatches = true;
        for (auto& Col : Scheme.ColourPair)
        {
            if (ColourDist.Contains(Col.Colour))
            {
                if(ColourDist.FindRef(Col.Colour) < Col.PercentThreshold)
                {
                    bMatches = false;
                    break;
                }
            }
            else
            {
                bMatches = false;
                break;
            }
        }
        if (bMatches == true)
        {
            Bonus += Scheme.Bonus;
        }
    }
    return Bonus;
}

int32 AScoringManager::CalculateFinalScore(const TArray<FScoring>& Items)
{
    int32 Base = CalculateBaseScore(Items);
    int32 Bonus = CalculateBonus(Items);
    return Base + Bonus;
}


