// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"


AEnemyBase::AEnemyBase()
{
 	// Set this pawn to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;
	
	Health = 500.0f;
	Speed = 500.0f;
	Points = 100;
	Player = nullptr;
	ScoreManager = nullptr;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (Player)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Player);
		if (PlayerCharacter)
		{
			ScoreManager = PlayerCharacter->FindComponentByClass<UScoreManagerComponent>();
		}
	}
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}

void AEnemyBase::Move(float DeltaTime)
{
	 // Movement logic to be overridden by derived classes
}

float AEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Health -= DamageApplied;

	if (Health <= 0.0f)
	{
		if (ScoreManager)
		{
			ScoreManager->AddScore(Points);
		}
		Destroy();
	}

	return DamageApplied;
}

void AEnemyBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
		if (PlayerCharacter)
		{
			UGameplayStatics::ApplyDamage(PlayerCharacter, DamageToPlayer, GetInstigatorController(), this, nullptr);
			Destroy();
		}
	}
}
