// Copyright Gerald Schenke

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HighscoreStorage.h"
#include "ScoreboardUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CRABSIMULATOR_API UScoreboardUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoreboard")
	TArray<FPlayerScore> PlayerScores;

	UFUNCTION(BlueprintCallable, Category = "Scoreboard")
	bool IsNewHighScore(int32 score) const;

	UFUNCTION(BlueprintCallable, Category = "Scoreboard")
	void EnterNewHighscore(FPlayerScore playerScore);

	UFUNCTION(BlueprintCallable, Category = "Scoreboard")
	void LoadScores();
	
	UFUNCTION(BlueprintCallable, Category = "Scoreboard")
	void SaveScores() const;

private:
	int HighscoreListSize = 5;
	FString SaveGameName = "Highscores";
};
