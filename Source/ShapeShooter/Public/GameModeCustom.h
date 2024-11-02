// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerControllerCustom.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"
#include "ScoreManager.h"
#include "GameModeCustom.generated.h"


UCLASS()
class SHAPESHOOTER_API AGameModeCustom : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameModeCustom();

	virtual void BeginPlay() override;

	//UScoreManager* GetScoreManager() const { return ScoreManager; }

private:
	//UScoreManager* ScoreManager;
};
