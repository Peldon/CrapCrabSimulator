// Copyright Gerald Schenke

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HighscoreStorage.generated.h"


/**
* PlayerScore struct to store the name, score and date
*/
USTRUCT(BlueprintType)
struct FPlayerScore
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerScore Struct")
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerScore Struct")
		int32 Score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerScore Struct")
		FDateTime Date;
};

/**
* method to sort PlayerScores easily
*/
struct FPlayerScoreDESC
{
	bool operator()(const FPlayerScore& l, const FPlayerScore& r) const {
		if (l.Score == r.Score) {
			return l.Date < r.Date;
		}
		return l.Score > r.Score;
	}
};

/**
 * 
 */
UCLASS()
class CRABSIMULATOR_API UHighscoreStorage : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
	TArray<FPlayerScore> PlayerScores;
	
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;

	UHighscoreStorage();
};
