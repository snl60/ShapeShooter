// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreManager.h"

UScoreManager::UScoreManager()
{
	//CurrentScore = 0;
	//HighScore = 0;
	//LoadHighScore();
}
//
//void UScoreManager::AddScore(int32 Points)
//{
//	CurrentScore += Points;
//	
//	if (CurrentScore > HighScore)
//	{
//		HighScore = CurrentScore;
//		SaveGameToSlot();
//	}
//
//	if (ScoreWidget)
//	{
//		ScoreWidget->UpdateCurrentScore(CurrentScore);
//	}
//	else
//	{
//		UE_LOG(LogTemp, Error, TEXT("ScoreWidget is null in AddScore!"));
//	}
//}
//
//int32 UScoreManager::GetCurrentScore() const
//{
//	return CurrentScore;
//}
//
//void UScoreManager::SaveHighScore()
//{
//	UHighScoreSaveGame* SaveGameInstance = Cast<UHighScoreSaveGame>(UGameplayStatics::CreateSaveGameObject(UHighScoreSaveGame::StaticClass()));
//	
//	if (SaveGameInstance)
//	{
//		SaveGameInstance->HighScore = HighScore;
//
//		UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("HighScores"), 0);
//	}
//	else
//	{
//		UE_LOG(LogTemp, Error, TEXT("Failed to create SaveGameInstace for HighScoreSaveGame!"));
//	}
//}
//
//int32 UScoreManager::GetHighScore() const
//{
//	return HighScore;
//}
//
//void UScoreManager::LoadHighScore()
//{
//	FString SaveDirectory = FPaths::ProjectSavedDir() / TEXT("SaveGames");
//	if (!FPaths::DirectoryExists(SaveDirectory))
//	{
//		IFileManager::Get().MakeDirectory(*SaveDirectory, true);
//	}
//
//	if (UGameplayStatics::DoesSaveGameExist(TEXT("HighScores"), 0))
//	{
//		USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(TEXT("HighScore"), 0);
//		if (LoadedGame)
//		{
//			UHighScoreSaveGame* HighScoreSaveGame = Cast<UHighScoreSaveGame>(LoadedGame);
//			if (HighScoreSaveGame)
//			{
//				HighScore = HighScoreSaveGame->HighScore;
//			}
//			else
//			{
//				UE_LOG(LogTemp, Error, TEXT("Failed to case LoadedGame to UHighScoreSaveGame!"));
//				HighScore = 0;
//			}
//		}
//		else
//		{
//			UE_LOG(LogTemp, Error, TEXT("Failed to load HighScores.sav!"));
//		}
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Highscores.sav not found, initializing HighScore to 0."))
//	}
//}
//
//void UScoreManager::SaveGameToSlot()
//{
//	FString SaveDirectory = FPaths::ProjectSavedDir() / TEXT("SaveGames");
//	if (!FPaths::DirectoryExists(SaveDirectory))
//	{
//		IFileManager::Get().MakeDirectory(*SaveDirectory, true);
//	}
//	
//	UHighScoreSaveGame* SaveGameInstance = Cast<UHighScoreSaveGame>(UGameplayStatics::CreateSaveGameObject(UHighScoreSaveGame::StaticClass()));
//
//	if (SaveGameInstance)
//	{
//		SaveGameInstance->HighScore = { HighScore };
//		UGameplayStatics::SaveGameToSlot(SaveGameInstance, "HighScores", 0);
//	}
//}
//
//void UScoreManager::LoadGameFromSlot()
//{
//	UHighScoreSaveGame* LoadedGame = Cast<UHighScoreSaveGame>(UGameplayStatics::LoadGameFromSlot("HighScores", 0));
//	if (LoadedGame)
//	{
//		HighScore = LoadedGame->HighScore;
//	}
//	else
//	{
//		HighScore = 0;
//		UE_LOG(LogTemp, Warning, TEXT("No save file found or failed to load. HighScore set to 0."))
//	}
//}
