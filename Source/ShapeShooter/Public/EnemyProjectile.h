// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "CustomCollisionChannels.h"
#include "EnemyProjectile.generated.h"


UCLASS()
class SHAPESHOOTER_API AEnemyProjectile : public AProjectile
{
	GENERATED_BODY()

public:
	AEnemyProjectile();
};
