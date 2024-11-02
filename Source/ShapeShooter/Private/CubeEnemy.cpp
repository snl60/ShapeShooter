// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeEnemy.h"


ACubeEnemy::ACubeEnemy()
{
	Speed = 500.0f;
	ZigZagTimer = 0.0f;
	bMoveLeft = true;

	// Setting up collision component (must be done in subclass due to different types)
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision Component"));
	CollisionComponent->InitBoxExtent(FVector(50.f, 50.f, 50.f));
	CollisionComponent->SetCollisionProfileName(TEXT("EnemyPawn"));
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetCollisionObjectType(ECC_EnemyPawn);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Player, ECR_Overlap);
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
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MeshMaterial(TEXT("/Game/Materials/M_Cube.M_Cube"));
	if (MeshAsset.Succeeded() && MeshMaterial.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
		MeshComponent->SetMaterial(0, MeshMaterial.Object);
	}

	// Setting up movement component (must be done in subclass where RootComponent is initialized)
	MovementComponent->UpdatedComponent = RootComponent;
}

void ACubeEnemy::Move(float DeltaTime)
{
	if (Player)
	{
		ZigZagTimer += DeltaTime;
		if (ZigZagTimer > 1.0f)
		{
			bMoveLeft = !bMoveLeft;
			ZigZagTimer = 0.0f;
		}

		FVector Direction = (Player->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		FVector RightVector = FVector::CrossProduct(Direction, FVector::UpVector).GetSafeNormal();
		FVector ZigZagDirection = bMoveLeft ? RightVector : -RightVector;
		FVector CombinedDirection = Direction + (ZigZagDirection * 0.75f);
		CombinedDirection = CombinedDirection.GetSafeNormal();
		FVector NewLocation = GetActorLocation() + (CombinedDirection * Speed * DeltaTime);
		SetActorLocation(NewLocation);
	}
}
