// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HighScoreSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "ScoreWidget.h"
#include "ScoreManager.generated.h"


UCLASS()
class SHAPESHOOTER_API UScoreManager : public UObject
{
	GENERATED_BODY()

public:
	UScoreManager();
//
//	void SetScoreWidget(UScoreWidget* Widget) { ScoreWidget = Widget; }
//
//	UFUNCTION(BlueprintCallable, Category = "Score")
//	void AddScore(int32 Points);
//
//	UFUNCTION(BlueprintCallable, Category = "Score")
//	int32 GetCurrentScore() const;
//
//	UFUNCTION(BlueprintCallable, Category = "Score")
//	void SaveHighScore();
//
//	UFUNCTION(BlueprintCallable, Category = "Score")
//	int32 GetHighScore() const;
//
//	UFUNCTION(BlueprintCallable, Category = "Score")
//	void LoadHighScore();
//
//private:
//	int32 CurrentScore;
//	int32 HighScore;
//
//	void SaveGameToSlot();
//	void LoadGameFromSlot();
//
//protected:
//	UScoreWidget* ScoreWidget;
};
