// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyProjectile.h"

AEnemyProjectile::AEnemyProjectile()
{
	// Set enemy projectiles to ignore enemy pawns
	CollisionComponent->SetCollisionResponseToChannel(ECC_EnemyPawn, ECollisionResponse::ECR_Ignore);
	MeshComponent->SetCollisionResponseToChannel(ECC_EnemyPawn, ECollisionResponse::ECR_Ignore);
}