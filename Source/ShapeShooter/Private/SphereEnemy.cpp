// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereEnemy.h"


ASphereEnemy::ASphereEnemy()
{
	Speed = 500.0f;

	// Setting up collision component (must be done in subclass due to different types)
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision Component"));
	CollisionComponent->InitSphereRadius(50.0f);
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
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MeshMaterial(TEXT("/Game/Materials/M_Sphere.M_Sphere"));
	if (MeshAsset.Succeeded() && MeshMaterial.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
		MeshComponent->SetMaterial(0, MeshMaterial.Object);
	}

	// Setting up movement component (must be done in subclass where RootComponent is initialized)
	MovementComponent->UpdatedComponent = RootComponent;
}

void ASphereEnemy::Move(float DeltaTime)
{
	if (Player)
	{
		FVector Direction = (Player->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		FVector NewLocation = GetActorLocation() + (Direction * Speed * DeltaTime);
		SetActorLocation(NewLocation);
	}
}
