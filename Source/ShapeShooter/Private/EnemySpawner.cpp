// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"


AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

	InitialNumberOfEnemies = 5;
	CurrentNumberOfEnemies = InitialNumberOfEnemies;
	ActiveEnemies = 0;
	WaveInterval = 3.0f;
	SpawnDistanceMin = 1000.0f;
	SpawnDistanceMax = 2000.0f;

	// Create static classes of enemies for array
	static ConstructorHelpers::FClassFinder<AEnemyBase> CubeEnemyClass(TEXT("/Game/Blueprints/BP_CubeEnemy"));
	static ConstructorHelpers::FClassFinder<AEnemyBase> HexagonEnemyClass(TEXT("/Game/Blueprints/BP_HexagonEnemy"));
	static ConstructorHelpers::FClassFinder<AEnemyBase> SphereEnemyClass(TEXT("/Game/Blueprints/BP_SphereEnemy"));

	// Add enemy classes to array
	EnemyClasses.Add(CubeEnemyClass.Class);
	EnemyClasses.Add(HexagonEnemyClass.Class);
	EnemyClasses.Add(SphereEnemyClass.Class);
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	SpawnEnemies();
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemySpawner::StartSpawning()
{
	SpawnNextWave();
}

void AEnemySpawner::SpawnNextWave()
{
	if (ActiveEnemies == 0) 
	{
		SpawnEnemies();
		CurrentNumberOfEnemies++;
	}
}

void AEnemySpawner::SpawnEnemies()
{
	if (Player == nullptr || EnemyClasses.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player or EnemyClasses not set!"));
		return;
	}

	for (int32 i = 0; i < CurrentNumberOfEnemies; i++)
	{
		int32 EnemyIndex = FMath::RandRange(0, EnemyClasses.Num() - 1);
		TSubclassOf<AEnemyBase> EnemyClass = EnemyClasses[EnemyIndex];

		float Distance = FMath::RandRange(SpawnDistanceMin, SpawnDistanceMax);
		float Angle = FMath::RandRange(0.0f, 2.0f * PI);
		FVector SpawnLocation = Player->GetActorLocation() + FVector(FMath::Cos(Angle) * Distance, FMath::Sin(Angle) * Distance, 0.0f);

		AEnemyBase* SpawnedEnemy = GetWorld()->SpawnActor<AEnemyBase>(EnemyClass, SpawnLocation, FRotator::ZeroRotator);
		if (SpawnedEnemy)
		{
			ActiveEnemies++;
			SpawnedEnemy->OnDestroyed.AddDynamic(this, &AEnemySpawner::OnEnemyKilled);
		}
	}
}

void AEnemySpawner::OnEnemyKilled(AActor* DestroyedActor)
{
	ActiveEnemies--;
	if (ActiveEnemies == 0)
	{
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemySpawner::SpawnNextWave, WaveInterval, false);
	}
}
