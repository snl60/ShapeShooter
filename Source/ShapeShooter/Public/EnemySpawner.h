// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "EnemySpawner.generated.h"


UCLASS()
class SHAPESHOOTER_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySpawner();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnEnemies();

	UFUNCTION()
	void OnEnemyKilled(AActor* DestroyedActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void StartSpawning();
	void SpawnNextWave();

	FTimerHandle SpawnTimerHandle;
	int32 CurrentNumberOfEnemies;
	int32 ActiveEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (AllowPrivateAccess = true))
	int32 InitialNumberOfEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (AllowPrivateAccess = true))
	AActor* Player;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<AEnemyBase>> EnemyClasses;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Spawning", meta = (AllowPrivateAccess = true))
	float WaveInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (AllowPrivateAccess = true))
	float SpawnDistanceMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (AllowPrivateAccess = true))
	float SpawnDistanceMax;
};
