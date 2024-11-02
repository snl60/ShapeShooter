// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"

void UScoreWidget::UpdateCurrentScore(int32 NewScore)
{
	if (CurrentScoreText)
	{
		CurrentScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), NewScore)));
	}
}

void UScoreWidget::UpdateHighScore(int32 NewHighScore)
{
	if (HighScoreText)
	{
		HighScoreText->SetText(FText::FromString(FString::Printf(TEXT("High Score: %d"), NewHighScore)));
	}
}