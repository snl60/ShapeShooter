// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "HexagonEnemy.generated.h"


UCLASS()
class SHAPESHOOTER_API AHexagonEnemy : public AEnemyBase
{
	GENERATED_BODY()
	
private:
	float Angle;
	float OrbitDistance;
	float OrbitSpeed;
	float FireRate;
	float FireTimer;

public:
	AHexagonEnemy();
	virtual void Move(float DeltaTime) override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<class AProjectile> ProjectileClass;

	void FireProjectile();
};
