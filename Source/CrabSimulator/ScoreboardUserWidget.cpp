// Copyright Gerald Schenke

#include "ScoreboardUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

bool UScoreboardUserWidget::IsNewHighScore(int32 score) const
{
	UE_LOG(LogTemp, Error, TEXT("IsNewHighScore"));
	if (PlayerScores.Num() == HighscoreListSize) {
		for (FPlayerScore playerScore : PlayerScores) {
			if (playerScore.Score < score) {
				return true;
			}
		}
		return false;
	}
	return true;
}

void UScoreboardUserWidget::EnterNewHighscore(FPlayerScore playerScore)
{
	UE_LOG(LogTemp, Log, TEXT("EnterNewHighscore"));
	if (!IsNewHighScore(playerScore.Score)) {
		UE_LOG(LogTemp, Error, TEXT("This is not a highscore. This should never happen!"));
	}
	PlayerScores.Sort(FPlayerScoreDESC());
	if (PlayerScores.Num() >= HighscoreListSize) {
		PlayerScores.RemoveAt(HighscoreListSize - 1);
	}
	PlayerScores.Add(playerScore);
	PlayerScores.Sort(FPlayerScoreDESC());
}

void UScoreboardUserWidget::SaveScores() const
{
	UE_LOG(LogTemp, Log, TEXT("SaveScores"));
	UHighscoreStorage* SaveGameInstance = Cast<UHighscoreStorage>(UGameplayStatics::CreateSaveGameObject(UHighscoreStorage::StaticClass()));
	SaveGameInstance->PlayerScores = PlayerScores;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}

void UScoreboardUserWidget::LoadScores()
{
	UE_LOG(LogTemp, Log, TEXT("LoadScores"));
	UHighscoreStorage* LoadGameInstance = Cast<UHighscoreStorage>(UGameplayStatics::CreateSaveGameObject(UHighscoreStorage::StaticClass()));
	if (UGameplayStatics::DoesSaveGameExist(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex)) {
		LoadGameInstance = Cast<UHighscoreStorage>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
		PlayerScores = LoadGameInstance->PlayerScores;
		PlayerScores.Sort(FPlayerScoreDESC());
	}else {
		UE_LOG(LogTemp, Warning, TEXT("No highscore file found, creating one"));
		SaveScores();
	}
}