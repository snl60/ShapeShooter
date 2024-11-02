// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreManagerComponent.h"

UScoreManagerComponent::UScoreManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentScore = 0;
	HighScore = 0;
}

void UScoreManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	LoadHighScores();

	if (ScoreWidgetClass)
	{
		ScoreWidget = CreateWidget<UScoreWidget>(GetWorld(), ScoreWidgetClass);

		if (ScoreWidget)
		{
			ScoreWidget->AddToViewport();
			UpdateScoreWidget();

			if (HighScores.Num() > 0)
			{
				ScoreWidget->UpdateHighScore(HighScores[0]);
			}
		}
	}
}

void UScoreManagerComponent::AddScore(int32 Points)
{
	CurrentScore += Points;

	if (HighScores.Num() < MaxHighScores || CurrentScore > HighScores.Last())
	{
		HighScores.Add(CurrentScore);
		HighScores.Sort([](const int32& A, const int32& B) {
			return A > B;
		});

		if (HighScores.Num() > MaxHighScores)
		{
			HighScores.RemoveAt(MaxHighScores);
		}
		
		SaveHighScores();
	}

	UpdateScoreWidget();
}

int32 UScoreManagerComponent::GetCurrentScore() const
{
	return CurrentScore;
}

int32 UScoreManagerComponent::GetHighScore() const
{
	return HighScore;
}

void UScoreManagerComponent::SaveHighScores()
{
	UHighScoreSaveGame* SaveGameInstance = Cast<UHighScoreSaveGame>(UGameplayStatics::CreateSaveGameObject(UHighScoreSaveGame::StaticClass()));
	
	if (SaveGameInstance)
	{
		SaveGameInstance->SavedHighScores = HighScores;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("HighScoresSlot"), 0);
	}
}

void UScoreManagerComponent::LoadHighScores()
{
	if (UGameplayStatics::DoesSaveGameExist(TEXT("HighScoresSlot"), 0))
	{
		UHighScoreSaveGame* LoadedGame = Cast<UHighScoreSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("HighScoresSlot"), 0));

		if (LoadedGame)
		{
			HighScores = LoadedGame->SavedHighScores;
		}
	}

	if (HighScores.Num() == 0)
	{
		HighScores.Init(0, MaxHighScores);
	}
}

void UScoreManagerComponent::SetScoreWidget(UScoreWidget* Widget)
{
	ScoreWidget = Widget;
	UpdateScoreWidget();
}

void UScoreManagerComponent::UpdateScoreWidget()
{
	if (ScoreWidget)
	{
		ScoreWidget->UpdateCurrentScore(CurrentScore);
		
		if (HighScores.Num() > 0)
		{
			ScoreWidget->UpdateHighScore(HighScores[0]);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ScoreWidget is null in UpdateScoreWidget!"));
	}
}
