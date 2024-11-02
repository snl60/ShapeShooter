// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreWidget.h"
#include "Kismet/GameplayStatics.h"
#include "HighScoreSaveGame.h"
#include "ScoreManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHAPESHOOTER_API UScoreManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UScoreManagerComponent();

	void AddScore(int32 Points);
	int32 GetCurrentScore() const;
	int32 GetHighScore() const;
	void SaveHighScores();
	void LoadHighScores();
	void SetScoreWidget(class UScoreWidget* Widget);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
	TArray<int32> HighScores;

private:
	int32 CurrentScore;
	int32 HighScore;
	static const int32 MaxHighScores = 10;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UScoreWidget> ScoreWidgetClass;

	UPROPERTY()
	UScoreWidget* ScoreWidget;

	void UpdateScoreWidget();	
};
