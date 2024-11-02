// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/OutputDeviceDebug.h"
#include "PlayerControllerCustom.generated.h"


UCLASS()
class SHAPESHOOTER_API APlayerControllerCustom : public APlayerController
{
	GENERATED_BODY()
	
public:
	APlayerControllerCustom();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> WidgetClass;

private:
	UUserWidget* CursorWidget;
};
