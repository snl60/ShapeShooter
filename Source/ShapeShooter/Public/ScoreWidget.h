// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ScoreWidget.generated.h"


UCLASS()
class SHAPESHOOTER_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Score")
	void UpdateCurrentScore(int32 NewScore);

	UFUNCTION(BlueprintCallable, Category = "Score")
	void UpdateHighScore(int32 NewHighScore);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentScoreText;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HighScoreText;
};
