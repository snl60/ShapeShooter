// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "PlayerCharacter.h"
#include "CustomCollisionChannels.h"
#include "ScoreManagerComponent.h"
#include "EnemyBase.generated.h"


UCLASS()
class SHAPESHOOTER_API AEnemyBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyBase();

	virtual void Tick(float DeltaTime) override;

	// OnOverlapBegin method (inheritted by derived classes)
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

	// Movement method (to be overridden by derived classes; cannot make pure virtual because it makes AEnemyBase abstract and causes compiler error)
	virtual void Move(float DeltaTime);

	// TakeDamage method (inheritted by derived classes)
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Player reference
	AActor* Player;

	// Score Manager reference
	UScoreManagerComponent* ScoreManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Properties")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Properties")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageToPlayer = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	class UFloatingPawnMovement* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Points;
};
