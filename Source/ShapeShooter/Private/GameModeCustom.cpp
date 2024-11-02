// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeCustom.h"


AGameModeCustom::AGameModeCustom()
{
	// Set game mode to use custom player controller
	PlayerControllerClass = APlayerControllerCustom::StaticClass();

	// Set default pawn class
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AGameModeCustom::BeginPlay()
{
	Super::BeginPlay();

	//FString SaveDirectory = FPaths::ProjectSavedDir() / TEXT("SaveGames");
	//if (!FPaths::DirectoryExists(SaveDirectory))
	//{
	//	IFileManager::Get().MakeDirectory(*SaveDirectory, true);
	//}

	//ScoreManager = NewObject<UScoreManager>(this, UScoreManager::StaticClass());

	//if (ScoreManager)
	//{
	//	ScoreManager->LoadHighScore();
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Error, TEXT("ScoreManager failed to initialize in GameModeCustom!"));
	//}
}
