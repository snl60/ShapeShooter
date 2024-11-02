// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CubeEnemy.generated.h"


UCLASS()
class SHAPESHOOTER_API ACubeEnemy : public AEnemyBase
{
	GENERATED_BODY()
	
private:
	float ZigZagTimer;
	bool bMoveLeft;

public:
	ACubeEnemy();
	virtual void Move(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* MeshComponent;

	//UFUNCTION()
	//void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
