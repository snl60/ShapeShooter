// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonEnemy.h"


AHexagonEnemy::AHexagonEnemy()
{
	// Initializing class variables
	Angle = FMath::RandRange(0.0f, 2.0f * PI);
	OrbitDistance = FMath::RandRange(750.0f, 1250.0f);
	OrbitSpeed = 1.0f;
	FireRate = 2.0f;
	FireTimer = 0.0f;

	// Setting up collision component (must be done in subclass due to different types)
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision Component"));
	CollisionComponent->InitSphereRadius(100.0f);
	CollisionComponent->SetCollisionProfileName(TEXT("EnemyPawn"));
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetCollisionObjectType(ECC_EnemyPawn);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	RootComponent = CollisionComponent;

	// Bind hit event from parent
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnOverlapBegin);

	// Attaching mesh component to root (must be done in subclass where RootComponent is initialized)
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);
	MeshComponent->SetupAttachment(RootComponent);

	// Assigning static mesh and material
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Meshes/HexagonalCube.HexagonalCube"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MeshMaterial(TEXT("/Game/Materials/M_Heaxagon.M_Heaxagon"));
	if (MeshAsset.Succeeded() && MeshMaterial.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
		MeshComponent->SetMaterial(0, MeshMaterial.Object);
	}

	// Setting up movement component (must be done in subclass where RootComponent is initialized)
	MovementComponent->UpdatedComponent = RootComponent;
}

void AHexagonEnemy::Move(float DeltaTime)
{
	if (Player)
	{
		Angle += OrbitSpeed * DeltaTime;
		FVector OrbitLocation = Player->GetActorLocation() + FVector(FMath::Cos(Angle) * OrbitDistance, FMath::Sin(Angle) * OrbitDistance, 0.0f);
		SetActorLocation(OrbitLocation);
	}
}

void AHexagonEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FireTimer += DeltaTime;

	if (FireTimer >= FireRate)
	{
		FireProjectile();
		FireTimer = 0.0f;
	}
}

void AHexagonEnemy::FireProjectile()
{
	if (ProjectileClass && Player)
	{
		FVector MuzzleLocation = GetActorLocation() - FVector(0.0f, 0.0f, 25.0f);
		FRotator MuzzleRotation = (Player->GetActorLocation() - GetActorLocation()).Rotation();

		AProjectile* FiredProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation);
		if (FiredProjectile)
		{
			FiredProjectile->CollisionComponent->IgnoreActorWhenMoving(this, true);
			FiredProjectile->MeshComponent->IgnoreActorWhenMoving(this, true);
		}
	}
}
