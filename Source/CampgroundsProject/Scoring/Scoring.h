

#pragma once

#include "CoreMinimal.h"
#include "Scoring.generated.h"

UENUM(BlueprintType)
enum class EColour : uint8
{
    None,
    Red,
    Orange,
    Yellow,
    Green,
    Blue,
    Purple,
    White,
    Black
};

UENUM(BlueprintType)
enum class EShape : uint8
{
    None,
    Round,
    Spike,
    Tall,
    Wide,
    Unique
};

UENUM(BlueprintType)
enum class ERarity : uint8
{
    Common,
    Uncommon,
    Rare,
    Epic,
    Exotic
};

USTRUCT(BlueprintType)
struct CAMPGROUNDSPROJECT_API FScoring
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Score = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EColour Colour = EColour::Red;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EShape Shape = EShape::Round;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ERarity Rarity = ERarity::Common;
};

USTRUCT(BlueprintType)
struct CAMPGROUNDSPROJECT_API FColourPair
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EColour Colour = EColour::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PercentThreshold = 0.3f;
};

USTRUCT(BlueprintType)
struct CAMPGROUNDSPROJECT_API FColourScheme
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Bonus = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FColourPair> ColourPair;
};